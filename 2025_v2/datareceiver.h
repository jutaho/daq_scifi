#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QThread>
#include <QSemaphore>
#include "cbuffer.h"

// Put these back so that datareceiver.cpp can use them
#define RECEIVER_BUFFER_SIZE        10000
#define RECEIVER_TIMER_PERIOD_MS    200
#define RECEIVER_FRAMES_PER_SIG     100

//--------------------------------------------------------------------------------------
// Constants that typically do not change
//--------------------------------------------------------------------------------------
#define DATA_PACKET_HEADER_SIZE     6    // e.g. 0x5555, command, length...
#define DATA_SYNC_HEADER_SIZE       6    // local_ctr, global_ctr, sma_state
#define DATA_RMS_FRAME_SIZE         16   // 8 unsigned shorts (or 16 bytes)
#define DATA_BYTES_PER_SAMPLE       2
#define DATA_SAMPLES_PER_SENSOR     64
#define DATA_MAX_SENSORS_PER_BOARD  5
#define DATA_MAX_BUNCH              16   // max product of dmaBunch * ethBunch

//--------------------------------------------------------------------------------------
// Helper inline functions for computing packet sizes at runtime
//--------------------------------------------------------------------------------------
inline int getDataRawBlockSize(int sensorsPerBoard)
{
    // For each sensor: 64 samples, each 2 bytes
    return sensorsPerBoard * DATA_SAMPLES_PER_SENSOR * DATA_BYTES_PER_SAMPLE;
}

inline int getExpectedPacketSize(int sensorsPerBoard, int dmaBunch, int ethBunch)
{
    // Each packet includes:
    //   1) 6-byte packet header
    //   2) 6-byte sync header
    //   3) dmaBunch * raw block
    //   4) 16-byte RMS frame
    //
    // Multiply by ethBunch if you expect multiple blocks per Ethernet packet.
    return ethBunch * (
               DATA_PACKET_HEADER_SIZE +
               DATA_SYNC_HEADER_SIZE +
               dmaBunch * getDataRawBlockSize(sensorsPerBoard) +
               DATA_RMS_FRAME_SIZE
               );
}

//--------------------------------------------------------------------------------------
// We still need a maximum buffer size for tmpBuffer to avoid overflow
//--------------------------------------------------------------------------------------
#define DATA_MAX_PACKET_SIZE  \
( DATA_MAX_BUNCH * ( DATA_PACKET_HEADER_SIZE + DATA_SYNC_HEADER_SIZE + \
                  (DATA_MAX_SENSORS_PER_BOARD * DATA_SAMPLES_PER_SENSOR * DATA_BYTES_PER_SAMPLE) + \
                  DATA_RMS_FRAME_SIZE ) )

    //--------------------------------------------------------------------------------------
    // Data structures for sync and RMS frames
    //--------------------------------------------------------------------------------------
    typedef struct
{
    unsigned short local_ctr;
    unsigned short global_ctr;
    unsigned short sma_state;
    unsigned short dummy;    // e.g. 0xFFFF for packing
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

//--------------------------------------------------------------------------------------
// Modified BufferData: holds raw and cal data arrays
//--------------------------------------------------------------------------------------
class BufferData
{
public:
    SyncFrame sync_frame;
    RMSFrame rms_frame;
    int buffer_size;        // number of samples (channels) per board
    unsigned short* raw_data;  // raw sensor data (unsigned short)
    short* cal_data;           // calibration data (signed short)

    BufferData() : buffer_size(0), raw_data(nullptr), cal_data(nullptr) {}

    explicit BufferData(int size) : buffer_size(0), raw_data(nullptr), cal_data(nullptr)
    {
        resize(size);
    }

    void resize(int size)
    {
        if (size == buffer_size) return;  // no change needed

        // clean up old arrays
        if (raw_data) {
            delete[] raw_data;
            raw_data = nullptr;
        }
        if (cal_data) {
            delete[] cal_data;
            cal_data = nullptr;
        }

        // allocate new
        buffer_size = size;
        if (size > 0) {
            raw_data = new unsigned short[size];
            cal_data = new short[size];
            // Initialize calibration data to zero
            memset(cal_data, 0, size * sizeof(short));
        }
    }

    // Copy constructor
    BufferData(const BufferData& master) : buffer_size(0), raw_data(nullptr), cal_data(nullptr)
    {
        sync_frame = master.sync_frame;
        rms_frame  = master.rms_frame;
        resize(master.buffer_size);
        memcpy(raw_data, master.raw_data, buffer_size * sizeof(unsigned short));
        memcpy(cal_data, master.cal_data, buffer_size * sizeof(short));
    }

    // Assignment operator
    BufferData& operator=(const BufferData& master)
    {
        if (this == &master)
            return *this; // self-assignment guard

        sync_frame = master.sync_frame;
        rms_frame  = master.rms_frame;
        resize(master.buffer_size);
        memcpy(raw_data, master.raw_data, buffer_size * sizeof(unsigned short));
        memcpy(cal_data, master.cal_data, buffer_size * sizeof(short));
        return *this;
    }

    ~BufferData()
    {
        resize(0);
    }
};

typedef CBuffer<BufferData> DataBuffer;

//--------------------------------------------------------------------------------------
// DataReceiver class
//--------------------------------------------------------------------------------------
class DataReceiver : public QObject
{
    Q_OBJECT
public:
    explicit DataReceiver(QObject *parent = nullptr);
    ~DataReceiver();

    void configureEthSettings(QHostAddress address_to_set, quint16 port_to_set);
    void configureBunchSize(int dma, int eth);
    void outputEnable(int en);

    int frameRate       = 0;
    int devNr           = 0;
    int sensorsPerBoard = 5;  // default: 2 sensors per board
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
    QTimer* timer         = nullptr;
    QUdpSocket* dataSocket = nullptr;
    QHostAddress address;
    quint16 port          = 0;
    int outputEnabled     = 0;
    int dmaBunch          = 1;
    int ethBunch          = 1;

    // We use DATA_MAX_PACKET_SIZE as the largest possible buffer to avoid overflow
    char tmpBuffer[DATA_MAX_PACKET_SIZE];

    int framesReceived    = 0; // for rate calculation
    int framesFromLastSig = 0; // count frames before emitting sigDataReady

protected slots:
    void readData();
    void onInit();
    void onDeinit();
    void onConfigureEthSettings();
};

#endif // DATARECEIVER_H
