#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    running(false)
{
    ui->setupUi(this);
    // Create our hardware manager and add one (or more) device(s)
    hw = new HW(this);
    hw->addDevices(1); // For example, add one device

    // Create a display widget and set it as the central widget
    displayWidget = new Display(this);
    setCentralWidget(displayWidget);

    // Setup timer to update display
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateDisplay);

    // Connect UI buttons (assume you have two buttons: btnStartStop and btnSave)
    connect(ui->btnStartStop, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    connect(ui->btnSave, &QPushButton::clicked, this, &MainWindow::onSaveDataClicked);
}

MainWindow::~MainWindow()
{
    delete hw;
    delete ui;
}

void MainWindow::onStartStopClicked()
{
    if (!running) {
        hw->connectDevices();
        hw->run();
        updateTimer->start(200);
        ui->btnStartStop->setText("Stop");
        running = true;
    } else {
        hw->stop();
        hw->disconnectDevices();
        updateTimer->stop();
        ui->btnStartStop->setText("Start");
        running = false;
    }
}

void MainWindow::onSaveDataClicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Raw Data", "", "Raw Data Files (*.raw)");
    if (!filename.isEmpty()) {
        QString err = hw->saveRawData(filename);
        if (!err.isEmpty())
            QMessageBox::warning(this, "Save Error", err);
    }
}

void MainWindow::updateDisplay()
{
    // For simplicity, get the latest frame from the first device
    QVector<BufferData> frames = hw->getLatestFrames();
    if (!frames.isEmpty()) {
        // Plot the raw data from the frame (using buffer and its buffer_size)
        displayWidget->plot(frames[0].raw_data, frames[0].buffer_size);
    }
}
