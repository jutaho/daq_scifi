#include "helpers.h"

QString ip2num(QString input, unsigned char* numbers)
{
    QStringList ip_sl = input.split(".");
    unsigned char ip_arr[4];
    for (int i = 0; i < 4; i++)
        if (i < ip_sl.length())
            ip_arr[i] = (unsigned char) ip_sl.at(i).toInt();
        else
            ip_arr[i] = 0;

    QString generated = QString("%1.%2.%3.%4")
                                .arg(ip_arr[0])
                                .arg(ip_arr[1])
                                .arg(ip_arr[2])
                                .arg(ip_arr[3]);

    if (numbers)
    {
        for (int i = 0; i < 4; i++)
            numbers[i] = ip_arr[i];
    }

    return generated;
}

void top (QSettings* settings)
{
    while(settings->group().length() != 0)
        settings->endGroup();
}


void copyQSettingsHelper(QSettings* from, QSettings* to)
{
        //copy own keys
    QStringList keys = from->childKeys();
    for(int i = 0; i < keys.length(); i++)
    {
       to->setValue(keys[i], from->value(keys[i]));
    }

        //recursively copy child groups
    QStringList groups = from->childGroups();
    for(int i = 0; i < groups.length(); i++)
    {
       from->beginGroup(groups[i]);
       to->beginGroup(groups[i]);

       copyQSettingsHelper(from, to);

       from->endGroup();\
       to->endGroup();
    }
}

void copyQSettings(QSettings* from, QSettings* to)
{
    to->clear();
    top(from);

    copyQSettingsHelper(from, to);
}

void msleep2(unsigned int ms, unsigned int resolution)
{
    QTimer timer;
    timer.setSingleShot(1);
    timer.start(ms);
    while(timer.isActive())
    {
        QCoreApplication::processEvents();
        QThread::msleep(resolution);
    }
}

void saveCsvFile(QString filename, QList<QVector<double>> params, QList<QVector<double>> sensormean, QList<QVector<double>> sensorstd, QString delimiter)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << qSetFieldWidth(14) << qSetRealNumberPrecision(8);
    for (int row = 0; (row < params.length()) && (row < sensormean.length()) && (row < sensorstd.length()); row++)
    {
        int col;
        for (col = 0; col < params[row].length(); col++)
            out << params[row][col] << delimiter;\

        for (col = 0; (col < (sensormean[row].length() - 1)) && (col < (sensorstd[row].length() - 1)); col++)
            out << sensormean[row][col] << delimiter << sensorstd[row][col] << delimiter;
        out << sensormean[row][col+1] << delimiter << sensorstd[row][col+1] << QString("\n");
    }

    file.close();
}
