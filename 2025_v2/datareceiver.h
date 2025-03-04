#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QThread>
#include <QSemaphore>
#include "cbuffer.h"

#define RECEIVER_BUFFER_SIZE        10000
#define RECEIVER_TIMER_PERIOD_MS    200
#define RECEIVER_FRAMES_PER_SIG     100

#define DATA_PACKET_HEADER_SIZE     6
#define DATA_SYNC_HEADER_SIZE       6
#define DATA_RMS_FRAME_SIZE         16
#define DATA_BYTES_PER_SAMPLE       4 // 2 bytes RAW + 2 bytes CAL
#define DATA_SAMPLES_PER_SENSOR     64
#define DATA_MAX_SENSORS_PER_BOARD  5
#define DATA_MAX_BUNCH              16

inline int getDataRawBlockSize(int sensorsPerBoard) {
    return sensorsPerBoard * DATA_SAMPLES_PER_SENSOR * DATA_BYTES_PER_SAMPLE;
}

inline int getExpectedPacketSize(int sensorsPerBoard, int dmaBunch, int ethBunch) {
    return ethBunch * (
               DATA_PACKET_HEADER_SIZE +
               DATA_SYNC_HEADER_SIZE +
               dmaBunch * (getDataRawBlockSize(sensorsPerBoard)) +
               DATA_RMS_FRAME_SIZE
               );
}

#define DATA_MAX_PACKET_SIZE  \
( DATA_MAX_BUNCH * ( DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + \
                  (DATA_MAX_SENSORS_PER_BOARD * DATA_SAMPLES_PER_SENSOR * DATA_BYTES_PER_SAMPLE ) + \
                  DATA_RMS_FRAME_SIZE ) )

    typedef struct {
    unsigned short local_ctr;
    unsigned short global_ctr;
    unsigned short sma_state;
    unsigned short dummy;
    int device_nr;
    int data_ok;
} SyncFrame;

typedef struct {
    unsigned short mean;
    unsigned short sigma;
    unsigned short max;
    unsigned short status;
    unsigned short registers[4];
} RMSFrame;

class BufferData {
public:
    SyncFrame sync_frame;
    RMSFrame rms_frame;
    int buffer_size;
    unsigned short* raw_data;   // Unsigned raw data
    signed short* cal_data;     // Signed cal data

    BufferData();
    explicit BufferData(int size);
    void resize(int size);
    BufferData(const BufferData& master);
    BufferData& operator=(const BufferData& master);
    ~BufferData();
};

typedef CBuffer<BufferData> DataBuffer;

class DataReceiver : public QObject {
    Q_OBJECT
public:
    explicit DataReceiver(QObject *parent = nullptr);
    ~DataReceiver();

    void configureEthSettings(QHostAddress address_to_set, quint16 port_to_set);
    void configureBunchSize(int dma, int eth);
    void outputEnable(int en);

    int frameRate = 0;
    int devNr = 0;
    int sensorsPerBoard = 5;
    DataBuffer dataBuffer;

signals:
    void sigInit();
    void sigDeinit();
    void sigConfigureEthSettings();
    void sigDataReady(DataReceiver* ptr);

public slots:
    void onTimer();

protected:
    void init();
    void deinit();
    QThread thread;
    QSemaphore initSemaphore;
    QTimer* timer = nullptr;
    QUdpSocket* dataSocket = nullptr;
    QHostAddress address;
    quint16 port = 0;
    int outputEnabled = 0;
    int dmaBunch = 1;
    int ethBunch = 1;
    char tmpBuffer[DATA_MAX_PACKET_SIZE];
    int framesReceived = 0;
    int framesFromLastSig = 0;

protected slots:
    void readData();
    void onInit();
    void onDeinit();
    void onConfigureEthSettings();
};

#endif // DATARECEIVER_H
