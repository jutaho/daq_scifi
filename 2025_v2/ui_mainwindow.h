/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionHost_IP;
    QAction *actionDevices;
    QAction *actionTrigger_config;
    QAction *actionRun;
    QAction *actionConnect_Keithley;
    QAction *actionDisconnect_Keithley;
    QAction *actionLinearity_test;
    QAction *actionIntegration_time_scan;
    QAction *actionProfile_viewer;
    QAction *actionConnect_Stepper;
    QAction *actionDisconnect_Stepper;
    QAction *actionBeta_Scanner;
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *logWindow;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushRun;
    QPushButton *pushLogging;
    QPushButton *pushDisplay;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushLogSettings;
    QPushButton *pushButton_exit;
    QPushButton *pushAnalysing;
    QMenuBar *menuBar;
    QMenu *menuDevice;
    QMenu *menuSettings;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(853, 601);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName("actionConnect");
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName("actionDisconnect");
        actionHost_IP = new QAction(MainWindow);
        actionHost_IP->setObjectName("actionHost_IP");
        actionDevices = new QAction(MainWindow);
        actionDevices->setObjectName("actionDevices");
        actionTrigger_config = new QAction(MainWindow);
        actionTrigger_config->setObjectName("actionTrigger_config");
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName("actionRun");
        actionConnect_Keithley = new QAction(MainWindow);
        actionConnect_Keithley->setObjectName("actionConnect_Keithley");
        actionDisconnect_Keithley = new QAction(MainWindow);
        actionDisconnect_Keithley->setObjectName("actionDisconnect_Keithley");
        actionLinearity_test = new QAction(MainWindow);
        actionLinearity_test->setObjectName("actionLinearity_test");
        actionIntegration_time_scan = new QAction(MainWindow);
        actionIntegration_time_scan->setObjectName("actionIntegration_time_scan");
        actionProfile_viewer = new QAction(MainWindow);
        actionProfile_viewer->setObjectName("actionProfile_viewer");
        actionConnect_Stepper = new QAction(MainWindow);
        actionConnect_Stepper->setObjectName("actionConnect_Stepper");
        actionDisconnect_Stepper = new QAction(MainWindow);
        actionDisconnect_Stepper->setObjectName("actionDisconnect_Stepper");
        actionBeta_Scanner = new QAction(MainWindow);
        actionBeta_Scanner->setObjectName("actionBeta_Scanner");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 831, 421));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        logWindow = new QTextBrowser(verticalLayoutWidget);
        logWindow->setObjectName("logWindow");

        verticalLayout->addWidget(logWindow);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        pushRun = new QPushButton(verticalLayoutWidget);
        pushRun->setObjectName("pushRun");
        pushRun->setEnabled(false);

        horizontalLayout->addWidget(pushRun);

        pushLogging = new QPushButton(verticalLayoutWidget);
        pushLogging->setObjectName("pushLogging");
        pushLogging->setEnabled(true);

        horizontalLayout->addWidget(pushLogging);

        pushDisplay = new QPushButton(verticalLayoutWidget);
        pushDisplay->setObjectName("pushDisplay");

        horizontalLayout->addWidget(pushDisplay);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushLogSettings = new QPushButton(verticalLayoutWidget);
        pushLogSettings->setObjectName("pushLogSettings");

        horizontalLayout->addWidget(pushLogSettings);


        verticalLayout->addLayout(horizontalLayout);

        pushButton_exit = new QPushButton(centralWidget);
        pushButton_exit->setObjectName("pushButton_exit");
        pushButton_exit->setGeometry(QRect(760, 510, 80, 24));
        pushAnalysing = new QPushButton(centralWidget);
        pushAnalysing->setObjectName("pushAnalysing");
        pushAnalysing->setEnabled(true);
        pushAnalysing->setGeometry(QRect(90, 440, 161, 24));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 853, 22));
        menuDevice = new QMenu(menuBar);
        menuDevice->setObjectName("menuDevice");
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName("menuSettings");
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDevice->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuDevice->addAction(actionConnect);
        menuDevice->addAction(actionDisconnect);
        menuDevice->addSeparator();
        menuDevice->addSeparator();
        menuSettings->addAction(actionHost_IP);
        menuSettings->addAction(actionDevices);
        menuSettings->addAction(actionTrigger_config);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "HIT DAQ", nullptr));
        actionConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        actionDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        actionHost_IP->setText(QCoreApplication::translate("MainWindow", "Host IP...", nullptr));
        actionDevices->setText(QCoreApplication::translate("MainWindow", "Devices...", nullptr));
        actionTrigger_config->setText(QCoreApplication::translate("MainWindow", "Trigger config...", nullptr));
        actionRun->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        actionConnect_Keithley->setText(QCoreApplication::translate("MainWindow", "Connect Keithley", nullptr));
        actionDisconnect_Keithley->setText(QCoreApplication::translate("MainWindow", "Disconnect Keithley", nullptr));
        actionLinearity_test->setText(QCoreApplication::translate("MainWindow", "Linearity test", nullptr));
        actionIntegration_time_scan->setText(QCoreApplication::translate("MainWindow", "Integration time scan", nullptr));
        actionProfile_viewer->setText(QCoreApplication::translate("MainWindow", "Profile viewer", nullptr));
        actionConnect_Stepper->setText(QCoreApplication::translate("MainWindow", "Connect Stepper", nullptr));
        actionDisconnect_Stepper->setText(QCoreApplication::translate("MainWindow", "Disconnect Stepper", nullptr));
        actionBeta_Scanner->setText(QCoreApplication::translate("MainWindow", "Beta Scanner", nullptr));
        pushRun->setText(QCoreApplication::translate("MainWindow", "Run!", nullptr));
        pushLogging->setText(QCoreApplication::translate("MainWindow", "Start logging!", nullptr));
        pushDisplay->setText(QCoreApplication::translate("MainWindow", "Show display!", nullptr));
        pushLogSettings->setText(QCoreApplication::translate("MainWindow", "Log settings...", nullptr));
        pushButton_exit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        pushAnalysing->setText(QCoreApplication::translate("MainWindow", "Start Analysing!", nullptr));
        menuDevice->setTitle(QCoreApplication::translate("MainWindow", "Device", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
