#ifndef DIALOGBETA_H
#define DIALOGBETA_H

#include <QDialog>
#include <QVector>
#include <QList>
#include <QTimer>
#include <QSettings>
#include "hw.h"
#include "histogram.h"
#include "helpers.h"

typedef struct
{
    int nracqs;
    int startpos;
    int endpos;
    int motorspeed;
    QVector<double> mean;
    QVector<double> std;
} BetaTestResult;


namespace Ui {
class DialogBeta;
}

class DialogBeta : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBeta(QWidget *parent = 0);
    ~DialogBeta();
    HW* theHW;
    QSettings* deviceSettings;

    int maxSpeed;
    int currentPosition;

public slots:
    void showEvent(QShowEvent *event);
    void onHistogramCompleted();
    void onTimer();
protected:
    int runState;
    int histoReady;
    int nrRunsDone;
    QList<BetaTestResult> results;
    QTimer timer;

    void run(QString raw_data_filename);
private slots:
    void on_pushRun_pressed();
    void on_pushSave_pressed();
    void on_pushClear_pressed();
    void on_pushLeft_pressed();
    void on_pushLeft_released();
    void on_pushRight_pressed();
    void on_pushRight_released();
    void on_pushResetCtr_pressed();

private:
    Ui::DialogBeta *ui;
};

#endif // DIALOGLINEARITY_H
