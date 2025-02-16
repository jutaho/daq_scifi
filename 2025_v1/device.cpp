#include "device.h"
#include "dev_commands.h"
#include "helpers.h"

#include <QtGlobal>



//************** Constructor ********************
// Qt5
/*
Device::Device(QObject *parent) : QObject(parent), controlSocket(this)
{
    connect(&controlSocket, QTcpSocket::connected, this, Device::onConnected);
    connect(&controlSocket,
            static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
            this, Device::onSocketError);
    connect(&controlSocket, QTcpSocket::disconnected, this, Device::onDisconnected);

*/
/*dataReceiver.moveToThread(&receiverThread);
    receiverThread.start();
    dataReceiver.init();*/
//}

//Qt6
Device::Device(QObject *parent) : QObject(parent), controlSocket(this)
{
    connect(&controlSocket, &QTcpSocket::connected, this, &Device::onConnected);

    connect(&controlSocket, &QAbstractSocket::errorOccurred,
            [this](QAbstractSocket::SocketError socketError) {
                this->onSocketError(socketError);
            });

    connect(&controlSocket, &QTcpSocket::disconnected, this, &Device::onDisconnected);

    /*dataReceiver.moveToThread(&receiverThread);
    receiverThread.start();
    dataReceiver.init();*/
}


Device::~Device()
{
    if (connected)
    {
        stopAcq();
        disconnectDevice();
    }

    /*receiverThread.quit();
    receiverThread.wait();*/
}


//************** Device configuration ********************

void Device::configure(DeviceConfig &cfg)
{
    int ip_changed = 0;
    for (int i = 0; i < 4; i++)
        if (cfg.device_ip[i] != deviceConfig.device_ip[i])
            ip_changed = 1;

    deviceConfig = cfg;

        //update data receiver settings
    quint32 ip32 = 0;
    unsigned short ipshort[4];
    for (int i = 0; i < 4; i++)
    {
        ip32 <<= 8;
        ip32 |= (qint32)(unsigned char)deviceConfig.own_ip[i];
        ipshort[i] = (unsigned short)(unsigned char)deviceConfig.own_ip[i];
    }
    dataReceiver.configureEthSettings(QHostAddress(ip32), DEV_BASE_DATA_PORT + deviceConfig.device_id);
    dataReceiver.configureBunchSize(deviceConfig.dma_bunch, deviceConfig.eth_bunch);
    dataReceiver.devNr = deviceConfig.device_id;
    dataReceiver.sensorsPerBoard = deviceConfig.max_sensors();

    if (connected)
    {
            //re-connect if needed
        if (ip_changed)
        {
            disconnectDevice();
            while(connected);
            connectDevice();

            int ctr = 0;
            while (!connected)
            {
                QThread::msleep(10);
                if (++ctr > 100)
                {
                    qWarning(qPrintable(QString("Device %1: IP change: reconnection failed!").arg(deviceConfig.device_id)));
                    return;
                }
            }
        }

            //update device settings
        qInfo(qPrintable(QString("Device %1: setting up.").arg(deviceConfig.device_id)));

        ctrlMaster(deviceConfig.master);
        ctrlSetPeriod(deviceConfig.period);
        ctrlSetTint(deviceConfig.tint);
        ctrlSetMasterDelay(deviceConfig.master_delay);
        ctrlSetSlaveDelay(deviceConfig.slave_delay);
        ctrlSetGain(deviceConfig.gain);
        ctrlSetClusterThreshold(deviceConfig.threshold);
        ctrlConfigBunch(deviceConfig.dma_bunch, deviceConfig.eth_bunch);
        ctrlConfigPeer(ipshort, DEV_BASE_DATA_PORT+ deviceConfig.device_id);
    }
}

//************** Device connection ********************

void Device::connectDevice()
{
    QString addr_txt = QString("%1.%2.%3.%4")
                        .arg(deviceConfig.device_ip[0])
                        .arg(deviceConfig.device_ip[1])
                        .arg(deviceConfig.device_ip[2])
                        .arg(deviceConfig.device_ip[3]);
    quint16 port = 4000;

    if (connected)
    {
        qWarning(qPrintable(QString("Device %1: connect: already connected, reconnecting!").arg(deviceConfig.device_id)));
        disconnectDevice();
        while (connected)
            QThread::msleep(1);
    }

    qInfo(qPrintable(QString("Device %1: trying to connect to %2").arg(deviceConfig.device_id).arg(addr_txt)));
    controlSocket.connectToHost(addr_txt, 4000);

}

void Device::disconnectDevice()
{
    if (!connected)
        qWarning(qPrintable(QString("Device %1: disconnect: device not connected!").arg(deviceConfig.device_id)));

    controlSocket.disconnectFromHost();
}

void Device::onConnected()
{
    qInfo(qPrintable(QString("Device %1: connected with %2.%3.%4.%5")
                     .arg(deviceConfig.device_id)
                     .arg(deviceConfig.device_ip[0])
                     .arg(deviceConfig.device_ip[1])
                     .arg(deviceConfig.device_ip[2])
                     .arg(deviceConfig.device_ip[3]) ));
    connected = 1;

    configure(deviceConfig);
}

void Device::onSocketError(QAbstractSocket::SocketError socketError)
{
    qWarning(qPrintable(QString("Device %1: socket error %2!").arg(deviceConfig.device_id).arg((int)socketError)));
    if (controlSocket.state() != QAbstractSocket::ConnectedState)
        connected = 0;
    else
        connected = 1;
}

void Device::onDisconnected()
{
    qInfo(qPrintable(QString("Device %1: disconnected.").arg(deviceConfig.device_id)));
    connected = 0;
}

//************** Controlling device ********************

void Device::startAcq()
{
    qInfo(qPrintable(QString("Device %1: starting data taking...").arg(deviceConfig.device_id)));

    if (!connected)
    {
        qWarning(qPrintable(QString("Device %1: not connected!").arg(deviceConfig.device_id)));
        return;
    }

    dataReceiver.dataBuffer.clear();
    dataReceiver.outputEnable(1);

    ctrlResetCounters();
    ctrlDaq(1);
    ctrlTrigger(1);
}

void Device::stopAcq()
{
    qInfo(qPrintable(QString("Device %1: stopping data taking...").arg(deviceConfig.device_id)));

    if (!connected)
    {
        qWarning(qPrintable(QString("Device %1: not connected!").arg(deviceConfig.device_id)));
        return;
    }

    ctrlTrigger(0);
    QThread::msleep(10);
    ctrlFlushData();
    ctrlDaq(0);
    QThread::msleep(10);
    //QThread::msleep(10);

    dataReceiver.outputEnable(0);
}

void Device::leds(int leds_enable, int debug_led)
{
    if (connected)
    {
        ctrlLeds(leds_enable);
        ctrlDebugLed(debug_led);
    }
    else
        qWarning(qPrintable(QString("Device %1: not connected!").arg(deviceConfig.device_id)));
}

int Device::getFrameRate()
{
    return dataReceiver.frameRate;
}

//************** Data exchange ********************

int Device::sendCtrl(unsigned short command, QVector<unsigned short> &data)
{
    if (!connected)
    {
        qWarning(qPrintable(QString("Device %1: not connected!").arg(deviceConfig.device_id)));
        return DEV_CTRL_ERROR;
    }

    int dl = data.length();
    char buffer[2*dl + 6];

    buffer[0] = 0x55;
    buffer[1] = 0x55;
    buffer[2] = HI(command);
    buffer[3] = LO(command);
    buffer[4] = HI(dl);
    buffer[5] = LO(dl);

    for (int i = 0; i < dl; i++)
    {
        buffer[2*i+6] = HI(data[i]);
        buffer[2*i+7] = LO(data[i]);
    }

    return (int)controlSocket.write(buffer, 2*dl + 6);
}

int Device::receiveCtrl(unsigned short &command, QVector<unsigned short> &data)
{
    if (!connected)
    {
        qWarning(qPrintable(QString("Device %1: not connected!").arg(deviceConfig.device_id)));
        return DEV_CTRL_ERROR;
    }
        //Wait for data
    if (!controlSocket.waitForReadyRead(DEV_CTRL_READ_TIMEOUT))
    {
        qWarning(qPrintable(QString("Device %1: no data received!").arg(deviceConfig.device_id)));
        return DEV_CTRL_ERROR;
    }

        //Find sync characters
    int sync_found = 0;
    char buffer;
    while (sync_found < 2)
    {
        if (controlSocket.read(&buffer, 1) <= 0)
        {
            qWarning(qPrintable(QString("Device %1: no data received!").arg(deviceConfig.device_id)));
            return DEV_CTRL_ERROR;
        }
        if (buffer == 0x55)
            sync_found++;
        else
            qWarning( qPrintable(QString("Device %1: 0x%2 found instead of sync character(0x55)!")
                                 .arg(deviceConfig.device_id).arg((int)(unsigned int)buffer,(int)2,(int)16,QLatin1Char('0'))) );
    }

    char header[4];
    if (controlSocket.read(header,4) < 4)
    {
        qWarning(qPrintable(QString("Device %1: data receive error when getting header!").arg(deviceConfig.device_id)));
        return DEV_CTRL_ERROR;
    }

    command = BYTES2SHORT(header);
    unsigned short dl = BYTES2SHORT(header+2);

    char data_buf[2*dl];
    if (controlSocket.read(data_buf, 2*dl) < (2*dl))
    {
        qWarning(qPrintable(QString("Device %1: data receive error when getting data!").arg(deviceConfig.device_id)));
        return DEV_CTRL_ERROR;

    }

    data.clear();

    for (int i = 0; i < dl; i++)
        data.append(BYTES2SHORT(data_buf + 2*i));

    return dl;
}

int Device::queryCtrl(unsigned short command, QVector<unsigned short> &txdata, QVector<unsigned short> &rxdata)
{
    if (sendCtrl(command, txdata) == DEV_CTRL_ERROR)
        return DEV_CTRL_ERROR;

    unsigned short command_rx;
    if (receiveCtrl(command_rx, rxdata) == DEV_CTRL_ERROR)
        return DEV_CTRL_ERROR;

    if (command_rx != command)
        return DEV_CTRL_ERROR;

    return DEV_CTRL_OK;
}

//************** Simple commands ********************

int Device::ctrlPing()
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;

    return queryCtrl(COMMAND_PING, txdata, rxdata);
}

int Device::ctrlDebugLed(int state)
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;

    if (state)
        return queryCtrl(COMMAND_DEBUG_LED_ON, txdata, rxdata);
    else
        return queryCtrl(COMMAND_DEBUG_LED_OFF, txdata, rxdata);
}

int Device::ctrlLeds(int en)
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;

    if (en)
        return queryCtrl(COMMAND_LEDS_ENABLE, txdata, rxdata);
    else
        return queryCtrl(COMMAND_LEDS_DISABLE, txdata, rxdata);
}

int Device::ctrlTrigger(int en)
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;

    if (en)
        return queryCtrl(COMMAND_TRIGGER_ENABLE, txdata, rxdata);
    else
        return queryCtrl(COMMAND_TRIGGER_DISABLE, txdata, rxdata);
}

int Device::ctrlMaster(int en)
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;

    if (en)
        return queryCtrl(COMMAND_TRIGGER_SET_MASTER, txdata, rxdata);
    else
        return queryCtrl(COMMAND_TRIGGER_SET_SLAVE, txdata, rxdata);
}

int Device::ctrlSetPeriod(int period)
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;
    txdata.append((unsigned short)period);

    return queryCtrl(COMMAND_TRIGGER_SET_PERIOD, txdata, rxdata);
}

int Device::ctrlSetTint(int tint)
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;
    txdata.append((unsigned short)tint);

    return queryCtrl(COMMAND_TRIGGER_SET_TINT, txdata, rxdata);
}

int Device::ctrlSetMasterDelay(int tint)
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;
    txdata.append((unsigned short)tint);

    return queryCtrl(COMMAND_TRIGGER_SET_MASTER_DELAY, txdata, rxdata);
}

int Device::ctrlSetSlaveDelay(int tint)
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;
    txdata.append((unsigned short)tint);

    return queryCtrl(COMMAND_TRIGGER_SET_SLAVE_DELAY, txdata, rxdata);
}

int Device::ctrlDaq(int en)
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;

    if (en)
        return queryCtrl(COMMAND_DAQ_ENABLE, txdata, rxdata);
    else
        return queryCtrl(COMMAND_DAQ_DISABLE, txdata, rxdata);
}

int Device::ctrlResetCounters()
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;

    return queryCtrl(COMMAND_DAQ_RESET_COUNTERS, txdata, rxdata);
}

int Device::ctrlFlushData()
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;

    return queryCtrl(COMMAND_DAQ_FLUSH_DATA, txdata, rxdata);
}

int Device::ctrlConfigPeer(unsigned short* ip, unsigned short port)
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;
    for (int i = 0; i < 4; i++)
        txdata.append(ip[i]);
    txdata.append(port);

    return queryCtrl(COMMAND_DAQ_CONFIG_PEER, txdata, rxdata);
}

int Device::ctrlSetGain(int val)
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;
    txdata.append((unsigned short)(val?1:0));

    return queryCtrl(COMMAND_SET_GAIN, txdata, rxdata);
}

int Device::ctrlConfigBunch(int dma, int eth)
{
    qWarning("Bunch configuration not implemented!");
    return DEV_CTRL_OK;

    /*QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;

    if (en)
        return queryCtrl(COMMAND_DAQ_ENABLE, txdata, rxdata);
    else
        return queryCtrl(COMMAND_DAQ_DISABLE, txdata, rxdata);*/
}

int Device::ctrlSetClusterThreshold(int threshold)
{
    QVector<unsigned short> rxdata;
    QVector<unsigned short> txdata;
    txdata.append((unsigned short)threshold);

    if (threshold)
        return queryCtrl(COMMAND_SET_CLUSTER_THRESHOLD, txdata, rxdata);
    else
        return queryCtrl(COMMAND_SET_CLUSTER_THRESHOLD, txdata, rxdata);
}


