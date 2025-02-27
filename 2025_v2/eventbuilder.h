#ifndef EVENTBUILDER_H
#define EVENTBUILDER_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QFile>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QQueue>
#include <QWaitCondition>
#include "datareceiver.h"
#include <immintrin.h> // Intel Intrinsics
#include <emmintrin.h> // SSE2

// The event builder will constantly keep some data in the buffers to enable synchronization of the devices.
#define EVB_MIN_BUFFER_OCCUPANCY    (RECEIVER_BUFFER_SIZE / 8)      // Wait until each device buffer has this many items.
#define EVB_MAX_BUFFER_OCCUPANCY    (RECEIVER_BUFFER_SIZE / 2)      // Or when at least one reaches this threshold.

class EventBuilder : public QObject
{
    Q_OBJECT
public:
    explicit EventBuilder(QObject *parent = 0);
    ~EventBuilder();

    void addSource(DataReceiver *source);
    void deleteSources();
    void startLogging(QString filename);
    void stopLogging();
    int isLogging();
    QVector<BufferData> getLastFrame();
    QVector<BufferData> getNewFrame();  // Returns a new frame (ensuring no frame is read twice)
    void recalculateChannels();         // Recalculate baseAddresses
    void setChannelCount(int sensor_nr, int nr_channels);

signals:
    void sigInit();
    void sigDeinit();
    void sigStartLogging();
    void sigStopLogging();
    void sigStartTakingHistos(int);
    void sigStopTakingHistos();
    void sigHistoCompleted();   // Notify user that the histogram is ready
    void dataReady(const QByteArray& data); // Data readiness signal

public slots:
    void onNewData(DataReceiver *receiver);
    void receiveData(const QByteArray &data);
    QByteArray getNextData();

protected:
    int checkBufferOccupancies();
    int findLowestId();
    void logDataToFile();
    void init();    // Called after moving to the thread
    void deinit();

    QThread thread;
    QSemaphore initSemaphore;

    QVector<DataReceiver*> receivers;

    QVector<BufferData> currentFrame;
    signed short * copy_sensor_data;
    QVector<BufferData> backgroundFrame;
    QVector<BufferData> lastFrame;

    QVector<unsigned short> baseAddresses; // Base channel numbers for receivers
    QVector<unsigned short> channelCounts;   // Number of channels per board
    unsigned short totalChannels;            // Total channels (to write directly into file)
    unsigned short totalBoards;

    QMutex lastFrameMutex;
    QSemaphore newDataSemaphore;
    int nrReceivers;
    QString logFileName;
    QFile logFile;
    int loggingData = 0;

protected slots:
    void onInit();
    void onDeinit();
    void onStartLogging();
    void onStopLogging();

private:
    long long int frame_counter = 0;
    double intensity = 0.0;
    double position = 0.0;
    double focus = 0.0;
    QQueue<QByteArray> dataQueue;
    QMutex mutex;
    QWaitCondition dataAvailable;
};

#endif // EVENTBUILDER_H
