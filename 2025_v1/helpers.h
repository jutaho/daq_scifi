#ifndef HELPERS_H
#define HELPERS_H

#include <QString>
#include <QStringList>
#include <QSettings>
#include <QTimer>
#include <QCoreApplication>
#include <QThread>
#include <QList>
#include <QVector>
#include <QFile>
#include <QTextStream>

    //byte array <-> unsiged short conversion
#define SHORT2BYTES(sh,by)  {by[0] = (sh>>8) & 0xFF; by[1] = sh & 0xFF;}
#define LO(x)               (x & 0xFF)
#define HI(x)               ((x>>8) & 0xFF)
#define BYTES2SHORT(by)     ( ((unsigned short)(unsigned char)((by)[0]) << 8) | ((unsigned short)(unsigned char)((by)[1])) )    //safe way
#define BYTES2SIGNSHORT(by)     ( *((signed short*)by) )                                          //faster
#define BYTES2SIGNEDSHORT(by) \
    ( \
        (static_cast<short>(static_cast<unsigned char>((by)[0])) << 8) | \
        (static_cast<short>(static_cast<unsigned char>((by)[1]))) \
        )
    //convert textual representation of IP to array of numbers and/or well-formatted string
QString ip2num(QString input, unsigned char* numbers = NULL);

    //go to the main branch of settings
void top (QSettings* settings);

    //copy settings table
void copyQSettings(QSettings* from, QSettings* to);

    //sleep with processing queues
void msleep2(unsigned int ms, unsigned int resolution = 10);

    //Save data in form of CSV file. The three tables should have the same number of rows. They will be concatenated. Sensormean and sensorstd will be interlaced.
void saveCsvFile(QString filename, QList<QVector<double>> params, QList<QVector<double>> sensormean, QList<QVector<double>> sensorstd, QString delimiter = QString(","));

#endif // HELPERS_H

