#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QTcpSocket>
#include <QVector>
#include <QMutex>
#include <QAtomicInt>
#include "datareceiver.h"
#include "deviceconfig.h"

#define DEV_BASE_DATA_PORT 4000

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
    int getFrameRate();

    DataReceiver& getDataReceiver();

signals:
    void connectionStatusChanged(bool connected);
    void logMessage(const QString &message);

protected slots:
    void onConnected();
    void onSocketError(QAbstractSocket::SocketError socketError);
    void onDisconnected();

private:
    QTcpSocket controlSocket;
    QAtomicInt connected;
    DeviceConfig deviceConfig;
    DataReceiver dataReceiver;
};

#endif // DEVICE_H
