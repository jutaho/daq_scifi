#include "device.h"
#include "dev_commands.h"
#include "helpers.h"
#include <QThread>

// Constructor
Device::Device(QObject *parent) : QObject(parent), controlSocket(this)
{
    connect(&controlSocket, &QTcpSocket::connected, this, &Device::onConnected);
    connect(&controlSocket, &QAbstractSocket::errorOccurred, this, &Device::onSocketError);
    connect(&controlSocket, &QTcpSocket::disconnected, this, &Device::onDisconnected);
}

// Destructor
Device::~Device()
{
    if (connected)
    {
        stopAcq();
        disconnectDevice();
    }
}

// Configure device
void Device::configure(DeviceConfig &cfg)
{
    QMutexLocker locker(&mutex);
    bool ip_changed = memcmp(cfg.device_ip, deviceConfig.device_ip, sizeof(deviceConfig.device_ip)) != 0;

    deviceConfig = cfg;

    quint32 ip32 = 0;
    unsigned short ipshort[4];
    for (int i = 0; i < 4; i++)
    {
        ip32 = (ip32 << 8) | cfg.own_ip[i];
        ipshort[i] = cfg.own_ip[i];
    }

    dataReceiver.configureEthSettings(QHostAddress(ip32), DEV_BASE_DATA_PORT + cfg.device_id);
    dataReceiver.configureBunchSize(cfg.dma_bunch, cfg.eth_bunch);

    if (connected && ip_changed)
    {
        disconnectDevice();
        QThread::msleep(100);
        connectDevice();
    }
}

// Connect device
void Device::connectDevice()
{
    QString addr_txt = QString("%1.%2.%3.%4")
    .arg(deviceConfig.device_ip[0])
        .arg(deviceConfig.device_ip[1])
        .arg(deviceConfig.device_ip[2])
        .arg(deviceConfig.device_ip[3]);

    qInfo() << "Device" << deviceConfig.device_id << ": trying to connect to" << addr_txt << "on port" << DEV_BASE_DATA_PORT;

    controlSocket.connectToHost(addr_txt, DEV_BASE_DATA_PORT);

    if (!controlSocket.waitForConnected(5000)) // Timeout 5 Sekunden
    {
        qWarning() << "Device" << deviceConfig.device_id << ": connection failed. Error:"
                   << controlSocket.errorString();
        return;
    }

    qInfo() << "Device" << deviceConfig.device_id << ": successfully connected.";
}
// Disconnect device
void Device::disconnectDevice()
{
    if (!connected)
    {
        qWarning() << "Device" << deviceConfig.device_id << ": not connected!";
        return;
    }

    controlSocket.disconnectFromHost();
}

// Handle connection established
void Device::onConnected()
{
    qInfo() << "Device" << deviceConfig.device_id << ": connected successfully.";
    connected = 1;
    emit connectionStatusChanged(true);
    configure(deviceConfig);
}

// Handle socket error
void Device::onSocketError(QAbstractSocket::SocketError socketError)
{
    qWarning() << "Device" << deviceConfig.device_id << ": socket error" << socketError << controlSocket.errorString();
    connected = 0;
    emit connectionStatusChanged(false);
}

// Handle disconnection
void Device::onDisconnected()
{
    qInfo() << "Device" << deviceConfig.device_id << ": disconnected.";
    connected = 0;
    emit connectionStatusChanged(false);
}

// Start acquisition
void Device::startAcq()
{
    QMutexLocker locker(&mutex);

    if (!connected)
    {
        qWarning() << "Device" << deviceConfig.device_id << ": not connected. Cannot start acquisition.";
        return;
    }

    dataReceiver.dataBuffer.clear();
    dataReceiver.outputEnable(true);

    ctrlResetCounters();
    ctrlDaq(1);
    emit acquisitionStarted();
}

// Stop acquisition
void Device::stopAcq()
{
    QMutexLocker locker(&mutex);

    if (!connected)
    {
        qWarning() << "Device" << deviceConfig.device_id << ": not connected. Cannot stop acquisition.";
        return;
    }

    ctrlDaq(0);
    dataReceiver.outputEnable(false);
    emit acquisitionStopped();
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


