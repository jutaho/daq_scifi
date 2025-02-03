#include "eventbuilder.h"

#include <QTime>
EventBuilder::EventBuilder( QObject *parent) : QObject(parent)
{
    connect(this, &EventBuilder::sigInit, this, &EventBuilder::onInit);
    connect(this, &EventBuilder::sigDeinit, this, &EventBuilder::onDeinit);
    connect(this, &EventBuilder::sigStartLogging, this, &EventBuilder::onStartLogging);
    connect(this, &EventBuilder::sigStopLogging, this, &EventBuilder::onStopLogging);

    moveToThread(&thread);
    thread.start();
    init();
    //get the network thread
}

EventBuilder::~EventBuilder()
{
    deinit();

    thread.quit();
    thread.wait();
    //  networkThread.stopThread();
    // networkThread.wait(); // Wait for the network thread to finish gracefully
}




//************************* Data processing framework ********************

//main processing slot
void EventBuilder::onNewData(DataReceiver* receiver)
{
    short * newcopy_sensor_data  = new short int[320];
    while (checkBufferOccupancies())
    {
        //find lowest global sync value
        int lowest_id = findLowestId();

        //get and validate data from buffers
        for (int dev_nr = 0; dev_nr < nrReceivers; dev_nr++)
        {
            BufferData data = receivers[dev_nr]->dataBuffer.look();
            if (data.sync_frame.global_ctr == lowest_id)
            {
                receivers[dev_nr]->dataBuffer.dump();  //right data, dump it from the buffer
            }
            else
            {
                data.sync_frame.data_ok = 0;            //wrong data, mark as bad
            }
            //store data for complete frame
            currentFrame[dev_nr] = data;

        }
        lastFrameMutex.lock();



        //************ TODO ************
        //Here we can do something more with the complete frame
        // I probably want to find the position and focus with the linear regression algorithm, but first, just send data to the udpserver to test.
        //ToDo:
        //1. Background subtraction.

        if (newDataSemaphore.available() == 1){
            frame_counter++;

            if (frame_counter<=32){
                for (unsigned int dev_nr = 0; dev_nr < nrReceivers; dev_nr++){
                    if (frame_counter<=1)  backgroundFrame[dev_nr].resize(channelCounts[dev_nr]);
                  //  backgroundFrame[dev_nr].sensor_data =  currentFrame[dev_nr].sensor_data;
                 //   addArrays(backgroundFrame[dev_nr].sensor_data, currentFrame[dev_nr].sensor_data, channelCounts[dev_nr]);

                  //  std::cerr << " set bkg" << std::endl;
                }
            }
            else if (frame_counter==33){
                for (unsigned int dev_nr = 0; dev_nr < nrReceivers; dev_nr++){
                    for (int i = 0; i < channelCounts[dev_nr]; ++i) {
                   //     backgroundFrame[dev_nr].sensor_data[i] /= 32; // Right-shift by 5 positions (equivalent to dividing by 32)
                    }
                }
            }

            else if (frame_counter>33){
                //HIT_ANALYSE_V2 hit_analyse_v2;//create the object
                QString dataString;
                for (unsigned int dev_nr = 0; dev_nr < nrReceivers; dev_nr++){
                 //   subtractArrays(currentFrame[dev_nr].sensor_data, backgroundFrame[dev_nr].sensor_data, channelCounts[dev_nr], newcopy_sensor_data  );
                  //  std::cerr << currentFrame[dev_nr].sensor_data[0] << " " << backgroundFrame[dev_nr].sensor_data[0] << " " << channelCounts[dev_nr] << " " <<  newcopy_sensor_data[0] << std::endl;


                    //  for (unsigned int dev_nrsim = 0; dev_nrsim < 3; dev_nrsim++){
                    //simulate 6 planes instead of just 2
                  //  for (unsigned int dev_nr = 0; dev_nr < nrReceivers; dev_nr++){

                 //  dataString += hit_analyse_v2.analyseBeamData(newcopy_sensor_data, dev_nr, channelCounts[dev_nr]);
                   // dataString += char(nrReceivers);
                    //}
                     //   if (frame_counter%1000==0) std::cerr << dataString.toStdString() << std::endl;
                }
            }
        }
            /*
        //histogram stuff
        if (histogramSamplesToTake)
        {
            for (int dev_nr = 0; dev_nr < nrReceivers; dev_nr++)
                for (int ch = 0; ch < channelCounts[dev_nr]; ch++)
                histograms[baseAddresses[dev_nr] + ch].shoot(currentFrame[dev_nr].sensor_data[ch]);

            if (histogramSamplesToTake != -1)
                histogramSamplesToTake--;
            if (histogramSamplesToTake == 0)
                emit sigHistoCompleted();
        }
*/



            // }
           // QTime currentTime = QTime::currentTime();
                //Calculate the time since midnight in milliseconds
           // int millisecondsSinceMidnight = currentTime.msecsSinceStartOfDay();
           // dataString += QString::number(millisecondsSinceMidnight);
           // receiveData(dataString.toUtf8());

        if (newDataSemaphore.available() == 0)
            newDataSemaphore.release(1);
        lastFrame = currentFrame;
        lastFrameMutex.unlock();


            //log data
            if (loggingData) logDataToFile();



    }

}

//return 1 if buffer levels allow/force data processing
int EventBuilder::checkBufferOccupancies()
{
    int result = 1;
    for (int dev_nr = 0; dev_nr < nrReceivers; dev_nr++)
    {
        int nr_items = receivers[dev_nr]->dataBuffer.nrItems();
        if (nr_items > EVB_MAX_BUFFER_OCCUPANCY)
            return 1;   //if at least one buffer is above high threshold - return immediately
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
            //for non-zero-crossing case
        if (value < min1) min1 = value;
        if (value > max1) max1 = value;
        //for zero-crossing case
        if (value > 256) value -= 512;
        if (value < min2) min2 = value;
        if (value > max2) max2 = value;
    }
    if ((max1-min1) < (max2-min2))
    {
        //non-zero-crossing
        return min1;
    }
    else
    {
        //zero-crossing
        if (min2 < 0) min2 += 512;
        return min2;
    }
}

void EventBuilder::logDataToFile()
{
    /*
     * Write data in binary format:
     * - number of boards: N = 1 x unsigned short
     * - number of channels per each board Cn: N x unsigned short
     * - N times the following sequence:
     *   - SyncFrame S = 1 x SyncFrame (== 16 bytes)
     *   - Data D = Cn x unsigned short
     */

    logFile.write((const char*)&totalBoards, sizeof(unsigned short));
    logFile.write((const char*)channelCounts.constData(), totalBoards * sizeof(unsigned short));

    for (int board = 0; board < totalBoards; board++)
    {
        logFile.write((const char*)&(currentFrame[board].sync_frame), sizeof(SyncFrame));
        logFile.write((const char*)currentFrame[board].sensor_data, currentFrame[board].buffer_size*sizeof(unsigned short));
        logFile.write((const char*)&(currentFrame[board].rms_frame), sizeof(RMSFrame));

    }

    //write data in native binary format. All devices written as 5-sensor-wide!
    //logFile.write((const char*)currentFrame.constData(), nrReceivers*sizeof(BufferData));
}


void EventBuilder::recalculateChannels()
{
    totalBoards = baseAddresses.count();

    if (totalBoards == 0)
        return;
    for (int i = 1; i < totalBoards; i++)
        baseAddresses[i] = baseAddresses[i-1] + channelCounts[i-1];

    totalChannels = 0;
    for (int i = 0; i < channelCounts.count(); i++)
        totalChannels += channelCounts[i];
}

void EventBuilder::setChannelCount(int sensor_nr, int nr_channels)
{
    channelCounts[sensor_nr] = nr_channels;
    recalculateChannels();
}

//************************* Protected slots ********************

void EventBuilder::onInit()
{
    //Still nothing? Strange...

    initSemaphore.release();
}

void EventBuilder::onDeinit()
{
    //Still nothing? Strange...

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


//******************** Thread-safe interface *******************

void EventBuilder::init()
{
    emit sigInit();
    initSemaphore.acquire();    //wait for initialization
}

void EventBuilder::deinit()
{
    emit sigDeinit();
    initSemaphore.acquire();    //wait for deinitialization
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
    //wait for new data
    newDataSemaphore.acquire(1);
        //and return it
    return getLastFrame();
}

void EventBuilder::receiveData(const QByteArray &data)
{
    QMutexLocker locker(&mutex);
    dataQueue.enqueue(data);
    QString dataString = QString(data);
    //   std::cerr << dataString.toStdString() << std::endl;

    dataAvailable.wakeOne();
}

QByteArray EventBuilder::getNextData()
{
    QMutexLocker locker(&mutex);
    if (dataQueue.isEmpty())
        return QByteArray(); // Return an empty QByteArray if no data is available
    return dataQueue.dequeue();
}
