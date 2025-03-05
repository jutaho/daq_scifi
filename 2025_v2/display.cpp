#include "display.h"
#include "ui_display.h"

#include <QVBoxLayout>
#include <qcustomplot.h> // Make sure you have qcustomplot.h in your include path

BPMDisplay::BPMDisplay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::display)
    , showCalibrated(true)  // Default to showing calibrated data
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

    // Create and configure the checkbox
    checkBoxShowCalibrated = new QCheckBox("Show Calibrated Data", this);
    checkBoxShowCalibrated->setChecked(true);
    connect(checkBoxShowCalibrated, &QCheckBox::stateChanged,
            this, &BPMDisplay::onDataToggleChanged);

    // Add widgets to the layout
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
    // Re-plot existing data if checkbox toggles
    plot(rawBuffer, calBuffer);
}

void BPMDisplay::plot(const QVector<unsigned short> &raw_data,
                      const QVector<signed short>   &cal_data)
{
    // Store them so we can re-plot if the user toggles the checkbox
    rawBuffer = raw_data;
    calBuffer = cal_data;

    // Prepare data arrays for QCustomPlot
    dataX.resize(raw_data.size());
    dataY.resize(raw_data.size());

    for (int i = 0; i < raw_data.size(); ++i)
    {
        dataX[i] = i;  // x-axis is just the sample index
        dataY[i] = showCalibrated
                       ? static_cast<double>(cal_data[i])  // signed short -> double
                       : static_cast<double>(raw_data[i]); // unsigned short -> double
    }

    // Clear existing graphs, add a new one, and set data
    ui->plotWidget->clearGraphs();
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(0)->setData(dataX, dataY);

    // Configure axes
    ui->plotWidget->xAxis->setLabel("Sample Number");
    ui->plotWidget->yAxis->setLabel(showCalibrated ? "Calibrated Data" : "Raw Data");

    // Rescale axes to fit the new data, then redraw
    ui->plotWidget->rescaleAxes();
    ui->plotWidget->replot();
}

void BPMDisplay::showEvent(QShowEvent *event)
{
    // When the dialog is shown for the first time,
    // plot any data we already have in the buffers
    if (!event->spontaneous()) {
        plot(rawBuffer, calBuffer);
    }
    QDialog::showEvent(event);
}
