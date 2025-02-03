#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H


#include <QThread>
#include <QUdpSocket>
#include "iostream"
#include <QTime>
#include <QThread>
#include <QUdpSocket>
#include <QMutex>
#include <QWaitCondition>
#include "eventbuilder.h"

class NetworkThread : public QThread
{
    Q_OBJECT
private:
    quint16 serverPort = 1901;    // Port number for the UDP server
    double intensity = 0.0, position = 0.0, focus = 0.0;

    QMutex mutex;               // Mutex for data synchronization
    QWaitCondition dataReady;  // Condition variable to signal data readiness

EventBuilder &eventBuilder;

public:
    NetworkThread(EventBuilder &builder, QObject *parent = nullptr) : QThread(parent), eventBuilder(builder), stopped(false) {}

    void run() override
    {
        QUdpSocket udpSocket;
       //udpSocket.bind(QHostAddress::Any, 12345); // Set your desired port
        // Bind the socket to a specific IP address and port
        if ( udpSocket.bind(QHostAddress("127.0.0.1"), serverPort) )
        {
           // connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
            qInfo() << "UDP server started on port" << serverPort;
        }
        else
        {
            stopped = true;
            qWarning() << "Failed to bind UDP socket on port" << serverPort;
        }

        while (!stopped)
        {
            // Your data serialization and broadcasting logic here


            QByteArray data = eventBuilder.getNextData(); // Get data from the EventBuilder
            if (!data.isEmpty())
            {
                QString dataString = QString(data);
                udpSocket.writeDatagram(data.data(), data.size(), QHostAddress::Broadcast, serverPort);
            //    std::cerr << dataString.toStdString() << std::endl;
            }
            else
            {
             //   std::cerr << "data is empty" << std::endl;

            }
          //  QByteArray data = serializeYourData();


          //  QTime currentTime = QTime::currentTime();
            // Calculate the time since midnight in milliseconds
          //  int millisecondsSinceMidnight = currentTime.msecsSinceStartOfDay();

 //           QByteArray data; // Create a QByteArray for your data
            // Populate data with your custom data
         //   data.append(QByteArray::number(millisecondsSinceMidnight));

         //   udpSocket.writeDatagram(data.data(),data.size(), QHostAddress::Broadcast, serverPort); // Broadcast to all reachable devices
 //           emit dataReady(data); // Emit the signal when data is ready
 //           std::cerr  << " running" << std::endl;
//            QThread::msleep(1); // Sleep for  microseconds usleep / millisecond msleep  //!!!!! on windows the minimum is about 15ms from OS reasons. ~ 30 microseconds between loops without thread sleep.

        }
    }

    void stopThread()
    {
        stopped = true;
        emit terminationRequested();
    }
    // Add this public slot to receive data from the main thread
public slots:

signals:
    void terminationRequested();

private:
    bool stopped;

    QByteArray serializeYourData()
    {
        // Implement your data serialization here
    }
};

/*
#include <QThread>
#include <QUdpSocket>
#include <QMutex>
#include <QWaitCondition>
#include <QTime>

class NetworkThread : public QThread
{
    Q_OBJECT

private:
    quint16 serverPort = 1901;    // Port number for the UDP server
    double intensity = 0.0, position = 0.0, focus = 0.0;

    QMutex mutex;               // Mutex for data synchronization
    QWaitCondition dataReady;  // Condition variable to signal data readiness

public:
    NetworkThread(QObject *parent = nullptr) : QThread(parent), stopped(false) {}

    void run() override
    {
        QUdpSocket udpSocket;

        if (udpSocket.bind(QHostAddress("10.0.7.1"), serverPort))
        {
            qInfo() << "UDP server started on port" << serverPort;
        }
        else
        {
            stopped = true;
            qWarning() << "Failed to bind UDP socket on port" << serverPort;
        }

        while (!stopped)
        {
            // Wait for data to be ready
            mutex.lock();
            dataReady.wait(&mutex);
            // Data is now ready, unlock the mutex

            QTime currentTime = QTime::currentTime();
            int millisecondsSinceMidnight = currentTime.msecsSinceStartOfDay();

            QByteArray data;
            data.append(QByteArray::number(millisecondsSinceMidnight));

            // Append the updated parameters to the data
            data.append(",");
            data.append(QByteArray::number(intensity));
            data.append(",");
            data.append(QByteArray::number(position));
            data.append(",");
            data.append(QByteArray::number(focus));

            udpSocket.writeDatagram(data.data(), data.size(), QHostAddress::Broadcast, serverPort);
            mutex.unlock();
        }
    }

    void stopThread()
    {
        stopped = true;
        emit terminationRequested();
    }

public slots:
    // This slot is called from another thread to update the parameters
    void updateParameters(double newIntensity, double newPosition, double newFocus)
    {
        // Lock the mutex before updating the parameters
        mutex.lock();

        // Update the parameters
        intensity = newIntensity;
        position = newPosition;
        focus = newFocus;

        // Signal that data is ready to be sent
        dataReady.wakeAll();

        // Unlock the mutex
        mutex.unlock();
    }

signals:
    void terminationRequested();

private:
    bool stopped;
};


*/

#endif // NETWORKTHREAD_H
