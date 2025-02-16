#ifndef DIALOGLINEARITY_H
#define DIALOGLINEARITY_H

#include <QDialog>
#include <QVector>
#include <QList>
#include "hw.h"
#include "keithley_thr.h"
#include "histogram.h"
#include "helpers.h"

typedef struct
{
    double vled;
    double ipd;
    QVector<double> mean;
    QVector<double> std;
} TestResult;


namespace Ui {
class DialogLinearity;
}

class DialogLinearity : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLinearity(QWidget *parent = 0);
    ~DialogLinearity();
    HW* theHW;
    keithley_thr* theKeithley;

public slots:
    void onHistogramCompleted();
protected:
    int runState;
    int histoReady;
    QList<TestResult> results;

    void run();
private slots:
    void on_pushRun_pressed();

    void on_pushSave_pressed();

private:
    Ui::DialogLinearity *ui;
};

#endif // DIALOGLINEARITY_H
