#include "dialoghostip.h"
#include "ui_dialoghostip.h"
#include "helpers.h"

#include <QStringList>




DialogHostIp::DialogHostIp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHostIp)
{
    ui->setupUi(this);
}

DialogHostIp::~DialogHostIp()
{
    delete ui;
}


//***************** Initialization ******************

void DialogHostIp::showEvent(QShowEvent * event)
{
    if (!event->spontaneous())
        if (deviceSettings != NULL)
        {
            top(deviceSettings);
            deviceSettings->beginGroup("Global");

            QString ip = deviceSettings->value("HostIp", QString("0.0.0.0")).toString();
            ui->lineIp->setText(ip);

        }
    QDialog::showEvent(event);
}

//***************** Processing ******************

void DialogHostIp::accept()
{
//    qInfo("Accepted!");

    if (validateAndSave())
        QDialog::accept();
}

int DialogHostIp::validateAndSave()
{
    if (deviceSettings == NULL)
        return 0;

    QString user_data = ui->lineIp->text();
    QString generated = ip2num(user_data);

        //if the strings are identical, save the value and return 1
    if (generated.compare(user_data) == 0)
    {
        top(deviceSettings);
        deviceSettings->beginGroup("Global");

        deviceSettings->setValue("HostIp", generated);
        return 1;
    }
    else
        //if not, display the parsed value and return 0
    {
        ui->lineIp->setText(generated);
        return 0;
    }

}
