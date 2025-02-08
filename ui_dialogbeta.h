/********************************************************************************
** Form generated from reading UI file 'dialogbeta.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGBETA_H
#define UI_DIALOGBETA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_DialogBeta
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGridLayout *gridLayout_2;
    QPushButton *pushLeft;
    QPushButton *pushRight;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineStepperPosition;
    QPushButton *pushResetCtr;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_3;
    QGridLayout *gridLayout;
    QLabel *label_11;
    QLabel *label_10;
    QSpinBox *spinScanSpeed;
    QSpinBox *spinStartPos;
    QLabel *label_4;
    QSpinBox *spinEndPos;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushRun;
    QCheckBox *checkSaveRawData;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineRunsDone;
    QPushButton *pushClear;
    QPushButton *pushSave;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_12;
    QCustomPlot *plotResultsMean;
    QLabel *label_13;
    QCustomPlot *plotResultsStd;

    void setupUi(QDialog *DialogBeta)
    {
        if (DialogBeta->objectName().isEmpty())
            DialogBeta->setObjectName("DialogBeta");
        DialogBeta->resize(844, 632);
        buttonBox = new QDialogButtonBox(DialogBeta);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(490, 590, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        horizontalLayoutWidget = new QWidget(DialogBeta);
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

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pushLeft = new QPushButton(horizontalLayoutWidget);
        pushLeft->setObjectName("pushLeft");

        gridLayout_2->addWidget(pushLeft, 0, 0, 1, 1);

        pushRight = new QPushButton(horizontalLayoutWidget);
        pushRight->setObjectName("pushRight");

        gridLayout_2->addWidget(pushRight, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        lineStepperPosition = new QLineEdit(horizontalLayoutWidget);
        lineStepperPosition->setObjectName("lineStepperPosition");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineStepperPosition->sizePolicy().hasHeightForWidth());
        lineStepperPosition->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(lineStepperPosition);

        pushResetCtr = new QPushButton(horizontalLayoutWidget);
        pushResetCtr->setObjectName("pushResetCtr");
        sizePolicy1.setHeightForWidth(pushResetCtr->sizePolicy().hasHeightForWidth());
        pushResetCtr->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(pushResetCtr);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_11 = new QLabel(horizontalLayoutWidget);
        label_11->setObjectName("label_11");

        gridLayout->addWidget(label_11, 1, 0, 1, 1);

        label_10 = new QLabel(horizontalLayoutWidget);
        label_10->setObjectName("label_10");

        gridLayout->addWidget(label_10, 0, 0, 1, 1);

        spinScanSpeed = new QSpinBox(horizontalLayoutWidget);
        spinScanSpeed->setObjectName("spinScanSpeed");
        spinScanSpeed->setMinimum(1);
        spinScanSpeed->setMaximum(2048);
        spinScanSpeed->setSingleStep(100);
        spinScanSpeed->setValue(1000);

        gridLayout->addWidget(spinScanSpeed, 0, 1, 1, 1);

        spinStartPos = new QSpinBox(horizontalLayoutWidget);
        spinStartPos->setObjectName("spinStartPos");
        spinStartPos->setMinimum(0);
        spinStartPos->setMaximum(1800000);
        spinStartPos->setSingleStep(10000);
        spinStartPos->setValue(0);

        gridLayout->addWidget(spinStartPos, 1, 1, 1, 1);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        spinEndPos = new QSpinBox(horizontalLayoutWidget);
        spinEndPos->setObjectName("spinEndPos");
        spinEndPos->setMaximum(1800000);
        spinEndPos->setSingleStep(10000);
        spinEndPos->setValue(1800000);

        gridLayout->addWidget(spinEndPos, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        pushRun = new QPushButton(horizontalLayoutWidget);
        pushRun->setObjectName("pushRun");

        verticalLayout->addWidget(pushRun);

        checkSaveRawData = new QCheckBox(horizontalLayoutWidget);
        checkSaveRawData->setObjectName("checkSaveRawData");

        verticalLayout->addWidget(checkSaveRawData);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineRunsDone = new QLineEdit(horizontalLayoutWidget);
        lineRunsDone->setObjectName("lineRunsDone");
        sizePolicy.setHeightForWidth(lineRunsDone->sizePolicy().hasHeightForWidth());
        lineRunsDone->setSizePolicy(sizePolicy);
        lineRunsDone->setAutoFillBackground(false);
        lineRunsDone->setReadOnly(true);

        horizontalLayout_2->addWidget(lineRunsDone);


        verticalLayout->addLayout(horizontalLayout_2);

        pushClear = new QPushButton(horizontalLayoutWidget);
        pushClear->setObjectName("pushClear");

        verticalLayout->addWidget(pushClear);

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
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy2);
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_12);

        plotResultsMean = new QCustomPlot(horizontalLayoutWidget);
        plotResultsMean->setObjectName("plotResultsMean");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(plotResultsMean->sizePolicy().hasHeightForWidth());
        plotResultsMean->setSizePolicy(sizePolicy3);

        verticalLayout_3->addWidget(plotResultsMean);

        label_13 = new QLabel(horizontalLayoutWidget);
        label_13->setObjectName("label_13");
        sizePolicy2.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy2);
        label_13->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_13);

        plotResultsStd = new QCustomPlot(horizontalLayoutWidget);
        plotResultsStd->setObjectName("plotResultsStd");

        verticalLayout_3->addWidget(plotResultsStd);


        horizontalLayout->addLayout(verticalLayout_3);

        buttonBox->raise();
        horizontalLayoutWidget->raise();

        retranslateUi(DialogBeta);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, DialogBeta, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, DialogBeta, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DialogBeta);
    } // setupUi

    void retranslateUi(QDialog *DialogBeta)
    {
        DialogBeta->setWindowTitle(QCoreApplication::translate("DialogBeta", "Beta Scanner", nullptr));
        label->setText(QCoreApplication::translate("DialogBeta", "Motor control", nullptr));
        pushLeft->setText(QCoreApplication::translate("DialogBeta", "Left!", nullptr));
        pushRight->setText(QCoreApplication::translate("DialogBeta", "Right!", nullptr));
        pushResetCtr->setText(QCoreApplication::translate("DialogBeta", "Reset", nullptr));
        label_3->setText(QCoreApplication::translate("DialogBeta", "Scan settings", nullptr));
        label_11->setText(QCoreApplication::translate("DialogBeta", "Start pos:", nullptr));
        label_10->setText(QCoreApplication::translate("DialogBeta", "Scanning speed", nullptr));
        label_4->setText(QCoreApplication::translate("DialogBeta", "End pos:", nullptr));
        pushRun->setText(QCoreApplication::translate("DialogBeta", "Run!", nullptr));
        checkSaveRawData->setText(QCoreApplication::translate("DialogBeta", "Save raw data", nullptr));
        label_2->setText(QCoreApplication::translate("DialogBeta", "Runs:", nullptr));
        pushClear->setText(QCoreApplication::translate("DialogBeta", "Clear", nullptr));
        pushSave->setText(QCoreApplication::translate("DialogBeta", "Save results...", nullptr));
        label_12->setText(QCoreApplication::translate("DialogBeta", "Signal mean", nullptr));
        label_13->setText(QCoreApplication::translate("DialogBeta", "Signal standard deviation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogBeta: public Ui_DialogBeta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGBETA_H
