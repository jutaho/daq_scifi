#ifndef HW_H
#define HW_H

#include <QObject>
#include <QVector>
#include <QThread>
#include "device.h"
#include "eventbuilder.h"
#include "networkthread.h"
class HW : public QObject
{
    Q_OBJECT
public:

public:
    explicit HW(QObject *parent = 0);
    ~HW();

    QVector<Device*> devices;
    EventBuilder eventBuilder;
  //  NetworkThread networkThread;

    Device &operator [](int nr);
    void addDevices(int nr_devices);
    void removeDevices();

    void connectDevices();
    void disconnectDevices();
    void run();
    void stop();
    QString report();
    void configureDevice(int dev_nr, DeviceConfig dc);
signals:

public slots:


protected:

private:



};

#endif // HW_H
