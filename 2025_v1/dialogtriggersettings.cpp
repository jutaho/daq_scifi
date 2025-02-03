#include "dialogtriggersettings.h"
#include "ui_dialogtriggersettings.h"
#include "helpers.h"

DialogTriggerSettings::DialogTriggerSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTriggerSettings)
{
    ui->setupUi(this);
}

DialogTriggerSettings::~DialogTriggerSettings()
{
    delete ui;
}

//***************** Initialization ******************

void DialogTriggerSettings::showEvent(QShowEvent * event)
{
    if (!event->spontaneous())
    {
        if (deviceSettings != NULL)
        {
            top(deviceSettings);
            deviceSettings->beginGroup("Trigger");

            ui->spinPeriodTicks->setValue( deviceSettings->value("Period", (int)9000).toInt() );
            ui->spinTintTicks->setValue( deviceSettings->value("Tint", (int)1000).toInt() );
            if (deviceSettings->value("Gain", (int)0).toInt() == 0)
                ui->radioLow->setChecked(true);
            else
                ui->radioHigh->setChecked(true);

            ui->spinPeriodTicks_v2->setValue( deviceSettings->value("Period_v2", (double)2500).toDouble() );
            ui->spinTintTicks_v2->setValue( deviceSettings->value("Tint_v2", (int)1000).toInt() );
            if (deviceSettings->value("Gain_v2", (int)0).toInt() == 0)
                ui->radioLow_v2->setChecked(true);
            else
                ui->radioHigh_v2->setChecked(true);

        }
        updateCalculations();
    }

    QDialog::showEvent(event);
}

//***************** Processing ******************

void DialogTriggerSettings::accept()
{
//    qInfo("Accepted!");

    if (validateAndSave())
        QDialog::accept();
}

int DialogTriggerSettings::validateAndSave()
{
    if (deviceSettings == NULL)
        return 0;

    if (!data_ok)
        return 0;

    top(deviceSettings);
    deviceSettings->beginGroup("Trigger");

    deviceSettings->setValue("Period", ui->spinPeriodTicks->value());
    deviceSettings->setValue("Tint", ui->spinTintTicks->value());
    if (ui->radioHigh->isChecked())
        deviceSettings->setValue("Gain", 1);
    else
        deviceSettings->setValue("Gain", 0);

    deviceSettings->setValue("Period_v2", ui->spinPeriodTicks_v2->value());
    deviceSettings->setValue("Tint_v2", ui->spinTintTicks_v2->value());
    if (ui->radioHigh_v2->isChecked())
        deviceSettings->setValue("Gain_v2", 1);
    else
        deviceSettings->setValue("Gain_v2", 0);

    return 1;
}

void DialogTriggerSettings::updateCalculations()
{
    data_ok = 1;

    // ***** V1 *****

    double period_us = (double)(ui->spinPeriodTicks->value()+1) / 90.0;
    ui->linePeriodUs->setText(QString("%1").arg(period_us, 0, 'f', 2));

    double freq_kHz = 1e+3/period_us;
    ui->lineFreqKhz->setText((QString("%1").arg(freq_kHz, 0, 'f', 3)));

    ui->linePeriodOK->setText("OK");

    double tint_us = (double)(ui->spinTintTicks->value()+1) / 90.0; //45.0;
    ui->lineTintUs->setText(QString("%1").arg(tint_us, 0, 'f', 2));

    if (tint_us > (period_us - (20.0/4)))
    {
        ui->lineTintOK->setText("Too long!");
        data_ok = 0;
    }
    else
        ui->lineTintOK->setText("OK");

    // ***** V2 *****

    double period_us_v2 = (double)(ui->spinPeriodTicks_v2->value()+1) / 25.0;
    ui->linePeriodUs_v2->setText(QString("%1").arg(period_us_v2, 0, 'f', 2));

    double freq_kHz_v2 = 1e+3/period_us_v2;
    ui->lineFreqKhz_v2->setText((QString("%1").arg(freq_kHz_v2, 0, 'f', 3)));

    ui->linePeriodOK_v2->setText("OK");

    double tint_us_v2 = (double)(ui->spinTintTicks_v2->value()+1) / (50.0/14.0); //makes these 3.5714... MHz
    ui->lineTintUs_v2->setText(QString("%1").arg(tint_us_v2, 0, 'f', 2));

    if (tint_us_v2 > (period_us_v2 - (20.0/(50.0/14.0))))
    {
        ui->lineTintOK_v2->setText("Too long!");
        data_ok = 0;
    }
    else
        ui->lineTintOK_v2->setText("OK");



}

void DialogTriggerSettings::on_spinPeriodTicks_valueChanged(int arg1)
{
    updateCalculations();
}

void DialogTriggerSettings::on_spinTintTicks_valueChanged(int arg1)
{
    updateCalculations();
}

void DialogTriggerSettings::on_spinPeriodTicks_v2_valueChanged(int arg1)
{
    updateCalculations();
}

void DialogTriggerSettings::on_spinTintTicks_v2_valueChanged(int arg1)
{
    updateCalculations();
}
