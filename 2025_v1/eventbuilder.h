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
//#include "hw.h"
#include "datareceiver.h"
#include <immintrin.h> // Include for Intel Intrinsics
#include <emmintrin.h> // Include for SSE2

    //The event builder will constantly keep some data in the buffers to enable synchronization of the devices. So:
#define EVB_MIN_BUFFER_OCCUPANCY    (RECEIVER_BUFFER_SIZE / 8)      //the EVB will wait until so much data is in each device buffer
#define EVB_MAX_BUFFER_OCCUPANCY    (RECEIVER_BUFFER_SIZE / 2)      //or so much in at least one



class EventBuilder : public QObject
{
    Q_OBJECT
public:
    explicit EventBuilder( QObject *parent = 0);
    ~EventBuilder();

    void addSource(DataReceiver *source);
    void deleteSources();
    void startLogging(QString filename);
    void stopLogging();
    int isLogging();
    QVector<BufferData> getLastFrame();
    QVector<BufferData> getNewFrame();  //as getLastFrame(), but ensures that the frame is new, i.e. no frame will be read twice
    void recalculateChannels(); //recalculate baseAddresses
    void setChannelCount(int sensor_nr, int nr_channels);
signals:
    void sigInit();
    void sigDeinit();
    void sigStartLogging();
    void sigStopLogging();
    void sigStartTakingHistos(int);
    void sigStopTakingHistos();

    void sigHistoCompleted();   //this is a public signal which can be used to notify user that the histo is ready
    // Define a signal to notify when postdata is updated
    void dataReady(const QByteArray& data); // Define a signal for data readiness
public slots:
    void onNewData(DataReceiver *receiver);
    // Add a public slot to receive and store data
    void receiveData(const QByteArray &data);


    // Add a method to get data from the queue
    QByteArray getNextData();


protected:
    int checkBufferOccupancies();
    int findLowestId();
    void logDataToFile();
    void init();    //run after moving to thread
    void deinit();

    QThread thread;
    QSemaphore initSemaphore; 

    QVector<DataReceiver*> receivers;

    QVector<BufferData> currentFrame;
    signed short * copy_sensor_data;
    QVector<BufferData> backgroundFrame;

    QVector<BufferData> lastFrame;

    QVector<unsigned short> baseAddresses; //base channel numbers for receivers
    QVector<unsigned short> channelCounts; //and numbers of channels
    unsigned short totalChannels;   //we like unsigned shorts to put them directly into the data file
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
