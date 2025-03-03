#ifndef EVENTBUILDER_H
#define EVENTBUILDER_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QThread>
#include <QMutex>
#include <QSemaphore>
#include <QQueue>
#include "datareceiver.h"

#define EVB_MIN_BUFFER_OCCUPANCY    (RECEIVER_BUFFER_SIZE / 8)
#define EVB_MAX_BUFFER_OCCUPANCY    (RECEIVER_BUFFER_SIZE / 2)

class EventBuilder : public QObject {
    Q_OBJECT

public:
    explicit EventBuilder(QObject *parent = nullptr);
    ~EventBuilder();

    void addSource(DataReceiver *source);
    void deleteSources();

    void startLogging(QString filename);
    void stopLogging();
    int isLogging();

    QVector<BufferData> getLastFrame();
    QVector<BufferData> getNewFrame();

    void setChannelCount(int sensor_nr, int nr_channels);
    QByteArray getNextData();

signals:
    void sigInit();
    void sigDeinit();
    void sigStartLogging();
    void sigStopLogging();

public slots:
    void onNewData(DataReceiver *receiver);

protected:
    int checkBufferOccupancies();
    int findLowestId();
    void logDataToFile();
    void processFrameData(BufferData &data);

    void init();
    void deinit();

    QThread thread;
    QSemaphore initSemaphore;

    QVector<DataReceiver*> receivers;

    QVector<BufferData> currentFrame;
    QVector<BufferData> backgroundFrame;
    QVector<BufferData> lastFrame;

    QVector<unsigned short> channelCounts;
    unsigned short totalChannels;
    unsigned short totalBoards;

    QMutex lastFrameMutex;
    QSemaphore newDataSemaphore;
    int nrReceivers;

    QString logFileName;
    QFile logFile;
    int loggingData = 0;

private:
    long long frame_counter = 0;
    QQueue<QByteArray> dataQueue;
    QMutex mutex;

protected slots:
    void onInit();
    void onDeinit();
    void onStartLogging();
    void onStopLogging();
};

#endif // EVENTBUILDER_H
