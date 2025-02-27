#include "eventbuilder.h"
#include <QTime>
#include <climits>
#include <iostream>

EventBuilder::EventBuilder(QObject *parent) : QObject(parent)
{
    connect(this, &EventBuilder::sigInit, this, &EventBuilder::onInit);
    connect(this, &EventBuilder::sigDeinit, this, &EventBuilder::onDeinit);
    connect(this, &EventBuilder::sigStartLogging, this, &EventBuilder::onStartLogging);
    connect(this, &EventBuilder::sigStopLogging, this, &EventBuilder::onStopLogging);

    moveToThread(&thread);
    thread.start();
    init();
    // Network thread setup, if needed, goes here.
}

EventBuilder::~EventBuilder()
{
    deinit();
    thread.quit();
    thread.wait();
    // Optionally wait for network thread to finish.
}

//************************* Data Processing Framework ********************

void EventBuilder::onNewData(DataReceiver* receiver)
{
    // Temporary copy buffer (size chosen arbitrarily, adjust as needed)
    short * newcopy_sensor_data = new short[320];

    while (checkBufferOccupancies())
    {
        // Find the lowest global sync counter among devices
        int lowest_id = findLowestId();

        // Retrieve and validate data from each device buffer
        for (int dev_nr = 0; dev_nr < nrReceivers; dev_nr++)
        {
            BufferData data = receivers[dev_nr]->dataBuffer.look();
            if (data.sync_frame.global_ctr == lowest_id)
            {
                receivers[dev_nr]->dataBuffer.dump();  // Correct data; remove it from the buffer.
            }
            else
            {
                data.sync_frame.data_ok = 0;            // Incorrect data; mark as bad.
            }
            // Store the data for the complete frame.
            currentFrame[dev_nr] = data;
        }
        lastFrameMutex.lock();

        // ************ TODO ************
        // Here you can add further processing (background subtraction, position/focus calculation, etc.)
        if (newDataSemaphore.available() == 1)
        {
            frame_counter++;

            if (frame_counter <= 32)
            {
                for (unsigned int dev_nr = 0; dev_nr < nrReceivers; dev_nr++)
                {
                    if (frame_counter <= 1)
                        backgroundFrame[dev_nr].resize(channelCounts[dev_nr]);
                    // Example (commented out): copy raw_data into backgroundFrame
                    // backgroundFrame[dev_nr].raw_data = currentFrame[dev_nr].raw_data;
                    // addArrays(backgroundFrame[dev_nr].raw_data, currentFrame[dev_nr].raw_data, channelCounts[dev_nr]);
                    // std::cerr << "Setting background" << std::endl;
                }
            }
            else if (frame_counter == 33)
            {
                for (unsigned int dev_nr = 0; dev_nr < nrReceivers; dev_nr++)
                {
                    for (int i = 0; i < channelCounts[dev_nr]; ++i)
                    {
                        // Example: Finalize background by averaging over 32 frames
                        // backgroundFrame[dev_nr].raw_data[i] /= 32;
                    }
                }
            }
            else if (frame_counter > 33)
            {
                // Example: Process currentFrame with background subtraction
                QString dataString;
                for (unsigned int dev_nr = 0; dev_nr < nrReceivers; dev_nr++)
                {
                    // subtractArrays(currentFrame[dev_nr].raw_data, backgroundFrame[dev_nr].raw_data,
                    //                 channelCounts[dev_nr], newcopy_sensor_data);
                    // std::cerr << currentFrame[dev_nr].raw_data[0] << " " << backgroundFrame[dev_nr].raw_data[0]
                    //           << " " << channelCounts[dev_nr] << " " << newcopy_sensor_data[0] << std::endl;
                    // dataString += hit_analyse_v2.analyseBeamData(newcopy_sensor_data, dev_nr, channelCounts[dev_nr]);
                }
                // Optionally print or transmit the dataString.
            }
        }

        if (newDataSemaphore.available() == 0)
            newDataSemaphore.release(1);
        lastFrame = currentFrame;
        lastFrameMutex.unlock();

        // Log data to file if logging is enabled.
        if (loggingData)
            logDataToFile();
    }
    delete[] newcopy_sensor_data;
}

// Returns 1 if buffer occupancy is high enough to force data processing.
int EventBuilder::checkBufferOccupancies()
{
    int result = 1;
    for (int dev_nr = 0; dev_nr < nrReceivers; dev_nr++)
    {
        int nr_items = receivers[dev_nr]->dataBuffer.nrItems();
        if (nr_items > EVB_MAX_BUFFER_OCCUPANCY)
            return 1;   // At least one buffer exceeds the high threshold.
        if (nr_items < EVB_MIN_BUFFER_OCCUPANCY)
            result = 0;
    }
    return result;
}

int EventBuilder::findLowestId()
{
    int min1 = INT_MAX, min2 = INT_MAX;
    int max1 = INT_MIN, max2 = INT_MIN;

    for (int dev_nr = 0; dev_nr < nrReceivers; dev_nr++)
    {
        int value = receivers[dev_nr]->dataBuffer.look().sync_frame.global_ctr;
        // For non-zero-crossing case:
        if (value < min1) min1 = value;
        if (value > max1) max1 = value;
        // For zero-crossing case:
        if (value > 256) value -= 512;
        if (value < min2) min2 = value;
        if (value > max2) max2 = value;
    }
    if ((max1 - min1) < (max2 - min2))
    {
        // Non-zero-crossing case.
        return min1;
    }
    else
    {
        // Zero-crossing case.
        if (min2 < 0) min2 += 512;
        return min2;
    }
}

void EventBuilder::logDataToFile()
{
    /*
     * Write data in binary format:
     * - Number of boards: 1 unsigned short
     * - Number of channels per board: totalBoards unsigned shorts
     * For each board:
     *   - SyncFrame (16 bytes)
     *   - Raw data: (buffer_size * unsigned short)
     *   - RMSFrame (16 bytes)
     */
    logFile.write((const char*)&totalBoards, sizeof(unsigned short));
    logFile.write((const char*)channelCounts.constData(), totalBoards * sizeof(unsigned short));

    for (int board = 0; board < totalBoards; board++)
    {
        logFile.write((const char*)&(currentFrame[board].sync_frame), sizeof(SyncFrame));
        // Use raw_data instead of the removed sensor_data member.
        logFile.write((const char*)currentFrame[board].raw_data, currentFrame[board].buffer_size * sizeof(unsigned short));
        logFile.write((const char*)&(currentFrame[board].rms_frame), sizeof(RMSFrame));
    }
    // Optionally, write the complete native binary format of currentFrame.
    // logFile.write((const char*)currentFrame.constData(), nrReceivers * sizeof(BufferData));
}

void EventBuilder::recalculateChannels()
{
    totalBoards = baseAddresses.count();

    if (totalBoards == 0)
        return;
    for (int i = 1; i < totalBoards; i++)
        baseAddresses[i] = baseAddresses[i - 1] + channelCounts[i - 1];

    totalChannels = 0;
    for (int i = 0; i < channelCounts.count(); i++)
        totalChannels += channelCounts[i];
}

void EventBuilder::setChannelCount(int sensor_nr, int nr_channels)
{
    channelCounts[sensor_nr] = nr_channels;
    recalculateChannels();
}

//************************* Protected Slots ****************************

void EventBuilder::onInit()
{
    // Any additional initialization can be added here.
    initSemaphore.release();
}

void EventBuilder::onDeinit()
{
    // Any additional deinitialization can be added here.
    initSemaphore.release();
}

void EventBuilder::onStartLogging()
{
    if (loggingData)
        onStopLogging();

    logFile.setFileName(logFileName);
    logFile.open(QIODevice::WriteOnly);
    loggingData = 1;
}

void EventBuilder::onStopLogging()
{
    loggingData = 0;
    logFile.close();
}

//******************** Thread-Safe Interface *******************

void EventBuilder::init()
{
    emit sigInit();
    initSemaphore.acquire();    // Wait for initialization.
}

void EventBuilder::deinit()
{
    emit sigDeinit();
    initSemaphore.acquire();    // Wait for deinitialization.
}

void EventBuilder::addSource(DataReceiver* source)
{
    baseAddresses.push_back(0);
    channelCounts.push_back(0);

    receivers.append(source);
    nrReceivers = receivers.length();
    currentFrame.resize(nrReceivers);
    backgroundFrame.resize(nrReceivers);
    connect(source, &DataReceiver::sigDataReady, this, &EventBuilder::onNewData);
}

void EventBuilder::deleteSources()
{
    for (int i = 0; i < receivers.length(); i++)
        disconnect(receivers[i], &DataReceiver::sigDataReady, this, &EventBuilder::onNewData);

    receivers.clear();
    nrReceivers = receivers.length();

    baseAddresses.clear();
    channelCounts.clear();
}

void EventBuilder::startLogging(QString filename)
{
    logFileName = filename;
    emit sigStartLogging();
}

void EventBuilder::stopLogging()
{
    emit sigStopLogging();
}

int EventBuilder::isLogging()
{
    return loggingData;
}

QVector<BufferData> EventBuilder::getLastFrame()
{
    QMutexLocker locker(&lastFrameMutex);
    return lastFrame;
}

QVector<BufferData> EventBuilder::getNewFrame()
{
    newDataSemaphore.acquire(1);
    return getLastFrame();
}

void EventBuilder::receiveData(const QByteArray &data)
{
    QMutexLocker locker(&mutex);
    dataQueue.enqueue(data);
    // Optionally, process data or wake a waiting thread.
    dataAvailable.wakeOne();
}

QByteArray EventBuilder::getNextData()
{
    QMutexLocker locker(&mutex);
    if (dataQueue.isEmpty())
        return QByteArray(); // Return an empty QByteArray if no data is available.
    return dataQueue.dequeue();
}
