/********************************************************************************
** Form generated from reading UI file 'dialogtiscan.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGTISCAN_H
#define UI_DIALOGTISCAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_DialogTiScan
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_11;
    QSpinBox *spinPLotDecimation;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QLabel *label_6;
    QSpinBox *spinAcquisitions;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinLEDV;
    QLabel *label_13;
    QLabel *label_12;
    QSpinBox *spinTEnd;
    QSpinBox *spinTIncrement;
    QSpacerItem *verticalSpacer_4;
    QCheckBox *checkUseLED;
    QSpinBox *spintStart;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushRun;
    QPushButton *pushSave;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QCustomPlot *plotResultsMean;
    QLabel *label_7;
    QCustomPlot *plotResultsStd;

    void setupUi(QDialog *DialogTiScan)
    {
        if (DialogTiScan->objectName().isEmpty())
            DialogTiScan->setObjectName("DialogTiScan");
        DialogTiScan->resize(844, 632);
        buttonBox = new QDialogButtonBox(DialogTiScan);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(490, 590, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        horizontalLayoutWidget = new QWidget(DialogTiScan);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 821, 571));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_11 = new QLabel(horizontalLayoutWidget);
        label_11->setObjectName("label_11");

        gridLayout->addWidget(label_11, 8, 0, 1, 1);

        spinPLotDecimation = new QSpinBox(horizontalLayoutWidget);
        spinPLotDecimation->setObjectName("spinPLotDecimation");
        spinPLotDecimation->setMinimum(1);
        spinPLotDecimation->setMaximum(128);
        spinPLotDecimation->setValue(16);

        gridLayout->addWidget(spinPLotDecimation, 8, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 6, 0, 1, 1);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_6 = new QLabel(horizontalLayoutWidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 1, 2, 1, 1);

        spinAcquisitions = new QSpinBox(horizontalLayoutWidget);
        spinAcquisitions->setObjectName("spinAcquisitions");
        spinAcquisitions->setMinimum(1);
        spinAcquisitions->setMaximum(1000000);
        spinAcquisitions->setSingleStep(1000);
        spinAcquisitions->setValue(10000);

        gridLayout->addWidget(spinAcquisitions, 7, 1, 1, 1);

        label_10 = new QLabel(horizontalLayoutWidget);
        label_10->setObjectName("label_10");

        gridLayout->addWidget(label_10, 7, 0, 1, 1);

        doubleSpinLEDV = new QDoubleSpinBox(horizontalLayoutWidget);
        doubleSpinLEDV->setObjectName("doubleSpinLEDV");
        doubleSpinLEDV->setMaximum(10.000000000000000);
        doubleSpinLEDV->setSingleStep(0.100000000000000);
        doubleSpinLEDV->setValue(6.000000000000000);

        gridLayout->addWidget(doubleSpinLEDV, 1, 1, 1, 1);

        label_13 = new QLabel(horizontalLayoutWidget);
        label_13->setObjectName("label_13");

        gridLayout->addWidget(label_13, 3, 0, 1, 1);

        label_12 = new QLabel(horizontalLayoutWidget);
        label_12->setObjectName("label_12");

        gridLayout->addWidget(label_12, 4, 0, 1, 1);

        spinTEnd = new QSpinBox(horizontalLayoutWidget);
        spinTEnd->setObjectName("spinTEnd");
        spinTEnd->setMinimum(10);
        spinTEnd->setMaximum(100000);
        spinTEnd->setValue(8549);

        gridLayout->addWidget(spinTEnd, 4, 1, 1, 1);

        spinTIncrement = new QSpinBox(horizontalLayoutWidget);
        spinTIncrement->setObjectName("spinTIncrement");
        spinTIncrement->setMinimum(1);
        spinTIncrement->setMaximum(100000);
        spinTIncrement->setValue(100);

        gridLayout->addWidget(spinTIncrement, 5, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 2, 0, 1, 1);

        checkUseLED = new QCheckBox(horizontalLayoutWidget);
        checkUseLED->setObjectName("checkUseLED");

        gridLayout->addWidget(checkUseLED, 0, 1, 1, 1);

        spintStart = new QSpinBox(horizontalLayoutWidget);
        spintStart->setObjectName("spintStart");
        spintStart->setMinimum(10);
        spintStart->setMaximum(100000);
        spintStart->setValue(100);

        gridLayout->addWidget(spintStart, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        pushRun = new QPushButton(horizontalLayoutWidget);
        pushRun->setObjectName("pushRun");

        verticalLayout->addWidget(pushRun);

        pushSave = new QPushButton(horizontalLayoutWidget);
        pushSave->setObjectName("pushSave");

        verticalLayout->addWidget(pushSave);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName("label_5");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_5);

        plotResultsMean = new QCustomPlot(horizontalLayoutWidget);
        plotResultsMean->setObjectName("plotResultsMean");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(plotResultsMean->sizePolicy().hasHeightForWidth());
        plotResultsMean->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(plotResultsMean);

        label_7 = new QLabel(horizontalLayoutWidget);
        label_7->setObjectName("label_7");
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_7);

        plotResultsStd = new QCustomPlot(horizontalLayoutWidget);
        plotResultsStd->setObjectName("plotResultsStd");

        verticalLayout_2->addWidget(plotResultsStd);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(DialogTiScan);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, DialogTiScan, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, DialogTiScan, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DialogTiScan);
    } // setupUi

    void retranslateUi(QDialog *DialogTiScan)
    {
        DialogTiScan->setWindowTitle(QCoreApplication::translate("DialogTiScan", "Integration Time Scan", nullptr));
        label->setText(QCoreApplication::translate("DialogTiScan", "Scan settings", nullptr));
        label_4->setText(QCoreApplication::translate("DialogTiScan", "Time increment:", nullptr));
        label_2->setText(QCoreApplication::translate("DialogTiScan", "Use LED:", nullptr));
        label_11->setText(QCoreApplication::translate("DialogTiScan", "Plot decimation:", nullptr));
        label_3->setText(QCoreApplication::translate("DialogTiScan", "LED voltage:", nullptr));
        label_6->setText(QCoreApplication::translate("DialogTiScan", "V", nullptr));
        label_10->setText(QCoreApplication::translate("DialogTiScan", "Acqs/point:", nullptr));
        label_13->setText(QCoreApplication::translate("DialogTiScan", "Start integration time:", nullptr));
        label_12->setText(QCoreApplication::translate("DialogTiScan", "End integration time:", nullptr));
        checkUseLED->setText(QCoreApplication::translate("DialogTiScan", "CheckBox", nullptr));
        pushRun->setText(QCoreApplication::translate("DialogTiScan", "Run!", nullptr));
        pushSave->setText(QCoreApplication::translate("DialogTiScan", "Save results...", nullptr));
        label_5->setText(QCoreApplication::translate("DialogTiScan", "Signal mean", nullptr));
        label_7->setText(QCoreApplication::translate("DialogTiScan", "Signal standard deviation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogTiScan: public Ui_DialogTiScan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGTISCAN_H
