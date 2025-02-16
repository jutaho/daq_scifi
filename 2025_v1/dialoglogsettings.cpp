#include "dialoglogsettings.h"
#include "ui_dialoglogsettings.h"
#include "Q_DebugStream.h"

#include <QShowEvent>

DialogLogSettings::DialogLogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogSettings)
{
    ui->setupUi(this);
}

DialogLogSettings::~DialogLogSettings()
{
    delete ui;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void DialogLogSettings::showEvent(QShowEvent * event)
{
    if (!event->spontaneous())
    {
        ui->checkDisplayDebug->setChecked((bool)(displayMask & DS_DEBUG));
        ui->checkDisplayInfo->setChecked((bool)(displayMask & DS_INFO));
        ui->checkDisplayWarning->setChecked((bool)(displayMask & DS_WARNING));
        ui->checkDisplayCritical->setChecked((bool)(displayMask & DS_CRITICAL));
        ui->checkDisplayFatal->setChecked((bool)(displayMask & DS_FATAL));

        ui->checkDetailsDebug->setChecked((bool)(detailsMask & DS_DEBUG));
        ui->checkDetailsInfo->setChecked((bool)(detailsMask & DS_INFO));
        ui->checkDetailsWarning->setChecked((bool)(detailsMask & DS_WARNING));
        ui->checkDetailsCritical->setChecked((bool)(detailsMask & DS_CRITICAL));
        ui->checkDetailsFatal->setChecked((bool)(detailsMask & DS_FATAL));
    }
    QDialog::showEvent(event);
}


void DialogLogSettings::on_buttonGroup_buttonReleased(int arg1)
{
    displayMask = 0;
    if (ui->checkDisplayDebug->isChecked())     displayMask |= DS_DEBUG;
    if (ui->checkDisplayInfo->isChecked())      displayMask |= DS_INFO;
    if (ui->checkDisplayWarning->isChecked())   displayMask |= DS_WARNING;
    if (ui->checkDisplayCritical->isChecked())  displayMask |= DS_CRITICAL;
    if (ui->checkDisplayFatal->isChecked())     displayMask |= DS_FATAL;

    detailsMask = 0;
    if (ui->checkDetailsDebug->isChecked())     detailsMask |= DS_DEBUG;
    if (ui->checkDetailsInfo->isChecked())      detailsMask |= DS_INFO;
    if (ui->checkDetailsWarning->isChecked())   detailsMask |= DS_WARNING;
    if (ui->checkDetailsCritical->isChecked())  detailsMask |= DS_CRITICAL;
    if (ui->checkDetailsFatal->isChecked())     detailsMask |= DS_FATAL;
}
