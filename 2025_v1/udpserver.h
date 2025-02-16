#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QVector>
#include <QThread>
#include <QUdpSocket>

class UDPServer : public QObject
{
    Q_OBJECT

private:
    QUdpSocket* udpSocket; // UDP socket for communication
    quint16 serverPort = 12345;    // Port number for the UDP server

public:
    UDPServer(QObject* parent = nullptr) : QObject(parent)
    {
        // Initialize and configure your UDP server here

    }

public slots:
    void startServer()
    {
        // Start your UDP server here
        udpSocket = new QUdpSocket(this);

        // Bind the socket to a specific IP address and port
        if ( udpSocket->bind(QHostAddress("10.0.7.1"), serverPort) )
        {
            connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
            qDebug() << "UDP server started on port" << serverPort;
        }
        else
        {
            qWarning() << "Failed to bind UDP socket on port" << serverPort;
        }
    }

    void stopServer()
    {
        // Stop your UDP server here
        if (udpSocket)
        {
            udpSocket->close();
            udpSocket->deleteLater();
        }
        qDebug() << "UDP server stopped";
    }

    // Add any other methods and signals relevant to your UDP server
};

#endif // UDPSERVER_H
