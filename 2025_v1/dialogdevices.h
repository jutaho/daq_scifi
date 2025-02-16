#ifndef DIALOGDEVICES_H
#define DIALOGDEVICES_H

#include <QDialog>
#include <QSettings>
#include <QShowEvent>

namespace Ui {
class DialogDevices;
}

class DialogDevices : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDevices(QWidget *parent = 0);
    ~DialogDevices();
    QSettings* deviceSettings = NULL;

public slots:
    void showEvent(QShowEvent *event);
    void accept();
protected:
    int validateAndSave();
    void importSettings();
    int last_nr_devices = -1;
    int initialized = 0;
private slots:
    void on_spinNrDevices_valueChanged(int arg1);

private:
    Ui::DialogDevices *ui;
};

#endif // DIALOGDEVICES_H
