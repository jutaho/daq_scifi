#include "hw.h"
HW::HW(QObject *parent) : QObject(parent), eventBuilder()// , networkThread(eventBuilder)
{

    /*eventBuilder.moveToThread(&eventBuilderThread);
    eventBuilderThread.start();
    eventBuilder.init();*/

    // Create and start the network thread
   // networkThread.start();
}

HW::~HW()
{
 //   if (networkThread.isRunning()){
 //       networkThread.stopThread();
 //       networkThread.wait(); // Wait for the network thread to finish gracefully
 //   }
    eventBuilder.stopLogging();
    removeDevices();

}

Device& HW::operator[](int nr)
{
    return *(devices[nr]);

}

void HW::addDevices(int nr_devices)
{
    for (int i = 0; i < nr_devices; i++)
    {
        Device* new_dev = new Device;
        devices.push_back(new_dev);
        eventBuilder.addSource(&(new_dev->dataReceiver));
    }
}

void HW::removeDevices()
{
    eventBuilder.deleteSources();
    for (int i = 0; i < devices.length(); i++)
        delete devices[i];
    devices.clear();
}


void HW::configureDevice(int dev_nr, DeviceConfig dc)
{
    (*this)[dev_nr].configure(dc);
    eventBuilder.setChannelCount(dev_nr, dc.max_channels());
}

void HW::connectDevices()
{
    qInfo("Connecting devices...");
    for (int i = 0; i < devices.length(); i++)
        devices[i]->connectDevice();
}

void HW::disconnectDevices()
{
    qInfo("Disconnecting devices...");
    for (int i = 0; i < devices.length(); i++)
        devices[i]->disconnectDevice();
}

void HW::run()
{
    //No need to start EVB. It's running all the time.
    // Start the UDP server when an instance of HW is created
        //run slave(s)
    for (int i = 0; i < devices.length(); i++)
        if (devices[i]->deviceConfig.master == 0)
            devices[i]->startAcq();

        //run master(s)
    for (int i = 0; i < devices.length(); i++)
        if (devices[i]->deviceConfig.master != 0)
            devices[i]->startAcq();
}

void HW::stop()
{
    // Application cleanup
    //if (networkThread.isRunning()){
 //   networkThread.stopThread();
 //   networkThread.wait(); // Wait for the network thread to finish gracefully
 //   }
        //stop master(s)
    for (int i = 0; i < devices.length(); i++)
        if (devices[i]->deviceConfig.master != 0)
            devices[i]->stopAcq();

        //stop slave(s)
    for (int i = 0; i < devices.length(); i++)
        if (devices[i]->deviceConfig.master == 0)
            devices[i]->stopAcq();

    //EVB is running all the time.
}

QString HW::report()
{
    int nr_devices = devices.length();
    QString result;

    for (int dev_nr = 0; dev_nr < nr_devices; dev_nr++)
    {
        double buffer_ocupancy = 100.0 * (double)(devices[dev_nr]->dataReceiver.dataBuffer.nrItems()) / (double)RECEIVER_BUFFER_SIZE;
        double ksps = (double)(devices[dev_nr]->getFrameRate())/1000.0;
        result += QString("%1: %2kfps, %3% ").arg(dev_nr).arg(ksps,5,'f',2,'0').arg(buffer_ocupancy,4,'f',1,'0');
    }

    return result;
}
