#ifndef DISPLAY_H
#define DISPLAY_H

#include <QDialog>
#include <QVector>
#include <QCheckBox>

namespace Ui {
class display;
}

class BPMDisplay : public QDialog {
    Q_OBJECT

public:
    explicit BPMDisplay(QWidget *parent = nullptr);
    ~BPMDisplay();

    // Raw data is unsigned short; Cal data is signed short
    void plot(const QVector<unsigned short> &raw_data,
              const QVector<signed short>   &cal_data);

    void setTitle(QString title);

    // Buffers also reflect raw = unsigned, cal = signed
    QVector<unsigned short> rawBuffer;
    QVector<signed short>   calBuffer;

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
    bool showCalibrated;

    void setupUI();
};

#endif // DISPLAY_H
