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
    void onStartStopClicked();
    void onSaveDataClicked();
    void updateDisplay();

private:
    Ui::MainWindow *ui;
    HW *hw;                   // Hardware manager (manages devices)
    Display *displayWidget;   // Widget for online visualization of raw data
    QTimer *updateTimer;      // Timer to refresh display periodically
    bool running;
};

#endif // MAINWINDOW_H
