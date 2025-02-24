#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QVector>
#include <QThread>
#include <QMutex>

#include "datareceiver.h"

#define DEV_CTRL_READ_TIMEOUT   500
#define DEV_CTRL_ERROR          -1
#define DEV_CTRL_OK             0

#define DEV_BASE_DATA_PORT      4000

class DeviceConfig
{
public:
    unsigned char own_ip[4];
    unsigned char device_ip[4];
    int device_id;
    int hardware_ver;
    int master;
    int plane;          //for ex. X may be 0 and Y may be 1
    int position;       //physical position within plane
    int nr_sensors;     //a device may be equipped with only one sensor
    int period;
    int tint;
    int master_delay;  //trigger delay values to synchronize boards
    int slave_delay;
    int gain;               //0 (low) or 1 (high); TO BE DONE
    int dma_bunch;
    int eth_bunch;
    int threshold;
    int max_sensors()

    {
        switch(hardware_ver)
        {
            case 1: return 2; break;
            case 2: return 5; break;
            default: qCritical("Unsupported hardware version!"); return 0; break;
        }
    }
    int max_channels() {return 64*max_sensors();}
    int nr_channels() {return 64*nr_sensors;}
    DeviceConfig() : own_ip{10,0,7,1}, device_ip{10,0,7,2},
        device_id{0}, hardware_ver{0}, master{1}, plane{0}, position{0}, nr_sensors{0},
        period{65535}, tint{1}, master_delay{1}, slave_delay{1}, gain{0}, dma_bunch{1}, eth_bunch{1}, threshold{1} {}

};


class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = 0);
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


protected:
    int connected = 0;


    QTcpSocket controlSocket;
    //QThread receiverThread;

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
