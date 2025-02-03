#ifndef DIALOGHOSTIP_H
#define DIALOGHOSTIP_H

#include <QDialog>
#include <QSettings>
#include <QShowEvent>

namespace Ui {
class DialogHostIp;
}

class DialogHostIp : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHostIp(QWidget *parent = 0);
    ~DialogHostIp();
    QSettings* deviceSettings = NULL;

public slots:
    void showEvent(QShowEvent *event);
    void accept();
protected:
    int validateAndSave();
private slots:


private:
    Ui::DialogHostIp *ui;
};

#endif // DIALOGHOSTIP_H
