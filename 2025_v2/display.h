#ifndef DISPLAY_H
#define DISPLAY_H

#include <QDialog>
#include <QVector>
#include <QRadioButton>
#include <QButtonGroup>
#include <QCheckBox>
#include <QLCDNumber>

namespace Ui {
class display;
}

class BPMDisplay : public QDialog {
    Q_OBJECT

public:
    explicit BPMDisplay(QWidget *parent = nullptr);
    ~BPMDisplay();

    void plot(const QVector<signed short> &raw_data, const QVector<unsigned short> &cal_data);
    void setTitle(QString title);

    QVector<signed short> rawBuffer;
    QVector<unsigned short> calBuffer;

public slots:
    void showEvent(QShowEvent *event);
    void onDataToggleChanged(int state);

protected:
    int nrPoints = 0;
    QVector<double> dataX;
    QVector<double> dataY;

private:
    Ui::display *ui;

    QCheckBox *checkBoxShowCalibrated;
    bool showCalibrated = true;

    void setupUI();
};

#endif // DISPLAY_H
