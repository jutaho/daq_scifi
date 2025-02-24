#include "dialogbeta.h"
#include "ui_dialogbeta.h"
#include <QFileDialog>


#define RUNNING 1
#define STOPPED 0
#define STOP_ISSUED -1

DialogBeta::DialogBeta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBeta)
{
    ui->setupUi(this);
    runState = STOPPED;
    nrRunsDone = 0;
    maxSpeed = 1500;


}

DialogBeta::~DialogBeta()
{
    timer.stop();
    disconnect(&timer, &QTimer::timeout, this, &DialogBeta::onTimer);

    delete ui;
}

void DialogBeta::showEvent(QShowEvent * event)
{
    if (!event->spontaneous())
    {
        ui->spinScanSpeed->setMaximum(maxSpeed);
        ui->lineRunsDone->setText(QString("%1").arg(nrRunsDone));
            //data logging possible only if global data logging is switched off
        if (theHW->eventBuilder.isLogging())
            ui->checkSaveRawData->setEnabled(false);

        connect(&timer, &QTimer::timeout, this, &DialogBeta::onTimer);
        timer.start(250);
    }
}


//************** Processing ***************

void DialogBeta::run(QString raw_data_filename)
{
    runState = RUNNING;


        //Prepare measurement
    ui->plotResultsMean->clearGraphs();
    ui->plotResultsStd->clearGraphs();


    int nr_devices = theHW->devices.length();
    int start_pos = ui->spinStartPos->value();
    int end_pos = ui->spinEndPos->value();
    int scan_speed = ui->spinScanSpeed->value();

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

        //Set up stepper drive
    qInfo("Setting up stepper drive...");

    while (currentPosition != start_pos)
    {
         QCoreApplication::processEvents();
         QThread::msleep(10);
         if (runState == STOP_ISSUED)
         {
             theStepper->command_MST();
             runState = STOPPED;
             return;
         }
    }

        //Measure!
    qInfo("Scanning...");

    if (raw_data_filename.length())
        theHW->eventBuilder.startLogging(raw_data_filename);
    theHW->eventBuilder.startTakingHistos(-1);
    while ((runState != STOP_ISSUED) && (currentPosition != end_pos))
    {
        QCoreApplication::processEvents();
        QThread::msleep(10);
        if (runState == STOP_ISSUED)
        {
            theStepper->command_MST();
            runState = STOPPED;
            return;
        }
    }
    theHW->eventBuilder.stopTakingHistos();
    if (raw_data_filename.length())
        theHW->eventBuilder.stopLogging();

        //Process results
    qInfo("Processing data...");
    BetaTestResult result;

        //Collect sensor data
    QVector<Histogram> histos = theHW->eventBuilder.getHistos();

    result.mean.fill(0, nr_devices*128);
    result.std.fill(0, nr_devices*128);
    for (int i = 0; i < result.mean.length(); i++)
    {
        histos[i].MS(&(result.mean[i]), &(result.std[i]));
    }

        //Add other information
    result.nracqs = histos[0].getNrSamples();
    result.startpos = start_pos;
    result.endpos = end_pos;
    result.motorspeed = scan_speed;
        //Store result
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

    nrRunsDone++;
    ui->lineRunsDone->setText(QString("%1").arg(nrRunsDone));

    qInfo("Scan finished!");
    runState = STOPPED;
}

//************** Slots ****************

void DialogBeta::onHistogramCompleted()
{
    histoReady = 1;
}

void DialogBeta::on_pushRun_pressed()
{
    if (runState)
    {
        runState = STOP_ISSUED;
    }
    else
    {
        ui->pushRun->setText("Stop");
        ui->pushClear->setEnabled(false);
        ui->pushSave->setEnabled(false);

        QString raw_data_filename = QString("");
        if (ui->checkSaveRawData->isChecked())
            raw_data_filename = QFileDialog::getSaveFileName(this, "Select file for saving data", "", tr("Binary log files (*.dat)"));
        if (raw_data_filename.length())
        {
                //Make copy of current settings
            QString ini_filename = raw_data_filename/*.left(filename.lastIndexOf(QString("."))) */ + QString(".ini");
            QSettings* settings_copy = new QSettings(ini_filename,QSettings::IniFormat);
            copyQSettings (deviceSettings, settings_copy);
            settings_copy->sync();
            delete settings_copy;
        }


        run(raw_data_filename);

        ui->pushRun->setText("Run");
        ui->pushClear->setEnabled(true);
        ui->pushSave->setEnabled(true);
    }
}



void DialogBeta::on_pushSave_pressed()
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
        out << results[row].nracqs << delimiter
            << results[row].startpos << delimiter
            << results[row].endpos << delimiter
            << results[row].motorspeed;

        for (int col = 0; (col < results[row].mean.length()) && (col < results[row].std.length()); col++)
            out << delimiter << results[row].mean[col] << delimiter << results[row].std[col];
        out << QString("\n");
    }

    file.close();
}


void DialogBeta::on_pushClear_pressed()
{
    nrRunsDone = 0;
    results.clear();
    ui->lineRunsDone->setText(QString("%1").arg(nrRunsDone));
}

void DialogBeta::on_pushLeft_pressed()
{
    theStepper->command_ROL(maxSpeed);
}

void DialogBeta::on_pushLeft_released()
{
    theStepper->command_MST();
}

void DialogBeta::on_pushRight_pressed()
{
    theStepper->command_ROR(maxSpeed);
}

void DialogBeta::on_pushRight_released()
{
    theStepper->command_MST();
}

void DialogBeta::on_pushResetCtr_pressed()
{
    theStepper->command_SAP(STEPPER_SAP_ACTUAL_POSITION, 0);
}
