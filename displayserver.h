#ifndef DISPLAYSERVER_H
#define DISPLAYSERVER_H

#include <QObject>
#include <QVector>
#include "hw.h"
#include "display.h"


typedef struct
{
    int nr;
    QString name;
    int nr_sensors; //this is commonly 2*nr_devices or 2*nr_devices-1
    int nr_devices;
    QVector<Device*> devices;
} PlaneConfig;


class DisplayServer : public QObject
{
    Q_OBJECT
public:
    explicit DisplayServer(QObject *parent = 0);

    void setup(HW *hw);
    void show();
    void hide();
    void plot();
    int isActive();
    ~DisplayServer();
    void unsetup();
signals:

public slots:

protected:
    int active = 0;
    HW* theHW;
    QVector<PlaneConfig*> planeConfig;
    QVector<BPMDisplay*> displays;

    PlaneConfig *findPlane(int plane_nr);
};

#endif // DISPLAYSERVER_H
