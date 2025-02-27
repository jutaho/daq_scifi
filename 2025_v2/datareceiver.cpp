#include "datareceiver.h"
#include "dev_commands.h"
#include "helpers.h"
#include <iostream>

DataReceiver::DataReceiver(QObject *parent)
    : QObject(parent),
    dataBuffer(RECEIVER_BUFFER_SIZE)
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

//------------------------- readData() -----------------------------
// Here we process each UDP datagram. We now fill a BufferData object
// with both raw_data and calibration data. Note that the packet still
// carries only sensor values (raw data), so we default the calibration data.
void DataReceiver::readData()
{
    int size_received_bytes;
    // Read into tmpBuffer up to DATA_MAX_PACKET_SIZE to avoid overflow.
    while ((size_received_bytes = dataSocket->readDatagram(tmpBuffer, DATA_MAX_PACKET_SIZE)) > 0)
    {
        // Calculate expected packet size based on current settings.
        int expected_size_bytes = getExpectedPacketSize(sensorsPerBoard, dmaBunch, ethBunch);
        if (size_received_bytes != expected_size_bytes)
        {
            std::cout << "packet error. Got " << size_received_bytes
                      << " bytes, expected " << expected_size_bytes << " bytes" << std::endl;
            continue;
        }

        // Precompute the raw block size for convenience
        int raw_block_size = getDataRawBlockSize(sensorsPerBoard);

        // Process each ethBunch sub-packet (if ethBunch > 1)
        for (int ethb = 0; ethb < ethBunch; ethb++)
        {
            int baseaddr = ethb * (DATA_PACKET_HEADER_SIZE
                                   + DATA_SYNC_HEADER_SIZE
                                   + dmaBunch * raw_block_size
                                   + DATA_RMS_FRAME_SIZE);

            // Verify header
            if (BYTES2SHORT(tmpBuffer + baseaddr + 0) != 0x5555) // sync word
                continue;
            if (BYTES2SHORT(tmpBuffer + baseaddr + 2) != COMMAND_DATA_TRANSFER)
                continue;

            // Check if the reported length matches (in halfwords)
            if ((BYTES2SHORT(tmpBuffer + baseaddr + 4) * 2) != (DATA_SYNC_HEADER_SIZE + dmaBunch * raw_block_size))
                continue;

            // Read sync data
            SyncFrame sync;
            sync.local_ctr  = BYTES2SHORT(tmpBuffer + baseaddr + DATA_PACKET_HEADER_SIZE);
            sync.global_ctr = BYTES2SHORT(tmpBuffer + baseaddr + DATA_PACKET_HEADER_SIZE + 2);
            sync.sma_state  = BYTES2SHORT(tmpBuffer + baseaddr + DATA_PACKET_HEADER_SIZE + 4);
            sync.device_nr  = devNr;
            sync.data_ok    = 1;

            RMSFrame rms;

            // Process each DMA block within the packet
            for (int dmab = 0; dmab < dmaBunch; dmab++)
            {
                framesReceived++;
                int baseaddr2 = baseaddr + dmab * raw_block_size;
                if (outputEnabled)
                {
                    // Allocate a BufferData object with size = sensorsPerBoard * DATA_SAMPLES_PER_SENSOR
                    BufferData data_to_push(sensorsPerBoard * DATA_SAMPLES_PER_SENSOR);
                    data_to_push.sync_frame = sync;

                    int baseaddr3 = baseaddr2 + DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE;

                    // Loop over all samples: fill raw_data and set cal_data to default (zero)
                    for (int s = 0; s < (sensorsPerBoard * DATA_SAMPLES_PER_SENSOR); s++)
                    {
                        data_to_push.raw_data[s] = 65535 - BYTES2SHORT(tmpBuffer + baseaddr3 + 2 * s);
                        data_to_push.cal_data[s] = 0;  // Default calibration value; adjust if calibration is available
                    }

                    // Read the RMS frame (located after the data block)
                    int rms_base = baseaddr + DATA_PACKET_HEADER_SIZE
                                   + DATA_SYNC_HEADER_SIZE
                                   + dmaBunch * raw_block_size;
                    rms.mean   = BYTES2SHORT(tmpBuffer + rms_base);
                    rms.sigma  = BYTES2SHORT(tmpBuffer + rms_base + 2);
                    rms.max    = BYTES2SHORT(tmpBuffer + rms_base + 4);
                    rms.status = BYTES2SHORT(tmpBuffer + rms_base + 6);
                    data_to_push.rms_frame = rms;

                    dataBuffer.push(data_to_push);
                    framesFromLastSig++;
                }
            }
        }
    }

    // Emit sigDataReady every N frames
    if (framesFromLastSig >= RECEIVER_FRAMES_PER_SIG)
    {
        framesFromLastSig = 0;
        emit sigDataReady(this);
    }
}

//------------------------- Timer and Initialization Slots ------------------
void DataReceiver::onTimer()
{
    // Compute approximate frame rate
    frameRate = framesReceived * 1000 / RECEIVER_TIMER_PERIOD_MS;
    framesReceived = 0;
}

void DataReceiver::onInit()
{
    if (dataSocket == nullptr)
    {
        dataSocket = new QUdpSocket(this);
        connect(dataSocket, &QUdpSocket::readyRead, this, &DataReceiver::readData);
    }
    if (timer == nullptr)
    {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &DataReceiver::onTimer);
        timer->start(RECEIVER_TIMER_PERIOD_MS);
    }
    initSemaphore.release();
}

void DataReceiver::onDeinit()
{
    if (dataSocket != nullptr)
    {
        delete dataSocket;
        dataSocket = nullptr;
    }
    if (timer != nullptr)
    {
        delete timer;
        timer = nullptr;
    }
    initSemaphore.release();
}

void DataReceiver::onConfigureEthSettings()
{
    if (dataSocket)
    {
        dataSocket->close();
        dataSocket->bind(address, port);
    }
}

void DataReceiver::init()
{
    emit sigInit();
    initSemaphore.acquire();  // wait for initialization
}

void DataReceiver::deinit()
{
    emit sigDeinit();
    initSemaphore.acquire();  // wait for deinitialization
}

void DataReceiver::configureEthSettings(QHostAddress address_to_set, quint16 port_to_set)
{
    address = address_to_set;
    port    = port_to_set;
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
    if (!en)
        dataBuffer.clear();
}
