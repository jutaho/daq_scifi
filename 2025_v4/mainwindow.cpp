#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    hw(new HW()),
    displayWidget(new Display()),
    updateTimer(new QTimer(this)),
    running(false),
    connected(false)
{
    ui->setupUi(this);

    hw->addDevices(1);

    for (Device* dev : hw->getDevices()) {
        connect(dev, &Device::logMessage, this, &MainWindow::logMessage);
    }

    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::onConnectClicked);
    connect(hw, &HW::connectionStatusChanged, this, &MainWindow::handleConnectionStatus);

    updateTimer->start(1000);
}

void MainWindow::onConnectClicked()
{
    logMessage("Trying to connect to the device...");
    hw->connectDevices();
}

void MainWindow::handleConnectionStatus(bool connected)
{
    this->connected = connected;
    if (connected) {
        ui->statusBar->showMessage("Connected to device.");
        logMessage("Successfully connected!");
    } else {
        ui->statusBar->showMessage("Failed to connect.");
        logMessage("Connection failed.");
    }
}

void MainWindow::logMessage(const QString &message)
{
    ui->logWindow->append(message);
}

void MainWindow::onStartStopClicked()
{
    logMessage("Start/Stop clicked.");
}

void MainWindow::onSaveDataClicked()
{
    logMessage("Save Data clicked.");
}

void MainWindow::updateDisplay()
{
    logMessage("Updating display.");
}


MainWindow::~MainWindow()
{
    delete ui;
    delete hw;
    delete displayWidget;
}
