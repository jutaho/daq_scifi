#include "eventbuilder.h"
#include <QTime>
#include <climits>
#include <iostream>

EventBuilder::EventBuilder(QObject *parent) : QObject(parent) {
    connect(this, &EventBuilder::sigInit, this, &EventBuilder::onInit);
    connect(this, &EventBuilder::sigDeinit, this, &EventBuilder::onDeinit);
    connect(this, &EventBuilder::sigStartLogging, this, &EventBuilder::onStartLogging);
    connect(this, &EventBuilder::sigStopLogging, this, &EventBuilder::onStopLogging);

    moveToThread(&thread);
    thread.start();
    init();
}

EventBuilder::~EventBuilder() {
    deinit();
    thread.quit();
    thread.wait();
}

void EventBuilder::onNewData(DataReceiver* receiver) {
    while (checkBufferOccupancies()) {
        int lowest_id = findLowestId();

        for (int dev_nr = 0; dev_nr < nrReceivers; dev_nr++) {
            BufferData data = receivers[dev_nr]->dataBuffer.look();
            if (data.sync_frame.global_ctr == lowest_id) {
                receivers[dev_nr]->dataBuffer.dump();
            } else {
                data.sync_frame.data_ok = 0;
            }

            currentFrame[dev_nr] = data;
            processFrameData(currentFrame[dev_nr]);
        }

        lastFrameMutex.lock();
        if (newDataSemaphore.available() == 1)
            frame_counter++;

        if (newDataSemaphore.available() == 0)
            newDataSemaphore.release(1);

        lastFrame = currentFrame;
        lastFrameMutex.unlock();

        if (loggingData)
            logDataToFile();
    }
}

void EventBuilder::processFrameData(BufferData &data) {
    if (data.buffer_size > 0) {
        //std::cout << "Raw data[0]: " << data.raw_data[0]
        //          << ", Cal data[0]: " << data.cal_data[0] << std::endl;
    }
}

int EventBuilder::checkBufferOccupancies() {
    for (int dev_nr = 0; dev_nr < nrReceivers; dev_nr++) {
        if (receivers[dev_nr]->dataBuffer.nrItems() > EVB_MAX_BUFFER_OCCUPANCY)
            return 1;
        if (receivers[dev_nr]->dataBuffer.nrItems() < EVB_MIN_BUFFER_OCCUPANCY)
            return 0;
    }
    return 1;
}

int EventBuilder::findLowestId() {
    int min_id = INT_MAX;
    for (int dev_nr = 0; dev_nr < nrReceivers; dev_nr++) {
        int value = receivers[dev_nr]->dataBuffer.look().sync_frame.global_ctr;
        if (value < min_id) min_id = value;
    }
    return min_id;
}

void EventBuilder::logDataToFile() {
    logFile.write(reinterpret_cast<const char*>(&totalBoards), sizeof(unsigned short));
    logFile.write(reinterpret_cast<const char*>(channelCounts.constData()), totalBoards * sizeof(unsigned short));

    for (int board = 0; board < totalBoards; board++) {
        logFile.write(reinterpret_cast<const char*>(&(currentFrame[board].sync_frame)), sizeof(SyncFrame));
        logFile.write(reinterpret_cast<const char*>(currentFrame[board].raw_data),
                      currentFrame[board].buffer_size * sizeof(unsigned short));
        logFile.write(reinterpret_cast<const char*>(currentFrame[board].cal_data),
                      currentFrame[board].buffer_size * sizeof(signed short));
        logFile.write(reinterpret_cast<const char*>(&(currentFrame[board].rms_frame)), sizeof(RMSFrame));
    }
}

void EventBuilder::onInit() {
    initSemaphore.release();
}

void EventBuilder::onDeinit() {
    initSemaphore.release();
}

void EventBuilder::onStartLogging() {
    if (loggingData) onStopLogging();

    logFile.setFileName(logFileName);
    logFile.open(QIODevice::WriteOnly);
    loggingData = 1;
}

void EventBuilder::onStopLogging() {
    loggingData = 0;
    logFile.close();
}

void EventBuilder::init() {
    emit sigInit();
    initSemaphore.acquire();
}

void EventBuilder::deinit() {
    emit sigDeinit();
    initSemaphore.acquire();
}

void EventBuilder::addSource(DataReceiver* source) {
    receivers.append(source);
    nrReceivers = receivers.size();
    currentFrame.resize(nrReceivers);
    backgroundFrame.resize(nrReceivers);
    connect(source, &DataReceiver::sigDataReady, this, &EventBuilder::onNewData);
}

void EventBuilder::deleteSources() {
    receivers.clear();
    nrReceivers = 0;
}

int EventBuilder::isLogging() { return loggingData; }

QVector<BufferData> EventBuilder::getLastFrame() {
    QMutexLocker locker(&lastFrameMutex);
    return lastFrame;
}

QVector<BufferData> EventBuilder::getNewFrame() {
    newDataSemaphore.acquire(1);
    return getLastFrame();
}

void EventBuilder::startLogging(QString filename) {
    logFileName = filename;
    emit sigStartLogging();
}

void EventBuilder::stopLogging() { emit sigStopLogging(); }

void EventBuilder::setChannelCount(int sensor_nr, int nr_channels) {
    std::cout << "HERE I AM" <<std::endl;
    if (sensor_nr >= 0 && sensor_nr < channelCounts.size()) {
        channelCounts[sensor_nr] = nr_channels;
    } else {
        qDebug() << "ERROR: setChannelCount() out of bounds! sensor_nr:" << sensor_nr << ", size:" << channelCounts.size();
    }
}


QByteArray EventBuilder::getNextData() {
    QMutexLocker locker(&mutex);
    if (dataQueue.isEmpty())
        return QByteArray();
    return dataQueue.dequeue();
}
