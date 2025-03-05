#include "datareceiver.h"
#include "dev_commands.h"
#include "helpers.h"
#include <iostream>
#include <fstream>

// Constructor
DataReceiver::DataReceiver(QObject *parent)
    : QObject(parent), dataBuffer(RECEIVER_BUFFER_SIZE)
{
    connect(this, &DataReceiver::sigInit, this, &DataReceiver::onInit);
    connect(this, &DataReceiver::sigDeinit, this, &DataReceiver::onDeinit);
    connect(this, &DataReceiver::sigConfigureEthSettings, this, &DataReceiver::onConfigureEthSettings);

    moveToThread(&thread);
    thread.start();
    init();
}


std::ofstream rawDataFile("raw_values_first_frame.txt", std::ios::out);

// Receiving Data
void DataReceiver::readData()
{

    int size_received_bytes;


    while ((size_received_bytes = dataSocket->readDatagram(tmpBuffer, DATA_PACKET_SIZE)) > 0)

    {

        int expected_size_bytes = ethBunch * (DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + dmaBunch * DATA_BLOCK_SIZE + DATA_RMS_FRAME_SIZE);

        if (size_received_bytes != expected_size_bytes)
        {
            std::cout << "Packet error. Got " << size_received_bytes << " bytes, expected " << expected_size_bytes << std::endl;
            continue;
        }


        for (int ethb = 0; ethb < ethBunch; ethb++)
        {

            // Check data size per frame
            int baseaddr = ethb * (DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + dmaBunch * DATA_BLOCK_SIZE + DATA_RMS_FRAME_SIZE);

            // Check reference byte = 0x5555
            if (BYTES2SHORT(tmpBuffer + baseaddr + 0) != 0x5555)
                continue;

            // Check data command transfer byte
            if (BYTES2SHORT(tmpBuffer + baseaddr + 2) != COMMAND_DATA_TRANSFER)
                continue;

            // Check Header + Data
            if ((BYTES2SHORT(tmpBuffer + baseaddr + 4) * 4) != (DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + dmaBunch * DATA_BLOCK_SIZE))
               continue;

            // Read sync data
            SyncFrame sync;
            sync.local_ctr = BYTES2SHORT(tmpBuffer + baseaddr + DATA_PACKET_HEADER_SIZE);
            sync.global_ctr = BYTES2SHORT(tmpBuffer + baseaddr + DATA_PACKET_HEADER_SIZE + 2);
            sync.sma_state = BYTES2SHORT(tmpBuffer + baseaddr + DATA_PACKET_HEADER_SIZE + 4);
            sync.device_nr = devNr;


            sync.data_ok = 1;

            RMSFrame rms;

            for (int dmab = 0; dmab < dmaBunch; dmab++)
            {

                framesReceived++;

                int baseaddr2 = baseaddr + dmab * DATA_BLOCK_SIZE;

                if (outputEnabled)

                {
                    BufferData data_to_push(sensorsPerBoard * DATA_SAMPLES_PER_SENSOR);
                    data_to_push.sync_frame = sync;
                    int baseaddr3 = baseaddr2 + DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE;


                    // Iterating over the number of "words"

                    for (int wordIndex = 0; wordIndex < sensorsPerBoard * DATA_SAMPLES_PER_SENSOR; wordIndex++)
                    {
                        int channelIndex = (wordIndex / 2) * 2;


                        if (wordIndex % 2 == 0)
                        {
                            data_to_push.raw_data[channelIndex] = 65535 - BYTES2SHORT(tmpBuffer + baseaddr3 + wordIndex * 4);
                            data_to_push.raw_data[channelIndex + 1] = 65535 - BYTES2SHORT(tmpBuffer + baseaddr3 + wordIndex * 4 + 2);
                        }

                        else

                        {
                        // Read calibrated values (from even words)
                            data_to_push.cal_data[channelIndex]     = 65535 - BYTES2SHORT(tmpBuffer + baseaddr3 + wordIndex * 4);
                            data_to_push.cal_data[channelIndex + 1] = 65535 - BYTES2SHORT(tmpBuffer + baseaddr3 + wordIndex * 4 + 2);
                        }
                    }

                    // Read RMS frame
                    rms.mean = BYTES2SHORT(tmpBuffer + baseaddr + DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + DATA_BLOCK_SIZE);
                    rms.sigma = BYTES2SHORT(tmpBuffer + baseaddr + DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + DATA_BLOCK_SIZE + 2);
                    rms.max = BYTES2SHORT(tmpBuffer + baseaddr + DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + DATA_BLOCK_SIZE + 4);
                    rms.status = BYTES2SHORT(tmpBuffer + baseaddr + DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + DATA_BLOCK_SIZE + 6);
                    data_to_push.rms_frame = rms;

                    // Push data to buffer
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

// Destructor
DataReceiver::~DataReceiver()
{
    deinit();
    thread.quit();
    thread.wait();
    rawDataFile.close();
}

// Timer function for frame rate calculation
void DataReceiver::onTimer()
{
    frameRate = framesReceived * 1000 / RECEIVER_TIMER_PERIOD_MS;
    framesReceived = 0;
}

// Initialization and Deinitialization
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

// Configuring Ethernet settings
void DataReceiver::configureEthSettings(QHostAddress address_to_set, quint16 port_to_set)
{
    address = address_to_set;
    port = port_to_set;
    emit sigConfigureEthSettings();
}

// Configuring Bunch Sizes
void DataReceiver::configureBunchSize(int dma, int eth)
{
    dmaBunch = dma;
    ethBunch = eth;
}

// Output enable/disable
void DataReceiver::outputEnable(int en)
{
    //std::cout << "Output enabled with:  " << en << std::endl;
    outputEnabled = en;
    if (!en)
        dataBuffer.clear();
}

// Initialization and Deinitialization logic
void DataReceiver::init()
{
    emit sigInit();
    initSemaphore.acquire();  // Wait for initialization
}

void DataReceiver::deinit()
{
    emit sigDeinit();
    initSemaphore.acquire();  // Wait for deinitialization
}
