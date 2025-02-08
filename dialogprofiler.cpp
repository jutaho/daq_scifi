#include "dialogprofiler.h"
#include "ui_dialogprofiler.h"

#define RUNNING 1
#define STOPPED 0
#define STOP_ISSUED -1

DialogProfiler::DialogProfiler(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProfiler)
{
    ui->setupUi(this);
    runState = STOPPED;
    nrRunsDone = 0;
}

DialogProfiler::~DialogProfiler()
{
    delete ui;
}

//************** Processing ***************

void DialogProfiler::run(int nr_loops)
{
    runState = RUNNING;
    qInfo("Starting profile acquisition");

        //Prepare measurement
    ui->plotResultsMean->clearGraphs();
    ui->plotResultsStd->clearGraphs();

    int nr_devices = theHW->devices.length();
    int nacqs = ui->spinAcquisitions->value();

        //Data structures for plot
    QVector<double> xdata;
    QVector<double> ymeandata;
    QVector<double> ystddata;

    ui->plotResultsMean->addGraph();
    ui->plotResultsStd->addGraph();

    for (int ch = 0; ch < nr_devices*128; ch++)
        xdata.append(ch);

    double ymeanmin = 1e+10;
    double ymeanmax = -1e+10;
    double ystdmin = 1e+10;
    double ystdmax = -1e+10;

        //Measure!
    int loop_nr = 0;
    while ((runState != STOP_ISSUED) && ((loop_nr < nr_loops) || (nr_loops == -1)))
    {
        ProfilerTestResult result;

            //Collect sensor data
        histoReady = 0;
        connect(&(theHW->eventBuilder), &EventBuilder::sigHistoCompleted, this, &DialogProfiler::onHistogramCompleted);
        theHW->eventBuilder.startTakingHistos(nacqs);
        while (!histoReady)
        {
             QCoreApplication::processEvents();
             QThread::msleep(10);
        }
        disconnect(&(theHW->eventBuilder), &EventBuilder::sigHistoCompleted, this, &DialogProfiler::onHistogramCompleted);
        QVector<Histogram> histos = theHW->eventBuilder.getHistos();

        result.mean.fill(0, nr_devices*128);
        result.std.fill(0, nr_devices*128);
        for (int i = 0; i < result.mean.length(); i++)
        {
            histos[i].MS(&(result.mean[i]), &(result.std[i]));
        }

            //Add LED/PD information
        result.nracqs = nacqs;
        results.append(result);

            //Plot data...
        ymeandata.clear();
        ymeandata.fill(0, nr_devices*128);
        ystddata.clear();
        ystddata.fill(0,nr_devices*128);
        for (int ch = 0; ch < (nr_devices*128); ch++)
        {
            ymeandata[ch] = result.mean[ch];
            if (result.mean[ch] > ymeanmax)
                ymeanmax = result.mean[ch];
            if (result.mean[ch] < ymeanmin)
                ymeanmin = result.mean[ch];
            ystddata[ch] = result.std[ch];
            if (result.std[ch] > ystdmax)
                ystdmax = result.std[ch];
            if (result.std[ch] < ystdmin)
                ystdmin = result.std[ch];
        }

        ui->plotResultsMean->xAxis->setRange(0, nr_devices*128-1);
        ui->plotResultsMean->yAxis->setRange(ymeanmin, ymeanmax);
        ui->plotResultsStd->xAxis->setRange(0, nr_devices*128-1);
        ui->plotResultsStd->yAxis->setRange(ystdmin, ystdmax);

        ui->plotResultsMean->graph(0)->setData(xdata, ymeandata);
        ui->plotResultsStd->graph(0)->setData(xdata, ystddata);

        ui->plotResultsMean->replot();
        ui->plotResultsStd->replot();

            //Roll over
        loop_nr++;
        nrRunsDone++;
        ui->lineRunsDone->setText(QString("%1").arg(nrRunsDone));
        QCoreApplication::processEvents();
    }

    qInfo("Profile acquisition finished!");
    runState = STOPPED;
}


void DialogProfiler::runHelper(int nr_loops)
{
    if (runState)
    {
        runState = STOP_ISSUED;
    }
    else
    {
        ui->pushRun->setText("Stop");
        ui->pushRunOnce->setEnabled(false);
        ui->pushRunInfinite->setEnabled(false);
        ui->pushClear->setEnabled(false);
        ui->pushSave->setEnabled(false);
        run(nr_loops);
        ui->pushRun->setText("Run");
        ui->pushRunOnce->setEnabled(true);
        ui->pushRunInfinite->setEnabled(true);
        ui->pushClear->setEnabled(true);
        ui->pushSave->setEnabled(true);
    }
}

//************** Slots ****************

void DialogProfiler::onHistogramCompleted()
{
    histoReady = 1;
}

void DialogProfiler::on_pushRun_pressed()
{
    runHelper(ui->spinRuns->value());
}

void DialogProfiler::on_pushRunOnce_pressed()
{
    runHelper(1);
}

void DialogProfiler::on_pushRunInfinite_pressed()
{
    runHelper(-1);
}

void DialogProfiler::on_pushSave_pressed()
{
    QString filename = QFileDialog::getSaveFileName(this, "Select file for saving data", "", tr("Comma separated files (*.csv)"));
    QString delimiter = QString(",");

    if (filename.length() == 0)
        return;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << qSetFieldWidth(14) << qSetRealNumberPrecision(8);
    for (int row = 0; row < results.length(); row++)
    {
        out << results[row].nracqs;

        for (int col = 0; (col < results[row].mean.length()) && (col < results[row].std.length()); col++)
            out << delimiter << results[row].mean[col] << delimiter << results[row].std[col];
        out << QString("\n");
    }

    file.close();
}


void DialogProfiler::on_pushClear_pressed()
{
    nrRunsDone = 0;
    results.clear();
    ui->lineRunsDone->setText(QString("%1").arg(nrRunsDone));
}
