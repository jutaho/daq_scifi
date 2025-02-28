/********************************************************************************
** Form generated from reading UI file 'dialogtriggersettings.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGTRIGGERSETTINGS_H
#define UI_DIALOGTRIGGERSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogTriggerSettings
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_9;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QSpinBox *spinTintTicks;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioLow;
    QRadioButton *radioHigh;
    QLabel *label_3;
    QLineEdit *linePeriodUs;
    QLineEdit *lineFreqKhz;
    QLabel *label_4;
    QLineEdit *linePeriodOK;
    QSpinBox *spinPeriodTicks;
    QLineEdit *lineTintOK;
    QLabel *label_7;
    QLineEdit *lineTintUs;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_10;
    QGridLayout *gridLayout_3;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *lineTintOK_v2;
    QLineEdit *linePeriodOK_v2;
    QLineEdit *lineFreqKhz_v2;
    QLabel *label_14;
    QLineEdit *linePeriodUs_v2;
    QLineEdit *lineTintUs_v2;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QSpinBox *spinPeriodTicks_v2;
    QLabel *label_19;
    QSpinBox *spinTintTicks_v2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioLow_v2;
    QRadioButton *radioHigh_v2;
    QLabel *label_15;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *DialogTriggerSettings)
    {
        if (DialogTriggerSettings->objectName().isEmpty())
            DialogTriggerSettings->setObjectName("DialogTriggerSettings");
        DialogTriggerSettings->resize(517, 281);
        buttonBox = new QDialogButtonBox(DialogTriggerSettings);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(90, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        verticalLayoutWidget = new QWidget(DialogTriggerSettings);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 501, 228));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(verticalLayoutWidget);
        label_9->setObjectName("label_9");
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_9);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 1, 2, 1, 1);

        spinTintTicks = new QSpinBox(verticalLayoutWidget);
        spinTintTicks->setObjectName("spinTintTicks");
        spinTintTicks->setMinimum(10);
        spinTintTicks->setMaximum(65535);

        gridLayout->addWidget(spinTintTicks, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        radioLow = new QRadioButton(verticalLayoutWidget);
        buttonGroup_2 = new QButtonGroup(DialogTriggerSettings);
        buttonGroup_2->setObjectName("buttonGroup_2");
        buttonGroup_2->addButton(radioLow);
        radioLow->setObjectName("radioLow");

        horizontalLayout->addWidget(radioLow);

        radioHigh = new QRadioButton(verticalLayoutWidget);
        buttonGroup_2->addButton(radioHigh);
        radioHigh->setObjectName("radioHigh");

        horizontalLayout->addWidget(radioHigh);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 4, 1, 1);

        linePeriodUs = new QLineEdit(verticalLayoutWidget);
        linePeriodUs->setObjectName("linePeriodUs");
        linePeriodUs->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        linePeriodUs->setReadOnly(true);

        gridLayout->addWidget(linePeriodUs, 0, 3, 1, 1);

        lineFreqKhz = new QLineEdit(verticalLayoutWidget);
        lineFreqKhz->setObjectName("lineFreqKhz");
        lineFreqKhz->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lineFreqKhz->setReadOnly(true);

        gridLayout->addWidget(lineFreqKhz, 0, 5, 1, 1);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 0, 6, 1, 1);

        linePeriodOK = new QLineEdit(verticalLayoutWidget);
        linePeriodOK->setObjectName("linePeriodOK");
        linePeriodOK->setAlignment(Qt::AlignmentFlag::AlignCenter);
        linePeriodOK->setReadOnly(true);

        gridLayout->addWidget(linePeriodOK, 0, 7, 1, 1);

        spinPeriodTicks = new QSpinBox(verticalLayoutWidget);
        spinPeriodTicks->setObjectName("spinPeriodTicks");
        spinPeriodTicks->setMinimum(8000);
        spinPeriodTicks->setMaximum(65535);

        gridLayout->addWidget(spinPeriodTicks, 0, 1, 1, 1);

        lineTintOK = new QLineEdit(verticalLayoutWidget);
        lineTintOK->setObjectName("lineTintOK");
        lineTintOK->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineTintOK->setReadOnly(true);

        gridLayout->addWidget(lineTintOK, 1, 7, 1, 1);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 1, 4, 1, 1);

        lineTintUs = new QLineEdit(verticalLayoutWidget);
        lineTintUs->setObjectName("lineTintUs");
        lineTintUs->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lineTintUs->setReadOnly(true);

        gridLayout->addWidget(lineTintUs, 1, 3, 1, 1);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        label_10 = new QLabel(verticalLayoutWidget);
        label_10->setObjectName("label_10");
        label_10->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_10);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        label_12 = new QLabel(verticalLayoutWidget);
        label_12->setObjectName("label_12");

        gridLayout_3->addWidget(label_12, 1, 2, 1, 1);

        label_13 = new QLabel(verticalLayoutWidget);
        label_13->setObjectName("label_13");

        gridLayout_3->addWidget(label_13, 0, 0, 1, 1);

        lineTintOK_v2 = new QLineEdit(verticalLayoutWidget);
        lineTintOK_v2->setObjectName("lineTintOK_v2");
        lineTintOK_v2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineTintOK_v2->setReadOnly(true);

        gridLayout_3->addWidget(lineTintOK_v2, 1, 7, 1, 1);

        linePeriodOK_v2 = new QLineEdit(verticalLayoutWidget);
        linePeriodOK_v2->setObjectName("linePeriodOK_v2");
        linePeriodOK_v2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        linePeriodOK_v2->setReadOnly(true);

        gridLayout_3->addWidget(linePeriodOK_v2, 0, 7, 1, 1);

        lineFreqKhz_v2 = new QLineEdit(verticalLayoutWidget);
        lineFreqKhz_v2->setObjectName("lineFreqKhz_v2");
        lineFreqKhz_v2->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lineFreqKhz_v2->setReadOnly(true);

        gridLayout_3->addWidget(lineFreqKhz_v2, 0, 5, 1, 1);

        label_14 = new QLabel(verticalLayoutWidget);
        label_14->setObjectName("label_14");

        gridLayout_3->addWidget(label_14, 0, 6, 1, 1);

        linePeriodUs_v2 = new QLineEdit(verticalLayoutWidget);
        linePeriodUs_v2->setObjectName("linePeriodUs_v2");
        linePeriodUs_v2->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        linePeriodUs_v2->setReadOnly(true);

        gridLayout_3->addWidget(linePeriodUs_v2, 0, 3, 1, 1);

        lineTintUs_v2 = new QLineEdit(verticalLayoutWidget);
        lineTintUs_v2->setObjectName("lineTintUs_v2");
        lineTintUs_v2->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lineTintUs_v2->setReadOnly(true);

        gridLayout_3->addWidget(lineTintUs_v2, 1, 3, 1, 1);

        label_16 = new QLabel(verticalLayoutWidget);
        label_16->setObjectName("label_16");

        gridLayout_3->addWidget(label_16, 1, 4, 1, 1);

        label_17 = new QLabel(verticalLayoutWidget);
        label_17->setObjectName("label_17");

        gridLayout_3->addWidget(label_17, 0, 4, 1, 1);

        label_18 = new QLabel(verticalLayoutWidget);
        label_18->setObjectName("label_18");

        gridLayout_3->addWidget(label_18, 0, 2, 1, 1);

        spinPeriodTicks_v2 = new QSpinBox(verticalLayoutWidget);
        spinPeriodTicks_v2->setObjectName("spinPeriodTicks_v2");
        spinPeriodTicks_v2->setMinimum(2000);
        spinPeriodTicks_v2->setMaximum(999999999);
        spinPeriodTicks_v2->setValue(24999);

        gridLayout_3->addWidget(spinPeriodTicks_v2, 0, 1, 1, 1);

        label_19 = new QLabel(verticalLayoutWidget);
        label_19->setObjectName("label_19");

        gridLayout_3->addWidget(label_19, 2, 0, 1, 1);

        spinTintTicks_v2 = new QSpinBox(verticalLayoutWidget);
        spinTintTicks_v2->setObjectName("spinTintTicks_v2");
        spinTintTicks_v2->setMinimum(10);
        spinTintTicks_v2->setMaximum(9999999);

        gridLayout_3->addWidget(spinTintTicks_v2, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        radioLow_v2 = new QRadioButton(verticalLayoutWidget);
        buttonGroup = new QButtonGroup(DialogTriggerSettings);
        buttonGroup->setObjectName("buttonGroup");
        buttonGroup->addButton(radioLow_v2);
        radioLow_v2->setObjectName("radioLow_v2");

        horizontalLayout_2->addWidget(radioLow_v2);

        radioHigh_v2 = new QRadioButton(verticalLayoutWidget);
        buttonGroup->addButton(radioHigh_v2);
        radioHigh_v2->setObjectName("radioHigh_v2");

        horizontalLayout_2->addWidget(radioHigh_v2);


        gridLayout_3->addLayout(horizontalLayout_2, 2, 1, 1, 1);

        label_15 = new QLabel(verticalLayoutWidget);
        label_15->setObjectName("label_15");

        gridLayout_3->addWidget(label_15, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_3);


        retranslateUi(DialogTriggerSettings);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, DialogTriggerSettings, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, DialogTriggerSettings, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DialogTriggerSettings);
    } // setupUi

    void retranslateUi(QDialog *DialogTriggerSettings)
    {
        DialogTriggerSettings->setWindowTitle(QCoreApplication::translate("DialogTriggerSettings", "Trigger configuration", nullptr));
        label_9->setText(QCoreApplication::translate("DialogTriggerSettings", "Hardware v.1", nullptr));
        label_6->setText(QCoreApplication::translate("DialogTriggerSettings", "=", nullptr));
        radioLow->setText(QCoreApplication::translate("DialogTriggerSettings", "Lo", nullptr));
        radioHigh->setText(QCoreApplication::translate("DialogTriggerSettings", "Hi", nullptr));
        label_3->setText(QCoreApplication::translate("DialogTriggerSettings", "us  =>", nullptr));
        label_4->setText(QCoreApplication::translate("DialogTriggerSettings", "kHz", nullptr));
        label_7->setText(QCoreApplication::translate("DialogTriggerSettings", "us", nullptr));
        label_5->setText(QCoreApplication::translate("DialogTriggerSettings", "=", nullptr));
        label_8->setText(QCoreApplication::translate("DialogTriggerSettings", "Gain:", nullptr));
        label_2->setText(QCoreApplication::translate("DialogTriggerSettings", "Tint:", nullptr));
        label->setText(QCoreApplication::translate("DialogTriggerSettings", "Period:", nullptr));
        label_10->setText(QCoreApplication::translate("DialogTriggerSettings", "Harware v.2", nullptr));
        label_12->setText(QCoreApplication::translate("DialogTriggerSettings", "=", nullptr));
        label_13->setText(QCoreApplication::translate("DialogTriggerSettings", "Period:", nullptr));
        label_14->setText(QCoreApplication::translate("DialogTriggerSettings", "kHz", nullptr));
        label_16->setText(QCoreApplication::translate("DialogTriggerSettings", "us", nullptr));
        label_17->setText(QCoreApplication::translate("DialogTriggerSettings", "us  =>", nullptr));
        label_18->setText(QCoreApplication::translate("DialogTriggerSettings", "=", nullptr));
        label_19->setText(QCoreApplication::translate("DialogTriggerSettings", "Gain:", nullptr));
        radioLow_v2->setText(QCoreApplication::translate("DialogTriggerSettings", "Lo", nullptr));
        radioHigh_v2->setText(QCoreApplication::translate("DialogTriggerSettings", "Hi", nullptr));
        label_15->setText(QCoreApplication::translate("DialogTriggerSettings", "Tint:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogTriggerSettings: public Ui_DialogTriggerSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGTRIGGERSETTINGS_H
