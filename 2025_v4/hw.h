#ifndef HW_H
#define HW_H

#include <QObject>
#include <QVector>
#include "device.h"

class HW : public QObject
{
    Q_OBJECT
public:
    explicit HW(QObject *parent = nullptr);
    ~HW();

    QVector<Device*> devices;
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

signals:

public slots:
};

#endif // HW_H
