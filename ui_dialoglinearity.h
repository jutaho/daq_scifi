/********************************************************************************
** Form generated from reading UI file 'dialoglinearity.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLINEARITY_H
#define UI_DIALOGLINEARITY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
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

class Ui_DialogLinearity
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_5;
    QLabel *label_8;
    QSpinBox *spinDelay;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_10;
    QSpinBox *spinAcquisitions;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinVend;
    QDoubleSpinBox *doubleSpinVstart;
    QLabel *label_2;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinVinc;
    QLabel *label_11;
    QSpinBox *spinPLotDecimation;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushRun;
    QPushButton *pushSave;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_12;
    QCustomPlot *plotResultsMean;
    QLabel *label_13;
    QCustomPlot *plotResultsStd;

    void setupUi(QDialog *DialogLinearity)
    {
        if (DialogLinearity->objectName().isEmpty())
            DialogLinearity->setObjectName("DialogLinearity");
        DialogLinearity->resize(844, 632);
        buttonBox = new QDialogButtonBox(DialogLinearity);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(490, 590, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        horizontalLayoutWidget = new QWidget(DialogLinearity);
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
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        label_8 = new QLabel(horizontalLayoutWidget);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 4, 0, 1, 1);

        spinDelay = new QSpinBox(horizontalLayoutWidget);
        spinDelay->setObjectName("spinDelay");
        spinDelay->setMinimum(100);
        spinDelay->setMaximum(10000);
        spinDelay->setSingleStep(100);
        spinDelay->setValue(1500);

        gridLayout->addWidget(spinDelay, 4, 1, 1, 1);

        label_9 = new QLabel(horizontalLayoutWidget);
        label_9->setObjectName("label_9");

        gridLayout->addWidget(label_9, 4, 2, 1, 1);

        label_7 = new QLabel(horizontalLayoutWidget);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 2, 2, 1, 1);

        label_6 = new QLabel(horizontalLayoutWidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 1, 2, 1, 1);

        label_10 = new QLabel(horizontalLayoutWidget);
        label_10->setObjectName("label_10");

        gridLayout->addWidget(label_10, 5, 0, 1, 1);

        spinAcquisitions = new QSpinBox(horizontalLayoutWidget);
        spinAcquisitions->setObjectName("spinAcquisitions");
        spinAcquisitions->setMinimum(1);
        spinAcquisitions->setMaximum(1000000);
        spinAcquisitions->setSingleStep(1000);
        spinAcquisitions->setValue(10000);

        gridLayout->addWidget(spinAcquisitions, 5, 1, 1, 1);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        doubleSpinVend = new QDoubleSpinBox(horizontalLayoutWidget);
        doubleSpinVend->setObjectName("doubleSpinVend");
        doubleSpinVend->setMaximum(10.000000000000000);
        doubleSpinVend->setSingleStep(0.100000000000000);
        doubleSpinVend->setValue(6.000000000000000);

        gridLayout->addWidget(doubleSpinVend, 1, 1, 1, 1);

        doubleSpinVstart = new QDoubleSpinBox(horizontalLayoutWidget);
        doubleSpinVstart->setObjectName("doubleSpinVstart");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(doubleSpinVstart->sizePolicy().hasHeightForWidth());
        doubleSpinVstart->setSizePolicy(sizePolicy1);
        doubleSpinVstart->setMaximum(10.000000000000000);
        doubleSpinVstart->setSingleStep(0.100000000000000);
        doubleSpinVstart->setValue(2.000000000000000);

        gridLayout->addWidget(doubleSpinVstart, 0, 1, 1, 1);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        doubleSpinVinc = new QDoubleSpinBox(horizontalLayoutWidget);
        doubleSpinVinc->setObjectName("doubleSpinVinc");
        doubleSpinVinc->setMaximum(10.000000000000000);
        doubleSpinVinc->setSingleStep(0.010000000000000);
        doubleSpinVinc->setValue(0.100000000000000);

        gridLayout->addWidget(doubleSpinVinc, 2, 1, 1, 1);

        label_11 = new QLabel(horizontalLayoutWidget);
        label_11->setObjectName("label_11");

        gridLayout->addWidget(label_11, 6, 0, 1, 1);

        spinPLotDecimation = new QSpinBox(horizontalLayoutWidget);
        spinPLotDecimation->setObjectName("spinPLotDecimation");
        spinPLotDecimation->setMinimum(1);
        spinPLotDecimation->setMaximum(128);
        spinPLotDecimation->setValue(16);

        gridLayout->addWidget(spinPLotDecimation, 6, 1, 1, 1);


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

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_12 = new QLabel(horizontalLayoutWidget);
        label_12->setObjectName("label_12");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy3);
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_12);

        plotResultsMean = new QCustomPlot(horizontalLayoutWidget);
        plotResultsMean->setObjectName("plotResultsMean");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(plotResultsMean->sizePolicy().hasHeightForWidth());
        plotResultsMean->setSizePolicy(sizePolicy4);

        verticalLayout_3->addWidget(plotResultsMean);

        label_13 = new QLabel(horizontalLayoutWidget);
        label_13->setObjectName("label_13");
        sizePolicy3.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy3);
        label_13->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_13);

        plotResultsStd = new QCustomPlot(horizontalLayoutWidget);
        plotResultsStd->setObjectName("plotResultsStd");

        verticalLayout_3->addWidget(plotResultsStd);


        horizontalLayout->addLayout(verticalLayout_3);


        retranslateUi(DialogLinearity);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, DialogLinearity, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, DialogLinearity, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DialogLinearity);
    } // setupUi

    void retranslateUi(QDialog *DialogLinearity)
    {
        DialogLinearity->setWindowTitle(QCoreApplication::translate("DialogLinearity", "Linearity Test", nullptr));
        label->setText(QCoreApplication::translate("DialogLinearity", "Scan settings", nullptr));
        label_5->setText(QCoreApplication::translate("DialogLinearity", "V", nullptr));
        label_8->setText(QCoreApplication::translate("DialogLinearity", "Measurement delay:", nullptr));
        label_9->setText(QCoreApplication::translate("DialogLinearity", "ms", nullptr));
        label_7->setText(QCoreApplication::translate("DialogLinearity", "V", nullptr));
        label_6->setText(QCoreApplication::translate("DialogLinearity", "V", nullptr));
        label_10->setText(QCoreApplication::translate("DialogLinearity", "Acqs/point:", nullptr));
        label_3->setText(QCoreApplication::translate("DialogLinearity", "End LED voltage:", nullptr));
        label_2->setText(QCoreApplication::translate("DialogLinearity", "Start LED voltage:", nullptr));
        label_4->setText(QCoreApplication::translate("DialogLinearity", "Voltage increment:", nullptr));
        label_11->setText(QCoreApplication::translate("DialogLinearity", "Plot decimation:", nullptr));
        pushRun->setText(QCoreApplication::translate("DialogLinearity", "Run!", nullptr));
        pushSave->setText(QCoreApplication::translate("DialogLinearity", "Save results...", nullptr));
        label_12->setText(QCoreApplication::translate("DialogLinearity", "Signal mean", nullptr));
        label_13->setText(QCoreApplication::translate("DialogLinearity", "Signal standard deviation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogLinearity: public Ui_DialogLinearity {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLINEARITY_H
