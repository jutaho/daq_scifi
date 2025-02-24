#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QTcpSocket>
#include <QVector>
#include <QMutex>
#include "datareceiver.h"

// Constants
#define DEV_CTRL_READ_TIMEOUT   500
#define DEV_CTRL_ERROR          -1
#define DEV_CTRL_OK             0
#define DEV_BASE_DATA_PORT      4000

// Device configuration structure
class DeviceConfig
{
public:
    unsigned char own_ip[4];
    unsigned char device_ip[4];
    int device_id;
    int hardware_ver;
    int master;
    int plane;          // For example, X = 0, Y = 1
    int position;       // Physical position within the plane
    int nr_sensors;     // Number of sensors equipped
    int period;
    int tint;
    int master_delay;   // Trigger delay for synchronization
    int slave_delay;
    int gain;           // 0 (low) or 1 (high), optional
    int dma_bunch;
    int eth_bunch;
    int threshold;

    DeviceConfig() : own_ip{10, 0, 7, 1}, device_ip{10, 0, 7, 2},
        device_id(0), hardware_ver(0), master(1), plane(0),
        position(0), nr_sensors(0), period(65535), tint(1),
        master_delay(1), slave_delay(1), gain(0),
        dma_bunch(1), eth_bunch(1), threshold(1) {}

    int max_sensors() const
    {
        switch (hardware_ver)
        {
        case 1: return 2;
        case 2: return 5;
        default: qCritical("Unsupported hardware version!"); return 0;
        }
    }

    int max_channels() const { return 64 * max_sensors(); }
    int nr_channels() const { return 64 * nr_sensors; }
};

// Device class
class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = nullptr);
    ~Device();

    void connectDevice();
    void disconnectDevice();

    void configure(DeviceConfig &cfg);
    void startAcq();
    void stopAcq();
    void leds(int leds_enable, int debug_led);
    int getFrameRate();

    DeviceConfig deviceConfig;
    DataReceiver dataReceiver;

signals:
    void connectionStatusChanged(bool connected);
    void acquisitionStarted();
    void acquisitionStopped();

protected:
    QAtomicInt connected{0}; // Thread-safe connection status
    QTcpSocket controlSocket;
    QMutex mutex;            // Mutex for shared resource protection

    int sendCtrl(unsigned short command, QVector<unsigned short> &data);
    int receiveCtrl(unsigned short &command, QVector<unsigned short> &data);
    int queryCtrl(unsigned short command, QVector<unsigned short> &txdata, QVector<unsigned short> &rxdata);

    int ctrlPing();
    int ctrlDebugLed(int state);
    int ctrlLeds(int en);
    int ctrlTrigger(int en);
    int ctrlMaster(int en);
    int ctrlSetPeriod(int period);
    int ctrlSetTint(int tint);
    int ctrlDaq(int en);
    int ctrlResetCounters();
    int ctrlFlushData();
    int ctrlConfigPeer(unsigned short *ip, unsigned short port);
    int ctrlSetGain(int val);
    int ctrlConfigBunch(int dma, int eth);
    int ctrlSetMasterDelay(int tint);
    int ctrlSetSlaveDelay(int tint);
    int ctrlSetClusterThreshold(int threshold);

protected slots:
    void onConnected();
    void onSocketError(QAbstractSocket::SocketError socketError);
    void onDisconnected();
};

#endif // DEVICE_H
