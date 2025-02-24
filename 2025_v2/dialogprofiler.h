#ifndef DIALOGPROFILER_H
#define DIALOGPROFILER_H

#include <QDialog>
#include <QVector>
#include <QList>
#include "hw.h"
#include "helpers.h"

typedef struct
{
    int nracqs;
    QVector<double> mean;
    QVector<double> std;
} ProfilerTestResult;


namespace Ui {
class DialogProfiler;
}

class DialogProfiler : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProfiler(QWidget *parent = 0);
    ~DialogProfiler();
    HW* theHW;

public slots:
    void onHistogramCompleted();
protected:
    int runState;
    int histoReady;
    int nrRunsDone;
    QList<ProfilerTestResult> results;

    void run(int nr_loops);
    void runHelper(int nr_loops);
private slots:
    void on_pushRun_pressed();

    void on_pushSave_pressed();

    void on_pushRunOnce_pressed();

    void on_pushRunInfinite_pressed();

    void on_pushClear_pressed();

private:
    Ui::DialogProfiler *ui;
};

#endif // DIALOGLINEARITY_H
