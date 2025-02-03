#ifndef DIALOGTRIGGERSETTINGS_H
#define DIALOGTRIGGERSETTINGS_H

#include <QDialog>
#include <QSettings>
#include <QShowEvent>

namespace Ui {
class DialogTriggerSettings;
}

class DialogTriggerSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTriggerSettings(QWidget *parent = 0);
    ~DialogTriggerSettings();
    QSettings* deviceSettings = NULL;

public slots:
    void showEvent(QShowEvent *event);
    void accept();

protected:
    int validateAndSave();
    void updateCalculations();
    int data_ok = 0;

private slots:
    void on_spinPeriodTicks_valueChanged(int arg1);

    void on_spinTintTicks_valueChanged(int arg1);

    void on_spinPeriodTicks_v2_valueChanged(int arg1);

    void on_spinTintTicks_v2_valueChanged(int arg1);

private:
    Ui::DialogTriggerSettings *ui;
};

#endif // DIALOGTRIGGERSETTINGS_H
