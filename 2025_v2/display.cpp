#include "display.h"
#include "ui_display.h"
#include <QVBoxLayout>
#include "qcustomplot.h"

BPMDisplay::BPMDisplay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::display)
    , showCalibrated(true)
{
    ui->setupUi(this);
    setupUI();
}

BPMDisplay::~BPMDisplay()
{
    delete ui;
}

void BPMDisplay::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    checkBoxShowCalibrated = new QCheckBox("Show Calibrated Data", this);
    checkBoxShowCalibrated->setChecked(true);
    connect(checkBoxShowCalibrated, &QCheckBox::stateChanged,
            this, &BPMDisplay::onDataToggleChanged);

    mainLayout->addWidget(checkBoxShowCalibrated);
    mainLayout->addWidget(ui->plotWidget);

    setLayout(mainLayout);
}

void BPMDisplay::setTitle(QString title)
{
    setWindowTitle(title);
}

void BPMDisplay::onDataToggleChanged(int state)
{
    showCalibrated = (state == Qt::Checked);
    // Re-plot with current data whenever the checkbox toggles
    plot(rawBuffer, calBuffer);
}

// IMPORTANT: Signature matches "display.h" now:
//    void plot(const QVector<unsigned short> &raw_data,
//              const QVector<signed short>   &cal_data)
void BPMDisplay::plot(const QVector<unsigned short> &raw_data,
                      const QVector<signed short>   &cal_data)
{
    // Keep local copies for re-plotting
    rawBuffer = raw_data;
    calBuffer = cal_data;

    dataX.resize(raw_data.size());
    dataY.resize(raw_data.size());

    for (int i = 0; i < raw_data.size(); ++i)
    {
        dataX[i] = i;  // x-axis is just sample index

        // If "Show Calibrated" is checked, plot cal_data; otherwise, plot raw_data
        dataY[i] = showCalibrated
                       ? static_cast<double>(cal_data[i])
                       : static_cast<double>(raw_data[i]);
    }

    ui->plotWidget->clearGraphs();
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(0)->setData(dataX, dataY);

    ui->plotWidget->xAxis->setLabel("Sample Number");
    ui->plotWidget->yAxis->setLabel(showCalibrated
                                        ? "Calibrated Data"
                                        : "Raw Data");

    ui->plotWidget->rescaleAxes();
    ui->plotWidget->replot();
}

void BPMDisplay::showEvent(QShowEvent *event)
{
    // On first show, plot with whatever data we have
    if (!event->spontaneous()) {
        plot(rawBuffer, calBuffer);
    }
    QDialog::showEvent(event);
}
