#include "datareceiver.h"
#include <QDebug>
#include <cstring>

DataReceiver::DataReceiver(QObject *parent)
    : QObject(parent), dataBuffer(RECEIVER_BUFFER_SIZE)
{
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
    if (!dataSocket) {
        dataSocket = new QUdpSocket(this);
        connect(dataSocket, &QUdpSocket::readyRead, this, &DataReceiver::readData);
    }
    if (!timer) {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &DataReceiver::onTimer);
        timer->start(RECEIVER_TIMER_PERIOD_MS);
    }
    initSemaphore.release();
}

void DataReceiver::deinit()
{
    if (dataSocket) {
        delete dataSocket;
        dataSocket = nullptr;
    }
    if (timer) {
        delete timer;
        timer = nullptr;
    }
    initSemaphore.release();
}

void DataReceiver::configureEthSettings(QHostAddress address_to_set, quint16 port_to_set)
{
    address = address_to_set;
    port = port_to_set;
    if (dataSocket) {
        dataSocket->close();
        dataSocket->bind(address, port);
    }
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

void DataReceiver::readData()
{
    int size_received;
    while ((size_received = dataSocket->readDatagram(tmpBuffer, DATA_MAX_PACKET_SIZE)) > 0)
    {
        int expected_size = getExpectedPacketSize(sensorsPerBoard, dmaBunch, ethBunch);
        if (size_received != expected_size) {
            qWarning() << "Packet error: received" << size_received << "expected" << expected_size;
            continue;
        }
        for (int eth = 0; eth < ethBunch; eth++) {
            int base = eth * (DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE +
                              dmaBunch * getDataRawBlockSize(sensorsPerBoard) +
                              DATA_RMS_FRAME_SIZE);
            BufferData data_to_push(sensorsPerBoard * DATA_SAMPLES_PER_SENSOR);
            memcpy(&data_to_push.sync_frame, tmpBuffer + base + DATA_PACKET_HEADER_SIZE, DATA_SYNC_HEADER_SIZE);
            int raw_offset = base + DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE;
            memcpy(data_to_push.raw_data, tmpBuffer + raw_offset, sensorsPerBoard * DATA_SAMPLES_PER_SENSOR * DATA_BYTES_PER_SAMPLE);
            memcpy(&data_to_push.rms_frame, tmpBuffer + base + DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + dmaBunch * getDataRawBlockSize(sensorsPerBoard), DATA_RMS_FRAME_SIZE);
            if (outputEnabled)
                dataBuffer.push(data_to_push);
            framesReceived++;
            framesFromLastSig++;
        }
    }
    if (framesFromLastSig >= RECEIVER_FRAMES_PER_SIG) {
        framesFromLastSig = 0;
        emit sigDataReady(this);
    }
}

void DataReceiver::onTimer()
{
    frameRate = framesReceived * 1000 / RECEIVER_TIMER_PERIOD_MS;
    framesReceived = 0;
}
