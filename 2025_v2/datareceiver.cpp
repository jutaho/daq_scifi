#include "datareceiver.h"
#include "dev_commands.h"
#include "helpers.h"
#include <iostream>

DataReceiver::DataReceiver(QObject *parent) : QObject(parent), dataBuffer(RECEIVER_BUFFER_SIZE)
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

//********************** Receiving data **************************



void DataReceiver::readData()
{
    int size_received_bytes;
    while ((size_received_bytes = dataSocket->readDatagram(tmpBuffer, DATA_PACKET_SIZE)) > 0)
    {
        //look if the packet isn't too short
        int expected_size_bytes = ethBunch * (DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + dmaBunch*DATA_BLOCK_SIZE + DATA_RMS_FRAME_SIZE);
        if (size_received_bytes != expected_size_bytes)
        {
            std::cout << "packet error. Got" << size_received_bytes << " bytes expected" << expected_size_bytes << std::endl;
            continue;
        }
        for (int ethb = 0; ethb < ethBunch; ethb++)
        {
            int baseaddr = ethb * (DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + dmaBunch*DATA_BLOCK_SIZE + DATA_RMS_FRAME_SIZE);

                //check the header
            if (BYTES2SHORT(tmpBuffer+baseaddr+0) != 0x5555)
                continue;
            if (BYTES2SHORT(tmpBuffer+baseaddr+2) != COMMAND_DATA_TRANSFER)
                continue;
            if ((BYTES2SHORT(tmpBuffer+baseaddr+4)*2) != (DATA_SYNC_HEADER_SIZE + dmaBunch*DATA_BLOCK_SIZE))
                continue;

                //read sync data;
            SyncFrame sync;
            sync.local_ctr = BYTES2SHORT(tmpBuffer+baseaddr+DATA_PACKET_HEADER_SIZE);
            sync.global_ctr = BYTES2SHORT(tmpBuffer+baseaddr+DATA_PACKET_HEADER_SIZE+2);
            sync.sma_state = BYTES2SHORT(tmpBuffer+baseaddr+DATA_PACKET_HEADER_SIZE+4);
            sync.device_nr = devNr;
            sync.data_ok = 1;

            RMSFrame rms;

            for (int dmab=0; dmab<dmaBunch; dmab++)
            {
                framesReceived++;
                int baseaddr2 = baseaddr + dmab*DATA_BLOCK_SIZE;

                if (outputEnabled)
                {
                    BufferData data_to_push(sensorsPerBoard * DATA_SAMPLES_PER_SENSOR);
                    data_to_push.sync_frame = sync;
                    int baseaddr3 = baseaddr2 + DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE;

                    for (int s = 0; s < (sensorsPerBoard * DATA_SAMPLES_PER_SENSOR); s++)
                        data_to_push.sensor_data[s] = 65535 - BYTES2SHORT(tmpBuffer + baseaddr3 + 2*s);

                    rms.mean = BYTES2SHORT(tmpBuffer+baseaddr+DATA_PACKET_HEADER_SIZE+DATA_SYNC_HEADER_SIZE+DATA_BLOCK_SIZE);
                    rms.sigma = BYTES2SHORT(tmpBuffer+baseaddr+DATA_PACKET_HEADER_SIZE+DATA_SYNC_HEADER_SIZE+DATA_BLOCK_SIZE + 2);
                    rms.max = BYTES2SHORT(tmpBuffer+baseaddr+DATA_PACKET_HEADER_SIZE+DATA_SYNC_HEADER_SIZE+DATA_BLOCK_SIZE + 4);
                    rms.status = BYTES2SHORT(tmpBuffer+baseaddr+DATA_PACKET_HEADER_SIZE+DATA_SYNC_HEADER_SIZE+DATA_BLOCK_SIZE + 6);
                    data_to_push.rms_frame = rms;

                    dataBuffer.push(data_to_push);
                    framesFromLastSig++;
                }
            }
        }
    }

    if (framesFromLastSig >= RECEIVER_FRAMES_PER_SIG)
    {
        framesFromLastSig = 0;
        emit sigDataReady(this);
    }
}

//********************** Internal slots ************************

void DataReceiver::onTimer()
{
    frameRate = framesReceived * 1000 / RECEIVER_TIMER_PERIOD_MS;
    framesReceived = 0;
}

void DataReceiver::onInit()
{
    if (dataSocket == NULL)
    {
        dataSocket = new QUdpSocket(this);
        connect(dataSocket, &QUdpSocket::readyRead, this, &DataReceiver::readData);
    }

    if (timer == NULL)
    {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &DataReceiver::onTimer);
        timer->start(RECEIVER_TIMER_PERIOD_MS);
    }

    initSemaphore.release();
}

void DataReceiver::onDeinit()
{
    if (dataSocket != NULL)
    {
        delete dataSocket;
        dataSocket = NULL;
    }
    if (timer != NULL)
    {
        delete timer;
        timer = NULL;
    }

    initSemaphore.release();
}

void DataReceiver::onConfigureEthSettings()
{
    dataSocket->close();
    dataSocket->bind(address, port);
}

//********************** Controlling  DataReceiver************************

void DataReceiver::init()
{
    emit sigInit();
    initSemaphore.acquire();    //wait for initialization
}

void DataReceiver::deinit()
{
    emit sigDeinit();
    initSemaphore.acquire();    //wait for deinitialization
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

void DataReceiver::outputEnable (int en)
{
    outputEnabled = en;
    if (!en)
        dataBuffer.clear();
}
