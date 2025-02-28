#ifndef HW_H
#define HW_H

#include <QObject>
#include <QVector>
#include "device.h"
#include "datareceiver.h"

class HW : public QObject
{
    Q_OBJECT
public:
    explicit HW(QObject *parent = nullptr);
    ~HW();

    void addDevices(int nr_devices);
    void removeDevices();
    void connectDevices();
    void disconnectDevices();
    void run();
    void stop();
    QString report();
    QVector<BufferData> getLatestFrames();
    QString saveRawData(const QString &filename);
    void configureDevice(int dev_nr, DeviceConfig dc);
    QVector<Device*>& getDevices();

signals:
    void connectionStatusChanged(bool connected);

private slots:
    void onDeviceConnected();
    void onDeviceDisconnected();

private:
    QVector<Device*> devices;
    int connectedDevices = 0;
};

#endif
