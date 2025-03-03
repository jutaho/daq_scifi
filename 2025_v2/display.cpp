#include "display.h"
#include "ui_display.h"
#include <QVBoxLayout>
#include "qcustomplot.h"

BPMDisplay::BPMDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::display) {

    ui->setupUi(this);
    setupUI();
}

BPMDisplay::~BPMDisplay() {
    delete ui;
}

void BPMDisplay::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    checkBoxShowCalibrated = new QCheckBox("Show Calibrated Data", this);
    checkBoxShowCalibrated->setChecked(true);
    connect(checkBoxShowCalibrated, &QCheckBox::stateChanged, this, &BPMDisplay::onDataToggleChanged);

    mainLayout->addWidget(checkBoxShowCalibrated);
    mainLayout->addWidget(ui->plotWidget);

    setLayout(mainLayout);
}

void BPMDisplay::setTitle(QString title) {
    setWindowTitle(title);
}

void BPMDisplay::onDataToggleChanged(int state) {
    showCalibrated = (state == Qt::Checked);
    plot(rawBuffer, calBuffer);
}

void BPMDisplay::plot(const QVector<signed short> &raw_data, const QVector<unsigned short> &cal_data) {
    rawBuffer = raw_data;
    calBuffer = cal_data;

    dataX.resize(raw_data.size());
    dataY.resize(raw_data.size());

    for (int i = 0; i < raw_data.size(); ++i) {
        dataX[i] = i;
        dataY[i] = showCalibrated ? cal_data[i] : raw_data[i];
    }

    ui->plotWidget->clearGraphs();
    ui->plotWidget->addGraph();

    ui->plotWidget->graph(0)->setData(dataX, dataY);

    ui->plotWidget->xAxis->setLabel("Sample Number");
    ui->plotWidget->yAxis->setLabel(showCalibrated ? "Calibrated Data" : "Raw Data");

    ui->plotWidget->rescaleAxes();
    ui->plotWidget->replot();
}

void BPMDisplay::showEvent(QShowEvent *event) {
    if (!event->spontaneous()) {
        plot(rawBuffer, calBuffer);
    }
    QDialog::showEvent(event);
}
