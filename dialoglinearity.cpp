#include "dialoglinearity.h"
#include "ui_dialoglinearity.h"

#define RUNNING 1
#define STOPPED 0
#define STOP_ISSUED -1

DialogLinearity::DialogLinearity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLinearity)
{
    ui->setupUi(this);
    runState = STOPPED;
}

DialogLinearity::~DialogLinearity()
{
    delete ui;
}

//************** Processing ***************

void DialogLinearity::run()
{
    runState = RUNNING;
    qInfo("Starting linearity test...");

        //Prepare measurement
    ui->plotResultsMean->clearGraphs();
    ui->plotResultsStd->clearGraphs();
    results.clear();
    int nr_devices = theHW->devices.length();

    int decimation = ui->spinPLotDecimation->value();
    int tdelay = ui->spinDelay->value();
    int nacqs = ui->spinAcquisitions->value();
    double vstart = ui->doubleSpinVstart->value();
    double vend = ui->doubleSpinVend->value();
    double vinc = ui->doubleSpinVinc->value();
    double vcurrent = vstart;

        //Plot data
    QVector<double> xdata;
    QList<QVector<double>> ymeandata;
    QList<QVector<double>> ystddata;
    for (int ch = 0; ch < (nr_devices*128); ch+= decimation)
    {
        ymeandata.append(xdata);    //just add empty vectors to the list
        ystddata.append(xdata);    //just add empty vectors to the list
    }

        //The number of plotted lines is smaller than number of channels - see decimation
    for (int plotnr = 0; plotnr < nr_devices*128; plotnr++)
    {
        ui->plotResultsMean->addGraph();
        ui->plotResultsStd->addGraph();
    }

    double xmin = 1e+10;
    double xmax = -1e+10;
    double ymeanmin = 1e+10;
    double ymeanmax = -1e+10;
    double ystdmin = 1e+10;
    double ystdmax = -1e+10;

    theKeithley->setVoltage(vcurrent);
    theKeithley->on(1);

        //Measure!
    while ((runState != STOP_ISSUED) && (vcurrent <= vend))
    {
            //Set LED voltage
        qInfo(qPrintable(QString("LED voltage: %1 V").arg(vcurrent)));
        theKeithley->setVoltage(vcurrent);

            //Wait
        msleep2(tdelay);

        TestResult result;

            //Collect sensor data
        histoReady = 0;
        connect(&(theHW->eventBuilder), &EventBuilder::sigHistoCompleted, this, &DialogLinearity::onHistogramCompleted);
        theHW->eventBuilder.startTakingHistos(nacqs);
        while (!histoReady)
        {
             QCoreApplication::processEvents();
             QThread::msleep(10);
        }
        disconnect(&(theHW->eventBuilder), &EventBuilder::sigHistoCompleted, this, &DialogLinearity::onHistogramCompleted);
        QVector<Histogram> histos = theHW->eventBuilder.getHistos();

        result.mean.fill(0, nr_devices*128);
        result.std.fill(0, nr_devices*128);
        for (int i = 0; i < result.mean.length(); i++)
        {
            histos[i].MS(&(result.mean[i]), &(result.std[i]));
            //result.mean[i] = histos[i].mean();
            //result.std[i] = histos[i].stdev();
        }


            //Add LED/PD information
        result.vled = vcurrent;
        result.ipd = theKeithley->getCurrent();
        results.append(result);

            //Plot data...
        xdata.append(result.ipd);
        if (result.ipd > xmax)
            xmax = result.ipd;
        if (result.ipd < xmin)
            xmin = result.ipd;

        for (int ch = 0, i = 0; ch < (nr_devices*128); ch+= decimation, i++)
        {
            ymeandata[i].append(result.mean[ch]);
            if (result.mean[ch] > ymeanmax)
                ymeanmax = result.mean[ch];
            if (result.mean[ch] < ymeanmin)
                ymeanmin = result.mean[ch];
            ystddata[i].append(result.std[ch]);
            if (result.std[ch] > ystdmax)
                ystdmax = result.std[ch];
            if (result.std[ch] < ystdmin)
                ystdmin = result.std[ch];
        }

        ui->plotResultsMean->xAxis->setRange(xmin, xmax);
        ui->plotResultsMean->yAxis->setRange(ymeanmin, ymeanmax);
        ui->plotResultsStd->xAxis->setRange(xmin, xmax);
        ui->plotResultsStd->yAxis->setRange(ystdmin, ystdmax);

        for (int ch = 0, i = 0; ch < (nr_devices*128); ch+= decimation, i++)
        {
            ui->plotResultsMean->graph(i)->setData(xdata, ymeandata[i]);
            ui->plotResultsStd->graph(i)->setData(xdata, ystddata[i]);
        }

        ui->plotResultsMean->replot();
        ui->plotResultsStd->replot();

            //Roll over
        vcurrent += vinc;
        QCoreApplication::processEvents();
    }


    theKeithley->on(0);

    qInfo("Linearity test finished!");
    runState = STOPPED;
}


//************** Slots ****************

void DialogLinearity::onHistogramCompleted()
{
    histoReady = 1;
}

void DialogLinearity::on_pushRun_pressed()
{
    if (runState)
    {
        runState = STOP_ISSUED;
    }
    else
    {
        ui->pushRun->setText("Stop");
        ui->pushSave->setEnabled(false);
        run();
        ui->pushRun->setText("Run");
        ui->pushSave->setEnabled(true);
    }

}

void DialogLinearity::on_pushSave_pressed()
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
        out << results[row].vled << delimiter << results[row].ipd;

        for (int col = 0; (col < results[row].mean.length()) && (col < results[row].std.length()); col++)
            out << delimiter << results[row].mean[col] << delimiter << results[row].std[col];
        out << QString("\n");
    }

    file.close();
}
