#include "hw.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

HW::HW(QObject *parent) : QObject(parent)
{
}

HW::~HW()
{
    removeDevices();
}

void HW::addDevices(int nr_devices)
{
    for (int i = 0; i < nr_devices; i++) {
        Device *newDev = new Device(this);
        devices.append(newDev);
    }
}

void HW::removeDevices()
{
    for (int i = 0; i < devices.size(); i++) {
        delete devices[i];
    }
    devices.clear();
}

void HW::connectDevices()
{
    for (int i = 0; i < devices.size(); i++) {
        devices[i]->connectDevice();
    }
}

void HW::disconnectDevices()
{
    for (int i = 0; i < devices.size(); i++) {
        devices[i]->disconnectDevice();
    }
}

void HW::run()
{
    for (int i = 0; i < devices.size(); i++) {
        devices[i]->startAcq();
    }
}

void HW::stop()
{
    for (int i = 0; i < devices.size(); i++) {
        devices[i]->stopAcq();
    }
}

QString HW::report()
{
    QString rep;
    for (int i = 0; i < devices.size(); i++) {
        rep += QString("Device %1: %2 fps\n").arg(i).arg(devices[i]->getFrameRate());
    }
    return rep;
}

QVector<BufferData> HW::getLatestFrames()
{
    QVector<BufferData> frames;
    for (int i = 0; i < devices.size(); i++) {
        BufferData frame = devices[i]->dataReceiver.dataBuffer.look();
        frames.append(frame);
    }
    return frames;
}

QString HW::saveRawData(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return QString("Failed to open file for writing");
    }
    QDataStream out(&file);
    for (int i = 0; i < devices.size(); i++) {
        BufferData frame = devices[i]->dataReceiver.dataBuffer.look();
        out.writeRawData((const char*)frame.raw_data, frame.buffer_size * sizeof(unsigned short));
    }
    file.close();
    return QString();
}

void HW::configureDevice(int dev_nr, DeviceConfig dc)
{
    if (dev_nr < 0 || dev_nr >= devices.size())
        return;
    devices[dev_nr]->configure(dc);
}
