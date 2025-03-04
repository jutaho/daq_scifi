#include "datareceiver.h"
#include "dev_commands.h"
#include "helpers.h"   // uses the BYTES2SHORT(...) macro
#include <iostream>    // for std::cerr, etc.
#include <cstring>     // for memset, memcpy

DataReceiver::DataReceiver(QObject *parent)
    : QObject(parent)
    , dataBuffer(RECEIVER_BUFFER_SIZE)
{
    connect(this, &DataReceiver::sigInit, this, &DataReceiver::onInit);
    connect(this, &DataReceiver::sigDeinit, this, &DataReceiver::onDeinit);
    connect(this, &DataReceiver::sigConfigureEthSettings, this, &DataReceiver::onConfigureEthSettings);

    moveToThread(&thread);
    thread.start();
    init();
}

DataReceiver::~DataReceiver()
{
    deinit();
    thread.quit();
    thread.wait();
}

void DataReceiver::init()
{
    emit sigInit();
    initSemaphore.acquire();
}

void DataReceiver::deinit()
{
    emit sigDeinit();
    initSemaphore.acquire();
}

void DataReceiver::readData()
{
    int size_received_bytes;
    while ((size_received_bytes = dataSocket->readDatagram(tmpBuffer, DATA_MAX_PACKET_SIZE)) > 0)
    {
        int expected_size_bytes = getExpectedPacketSize(sensorsPerBoard, dmaBunch, ethBunch);
        if (size_received_bytes != expected_size_bytes)
        {
            std::cerr << "[ERROR] packet size mismatch: got "
                      << size_received_bytes
                      << ", expected " << expected_size_bytes << std::endl;
            continue;
        }

        int raw_block_size = getDataRawBlockSize(sensorsPerBoard);

        for (int ethb = 0; ethb < ethBunch; ethb++)
        {
            int baseaddr = ethb * (DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE +
                                   dmaBunch * (2 * raw_block_size) +
                                   DATA_RMS_FRAME_SIZE);

            // Check packet header:
            if (BYTES2SHORT(tmpBuffer + baseaddr) != 0x5555 ||
                BYTES2SHORT(tmpBuffer + baseaddr + 2) != COMMAND_DATA_TRANSFER)
            {
                continue;
            }

            // Parse sync frame:
            SyncFrame sync;
            sync.local_ctr  = BYTES2SHORT(tmpBuffer + baseaddr + 6);
            sync.global_ctr = BYTES2SHORT(tmpBuffer + baseaddr + 8);
            sync.sma_state  = BYTES2SHORT(tmpBuffer + baseaddr + 10);
            sync.device_nr  = devNr;
            sync.data_ok    = 1;

            // Process each DMA block:
            for (int dmab = 0; dmab < dmaBunch; dmab++)
            {
                framesReceived++;

                if (!outputEnabled)
                    continue;

                int base_raw = baseaddr
                               + DATA_PACKET_HEADER_SIZE
                               + DATA_SYNC_HEADER_SIZE
                               + dmab * (2 * raw_block_size);

                int base_cal = base_raw + raw_block_size;

                // Create a BufferData for one "frame" of data:
                BufferData data(sensorsPerBoard * DATA_SAMPLES_PER_SENSOR);
                data.sync_frame = sync;

                // Copy raw & cal data:
                for (int s = 0; s < data.buffer_size; s++)
                {
                    // Raw is "65535 - value" (inverted?):
                    data.raw_data[s] = 65535 - BYTES2SHORT(tmpBuffer + base_raw + 2*s);

                    // Cal is direct read:
                    data.cal_data[s] = BYTES2SHORT(tmpBuffer + base_cal + 2*s);
                }

                // Parse RMS info (just once per DMA block, after the raw+cal blocks):
                int rms_base = baseaddr
                               + DATA_PACKET_HEADER_SIZE
                               + DATA_SYNC_HEADER_SIZE
                               + dmaBunch * (2 * raw_block_size);

                data.rms_frame.mean   = BYTES2SHORT(tmpBuffer + rms_base);
                data.rms_frame.sigma  = BYTES2SHORT(tmpBuffer + rms_base + 2);
                data.rms_frame.max    = BYTES2SHORT(tmpBuffer + rms_base + 4);
                data.rms_frame.status = BYTES2SHORT(tmpBuffer + rms_base + 6);

                // Push to ring buffer:
                if (!dataBuffer.push(data))
                {
                    std::cerr << "[WARNING] Data buffer overflow!" << std::endl;
                }

                framesFromLastSig++;
            }
        }

        // Emit signal periodically after N frames:
        if (framesFromLastSig >= RECEIVER_FRAMES_PER_SIG)
        {
            framesFromLastSig = 0;
            emit sigDataReady(this);
        }
    }
}

// -------------- The rest is unchanged (onInit, onDeinit, etc.) --------------

void DataReceiver::onInit()
{
    dataSocket = new QUdpSocket(this);
    dataSocket->bind(address, port);
    connect(dataSocket, &QUdpSocket::readyRead, this, &DataReceiver::readData);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DataReceiver::onTimer);
    timer->start(RECEIVER_TIMER_PERIOD_MS);

    initSemaphore.release();
}

void DataReceiver::onDeinit()
{
    if (timer) {
        timer->stop();
        timer->deleteLater();
        timer = nullptr;
    }

    if (dataSocket) {
        dataSocket->close();
        dataSocket->deleteLater();
        dataSocket = nullptr;
    }

    initSemaphore.release();
}

void DataReceiver::configureEthSettings(QHostAddress address_to_set, quint16 port_to_set)
{
    address = address_to_set;
    port = port_to_set;
    emit sigConfigureEthSettings();
}

void DataReceiver::configureBunchSize(int dma, int eth)
{
    dmaBunch = dma;
    ethBunch = eth;
}

void DataReceiver::outputEnable(int en)
{
    outputEnabled = en;
}

void DataReceiver::onConfigureEthSettings()
{
    if (dataSocket) {
        dataSocket->close();
        dataSocket->bind(address, port);
    }
}

void DataReceiver::onTimer()
{
    frameRate = (framesReceived * 1000) / RECEIVER_TIMER_PERIOD_MS;
    framesReceived = 0;
}

// ----------------- BufferData class implementations ------------------

BufferData::BufferData()
    : buffer_size(0)
    , raw_data(nullptr)
    , cal_data(nullptr)
{
}

BufferData::BufferData(int size)
    : buffer_size(0)
    , raw_data(nullptr)
    , cal_data(nullptr)
{
    resize(size);
}

void BufferData::resize(int size)
{
    if (size == buffer_size)
        return;

    if (raw_data) {
        delete[] raw_data;
        raw_data = nullptr;
    }
    if (cal_data) {
        delete[] cal_data;
        cal_data = nullptr;
    }

    buffer_size = size;
    raw_data = new unsigned short[size];
    cal_data = new signed short[size];

    memset(raw_data, 0, size * sizeof(unsigned short));
    memset(cal_data, 0, size * sizeof(signed short));
}

BufferData::BufferData(const BufferData& master)
    : buffer_size(0)
    , raw_data(nullptr)
    , cal_data(nullptr)
{
    sync_frame = master.sync_frame;
    rms_frame  = master.rms_frame;
    resize(master.buffer_size);

    memcpy(raw_data, master.raw_data, buffer_size * sizeof(unsigned short));
    memcpy(cal_data, master.cal_data, buffer_size * sizeof(signed short));
}

BufferData& BufferData::operator=(const BufferData& master)
{
    if (this == &master)
        return *this;

    sync_frame = master.sync_frame;
    rms_frame  = master.rms_frame;
    resize(master.buffer_size);

    memcpy(raw_data, master.raw_data, buffer_size * sizeof(unsigned short));
    memcpy(cal_data, master.cal_data, buffer_size * sizeof(signed short));

    return *this;
}

BufferData::~BufferData()
{
    resize(0);
}
