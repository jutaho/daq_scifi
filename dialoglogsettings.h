#ifndef DIALOGLOGSETTINGS_H
#define DIALOGLOGSETTINGS_H

#include <QDialog>

namespace Ui {
class DialogLogSettings;
}

class DialogLogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogSettings(QWidget *parent = 0);
    ~DialogLogSettings();

    int displayMask;
    int detailsMask;

private slots:
    void on_buttonGroup_buttonReleased(int arg1);
    void showEvent(QShowEvent *event);
private:
    Ui::DialogLogSettings *ui;
};

#endif // DIALOGLOGSETTINGS_H
