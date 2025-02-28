#include "device.h"
#include <QDebug>

Device::Device(QObject *parent)
    : QObject(parent),
    controlSocket(this),
    connected(0),
    dataReceiver(this)
{
    connect(&controlSocket, &QTcpSocket::connected, this, &Device::onConnected);
    connect(&controlSocket, &QTcpSocket::errorOccurred, this, &Device::onSocketError);
    connect(&controlSocket, &QTcpSocket::disconnected, this, &Device::onDisconnected);
}

Device::~Device()
{
    if (connected)
        stopAcq();
    disconnectDevice();
}

void Device::connectDevice()
{
    QString ipStr = "10.0.7.16";
    quint16 port = DEV_BASE_DATA_PORT;

    emit logMessage("Device::connectDevice() called. Attempting to connect to " + ipStr + " on port " + QString::number(port));

    controlSocket.connectToHost(QHostAddress(ipStr), port);
}

void Device::disconnectDevice()
{
    controlSocket.disconnectFromHost();
}

void Device::onConnected()
{
    emit logMessage("Device connected successfully!");
    emit connectionStatusChanged(true);
}

void Device::onSocketError(QAbstractSocket::SocketError socketError)
{
    emit logMessage("Connection failed! Error: " + QString::number(socketError) + " - " + controlSocket.errorString());
}

void Device::onDisconnected()
{
    emit logMessage("Device disconnected.");
    emit connectionStatusChanged(false);
}

void Device::startAcq()
{
    dataReceiver.outputEnable(1);
}

void Device::stopAcq()
{
    dataReceiver.outputEnable(0);
}

int Device::getFrameRate()
{
    return dataReceiver.frameRate;
}

DataReceiver& Device::getDataReceiver()
{
    return dataReceiver;
}
