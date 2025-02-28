#include "hw.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

HW::HW(QObject *parent) : QObject(parent), connectedDevices(0) {}

HW::~HW()
{
    removeDevices();
}

void HW::addDevices(int nr_devices)
{
    for (int i = 0; i < nr_devices; i++)
    {
        Device* dev = new Device(this);
        devices.append(dev);
        qDebug() << "Added device" << i;
    }
}

void HW::removeDevices()
{
    qDeleteAll(devices);
    devices.clear();
}

void HW::connectDevices()
{
    qDebug() << "HW::connectDevices() called.";
    qDebug() << "Number of devices:" << devices.size();

    if (devices.isEmpty()) {
        qDebug() << "No devices to connect!";
        emit connectionStatusChanged(false);
        return;
    }

    for (Device* dev : devices) {
        connect(dev, &Device::connectionStatusChanged, this, &HW::onDeviceConnected);
        dev->connectDevice();
    }
}

void HW::onDeviceConnected()
{
    connectedDevices++;
    emit connectionStatusChanged(true);
}

void HW::onDeviceDisconnected()
{
    connectedDevices--;
    if (connectedDevices <= 0) {
        emit connectionStatusChanged(false);
    }
}


QVector<Device*>& HW::getDevices()
{
    return devices;
}
