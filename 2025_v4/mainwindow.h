#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "hw.h"
#include "display.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void onConnectClicked();
    void onStartStopClicked();
    void onSaveDataClicked();
    void updateDisplay();
    void handleConnectionStatus(bool connected);
    void logMessage(const QString &message);

private:
    Ui::MainWindow *ui;
    HW *hw;
    Display *displayWidget;
    QTimer *updateTimer;
    bool running;
    bool connected;
};

#endif
