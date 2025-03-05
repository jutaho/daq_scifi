#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QThread>
#include <QSemaphore>
#include "cbuffer.h"

#define DATA_PACKET_HEADER_SIZE     6
#define DATA_SYNC_HEADER_SIZE       6 // add up to 12 in total
#define DATA_RMS_FRAME_SIZE         16
#define DATA_BYTES_PER_SAMPLE       4
#define DATA_SAMPLES_PER_SENSOR     64
#define DATA_MAX_SENSORS_PER_BOARD  5
#define DATA_MAX_BUNCH              16

// Each word (4 bytes) contains two sensor values (either raw or calibrated)
#define DATA_BYTES_PER_WORD         4
#define DATA_SAMPLES_PER_WORD       2  // Each word contains 2 samples (raw or calibrated)
#define DATA_BLOCK_WORDS            (sensorsPerBoard * DATA_SAMPLES_PER_SENSOR / DATA_SAMPLES_PER_WORD)

// Updated data block size considering interleaved format (word-based storage)
#define DATA_BLOCK_SIZE (sensorsPerBoard * DATA_SAMPLES_PER_SENSOR * DATA_BYTES_PER_SAMPLE)

#define DATA_PACKET_SIZE            (DATA_MAX_BUNCH * (DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + DATA_BLOCK_SIZE + DATA_RMS_FRAME_SIZE ) )

#define DATA_MAX_BLOCK_SIZE         (DATA_MAX_SENSORS_PER_BOARD * DATA_SAMPLES_PER_SENSOR * DATA_BYTES_PER_SAMPLE)
#define DATA_MAX_PACKET_SIZE        ( DATA_MAX_BUNCH * (DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + DATA_MAX_BLOCK_SIZE + DATA_RMS_FRAME_SIZE ) )

#define RECEIVER_BUFFER_SIZE        10000

#define RECEIVER_TIMER_PERIOD_MS    200 // The period of the timer to measure data rate. The measurement is always properly scaled.
#define RECEIVER_FRAMES_PER_SIG     100 // The DataReady signal is transmitted only every N frames, not to overload queued signals framework.

typedef struct {
    unsigned short local_ctr;
    unsigned short global_ctr;
    unsigned short sma_state;
    unsigned short dummy = 0xFFFF;  // for nice structure packing
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

class BufferData
{
public:
    SyncFrame sync_frame;        // Synchronization frame data
    RMSFrame rms_frame;          // RMS frame data (mean, sigma, max, status)
    int buffer_size;             // Size of the buffer
    unsigned short* raw_data;    // Raw sensor data (unsigned short)
    signed short* cal_data;      // Calibrated sensor data (signed short)

    BufferData() : buffer_size(0), raw_data(nullptr), cal_data(nullptr) {}

    BufferData(int size) : buffer_size(0), raw_data(nullptr), cal_data(nullptr) {
        resize(size);
    }

    void resize(int size)
    {
        if (size == buffer_size)
            return;         // No need to change

        // Delete old data if any
        if (raw_data) {
            delete[] raw_data;
            raw_data = nullptr;
        }
        if (cal_data) {
            delete[] cal_data;
            cal_data = nullptr;
        }

        buffer_size = size;

        // Allocate memory for both raw and calibrated data if the size is greater than 0
        if (size) {
            raw_data = new unsigned short[size];  // For raw data (unsigned short)
            cal_data = new signed short[size];    // For calibrated data (signed short)
        }
    }

    BufferData(const BufferData& master) : buffer_size(0), raw_data(nullptr), cal_data(nullptr)
    {
        sync_frame = master.sync_frame;
        rms_frame = master.rms_frame;
        resize(master.buffer_size);
        // Copy data for both raw and calibrated data
        memcpy(raw_data, master.raw_data, buffer_size * sizeof(unsigned short));
        memcpy(cal_data, master.cal_data, buffer_size * sizeof(signed short));
    }

    BufferData& operator=(const BufferData& master)
    {
        if (this == &master)
            return *this;    // Self-assignment

        sync_frame = master.sync_frame;
        rms_frame = master.rms_frame;
        resize(master.buffer_size);
        // Copy data for both raw and calibrated data
        memcpy(raw_data, master.raw_data, buffer_size * sizeof(unsigned short));
        memcpy(cal_data, master.cal_data, buffer_size * sizeof(signed short));
        return *this;
    }

    ~BufferData()
    {
        resize(0);  // Deallocate memory
    }
};

typedef CBuffer<BufferData> DataBuffer;

class DataReceiver : public QObject
{
    Q_OBJECT
public:
    explicit DataReceiver(QObject *parent = nullptr);
    ~DataReceiver();

    void configureEthSettings(QHostAddress address_to_set, quint16 port_to_set);
    void configureBunchSize(int dma, int eth);
    void outputEnable(int en);

    int frameRate = 0;
    int devNr = 0;
    int sensorsPerBoard = 5; // Number of sensors per board (adjust as needed)

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
    quint16 port;
    int outputEnabled = 0;
    int dmaBunch = 1;
    int ethBunch = 1;
    char tmpBuffer[DATA_MAX_PACKET_SIZE];
    int framesReceived = 0; // To calculate frame rate
    int framesFromLastSig = 0;

protected slots:
    void readData();
    void onInit();
    void onDeinit();
    void onConfigureEthSettings();
};

#endif // DATARECEIVER_H
