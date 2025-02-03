#ifndef DISPLAY_H
#define DISPLAY_H

#include <QDialog>
#include <QVector>
#include <QRadioButton>
#include <QButtonGroup>
#include <QTextStream>
#include <QFile>
#include <QCheckBox>
#include <QLCDNumber>

namespace Ui {
class display;
}

class BPMDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit BPMDisplay(QWidget *parent = 0);
    ~BPMDisplay();


    void plot(const QVector<signed short> &data);
    void plot();
    void plot(const QVector<signed short> &data, const QVector<signed short> &rmsdata);

    void setTitle(QString title);

    QVector<signed short> buffer;
    QVector<signed short> rmsbuffer;


public slots:
    void showEvent(QShowEvent *event);
    void onButtonClicked(QAbstractButton *button);
    void onSaveBackgroundClicked();
    void onLoadBackgroundClicked();
    void onCheckBoxStateChanged(int state);
    void onSaveCalibrationClicked();
    void onLoadCalibrationClicked();
    void onCalibrationCheckBoxChanged(int state);
    void onExpertModeStateChanged(int state);
    void updateMean(unsigned short value);
    void updateRms(unsigned short value);
    void updateMax(unsigned short value);
    void updateStatus(unsigned short value);



protected:
    int nrPoints = 0;
    QVector<double> dataX;
    QVector<double> dataY;
    QVector<signed short> dataRMS;


private:
    Ui::display *ui;
    QRadioButton *radioButtonFixedScale; // Pointer to the Fixed Scale radio button
    QRadioButton *radioButtonAutoscale;  // Pointer to the Autoscale radio button
    QButtonGroup *buttonGroup;
    QMap<QString, QVector<signed short>> backgroundDataMap; // Map to store background data for each plane
    bool subtractBackground = false; // Flag to track if background subtraction is enabled

    QMap<QString, QVector<float>> calibrationDataMap; // Map to store calibration data for each plane
    bool applyCalibration = false; // Flag to track if calibration should be applied
    QVector<float> calibrationData; // Stores the loaded calibration data
    QCheckBox *checkBoxExpertMode; // Expert Mode checkbox
    bool expertModeEnabled = false; // Flag to track if expert mode is enabled
    QLCDNumber * lcdNumber_mean;
    QLCDNumber * lcdNumber_focus;
    QLCDNumber * lcdNumber_max;
    QLCDNumber * lcdNumber_status;

};

#endif // DISPLAY_H
