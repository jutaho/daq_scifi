/********************************************************************************
** Form generated from reading UI file 'display.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_display
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineTitle;
    QCustomPlot *plot;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButtonAutoscale;
    QFrame *line;
    QRadioButton *radioButtonMaxScale;
    QFrame *line_2;
    QRadioButton *radioButtonFixedScale;
    QSpinBox *spinBox_fixedmin;
    QSpinBox *spinBox_fixedmax;
    QFrame *line_3;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_expertmode;
    QCheckBox *checkBox_enablecalib;
    QPushButton *pushButton_loadcalib;
    QPushButton *pushButton_savecalib;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_5;
    QFrame *frame;
    QLCDNumber *lcdNumber_mean;
    QLabel *label;
    QFrame *frame_4;
    QLabel *label_4;
    QLCDNumber *lcdNumber_status;
    QFrame *frame_3;
    QLCDNumber *lcdNumber_focus;
    QLabel *label_2;
    QFrame *frame_2;
    QLCDNumber *lcdNumber_max;
    QLabel *label_3;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *display)
    {
        if (display->objectName().isEmpty())
            display->setObjectName("display");
        display->resize(609, 463);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(display->sizePolicy().hasHeightForWidth());
        display->setSizePolicy(sizePolicy);
        verticalLayoutWidget = new QWidget(display);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(9, 10, 581, 341));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineTitle = new QLineEdit(verticalLayoutWidget);
        lineTitle->setObjectName("lineTitle");
        lineTitle->setFrame(false);
        lineTitle->setAlignment(Qt::AlignCenter);
        lineTitle->setReadOnly(true);

        verticalLayout->addWidget(lineTitle);

        plot = new QCustomPlot(verticalLayoutWidget);
        plot->setObjectName("plot");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(plot);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        radioButtonAutoscale = new QRadioButton(verticalLayoutWidget);
        buttonGroup = new QButtonGroup(display);
        buttonGroup->setObjectName("buttonGroup");
        buttonGroup->addButton(radioButtonAutoscale);
        radioButtonAutoscale->setObjectName("radioButtonAutoscale");

        horizontalLayout->addWidget(radioButtonAutoscale);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line);

        radioButtonMaxScale = new QRadioButton(verticalLayoutWidget);
        buttonGroup->addButton(radioButtonMaxScale);
        radioButtonMaxScale->setObjectName("radioButtonMaxScale");

        horizontalLayout->addWidget(radioButtonMaxScale);

        line_2 = new QFrame(verticalLayoutWidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line_2);

        radioButtonFixedScale = new QRadioButton(verticalLayoutWidget);
        buttonGroup->addButton(radioButtonFixedScale);
        radioButtonFixedScale->setObjectName("radioButtonFixedScale");

        horizontalLayout->addWidget(radioButtonFixedScale);

        spinBox_fixedmin = new QSpinBox(verticalLayoutWidget);
        spinBox_fixedmin->setObjectName("spinBox_fixedmin");
        spinBox_fixedmin->setMinimum(-1000);
        spinBox_fixedmin->setMaximum(66000);
        spinBox_fixedmin->setSingleStep(100);
        spinBox_fixedmin->setValue(-1000);
        spinBox_fixedmin->setDisplayIntegerBase(10);

        horizontalLayout->addWidget(spinBox_fixedmin);

        spinBox_fixedmax = new QSpinBox(verticalLayoutWidget);
        spinBox_fixedmax->setObjectName("spinBox_fixedmax");
        spinBox_fixedmax->setMinimum(1000);
        spinBox_fixedmax->setMaximum(65000);
        spinBox_fixedmax->setSingleStep(100);
        spinBox_fixedmax->setValue(65000);

        horizontalLayout->addWidget(spinBox_fixedmax);


        verticalLayout->addLayout(horizontalLayout);

        line_3 = new QFrame(display);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(10, 350, 581, 20));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy2);
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        horizontalLayoutWidget = new QWidget(display);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 410, 581, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        checkBox_expertmode = new QCheckBox(horizontalLayoutWidget);
        checkBox_expertmode->setObjectName("checkBox_expertmode");

        horizontalLayout_2->addWidget(checkBox_expertmode);

        checkBox_enablecalib = new QCheckBox(horizontalLayoutWidget);
        checkBox_enablecalib->setObjectName("checkBox_enablecalib");

        horizontalLayout_2->addWidget(checkBox_enablecalib);

        pushButton_loadcalib = new QPushButton(horizontalLayoutWidget);
        pushButton_loadcalib->setObjectName("pushButton_loadcalib");

        horizontalLayout_2->addWidget(pushButton_loadcalib);

        pushButton_savecalib = new QPushButton(horizontalLayoutWidget);
        pushButton_savecalib->setObjectName("pushButton_savecalib");
        pushButton_savecalib->setEnabled(false);

        horizontalLayout_2->addWidget(pushButton_savecalib);

        horizontalLayoutWidget_2 = new QWidget(display);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 370, 581, 41));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(horizontalLayoutWidget_2);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Sunken);
        lcdNumber_mean = new QLCDNumber(frame);
        lcdNumber_mean->setObjectName("lcdNumber_mean");
        lcdNumber_mean->setGeometry(QRect(50, 0, 91, 41));
        lcdNumber_mean->setFrameShape(QFrame::NoFrame);
        lcdNumber_mean->setFrameShadow(QFrame::Plain);
        lcdNumber_mean->setSmallDecimalPoint(true);
        lcdNumber_mean->setProperty("value", QVariant(0.000000000000000));
        lcdNumber_mean->setProperty("intValue", QVariant(0));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 61, 21));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setTextFormat(Qt::RichText);
        label->setScaledContents(true);

        horizontalLayout_5->addWidget(frame);

        frame_4 = new QFrame(horizontalLayoutWidget_2);
        frame_4->setObjectName("frame_4");
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(frame_4);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 10, 61, 21));
        label_4->setFont(font);
        label_4->setTextFormat(Qt::RichText);
        label_4->setScaledContents(true);
        lcdNumber_status = new QLCDNumber(frame_4);
        lcdNumber_status->setObjectName("lcdNumber_status");
        lcdNumber_status->setGeometry(QRect(50, 0, 91, 41));
        lcdNumber_status->setFrameShape(QFrame::NoFrame);
        lcdNumber_status->setFrameShadow(QFrame::Plain);
        lcdNumber_status->setSmallDecimalPoint(true);
        lcdNumber_status->setProperty("value", QVariant(0.000000000000000));
        lcdNumber_status->setProperty("intValue", QVariant(0));

        horizontalLayout_5->addWidget(frame_4);

        frame_3 = new QFrame(horizontalLayoutWidget_2);
        frame_3->setObjectName("frame_3");
        frame_3->setFrameShape(QFrame::WinPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        lcdNumber_focus = new QLCDNumber(frame_3);
        lcdNumber_focus->setObjectName("lcdNumber_focus");
        lcdNumber_focus->setGeometry(QRect(60, 0, 71, 41));
        lcdNumber_focus->setFrameShape(QFrame::NoFrame);
        lcdNumber_focus->setFrameShadow(QFrame::Plain);
        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(8, 10, 61, 21));
        label_2->setFont(font);

        horizontalLayout_5->addWidget(frame_3);

        frame_2 = new QFrame(horizontalLayoutWidget_2);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::WinPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        lcdNumber_max = new QLCDNumber(frame_2);
        lcdNumber_max->setObjectName("lcdNumber_max");
        lcdNumber_max->setGeometry(QRect(50, 0, 71, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(8);
        lcdNumber_max->setFont(font1);
        lcdNumber_max->setFrameShape(QFrame::NoFrame);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(8, 10, 61, 21));
        label_3->setFont(font);

        horizontalLayout_5->addWidget(frame_2);


        retranslateUi(display);

        QMetaObject::connectSlotsByName(display);
    } // setupUi

    void retranslateUi(QDialog *display)
    {
        display->setWindowTitle(QCoreApplication::translate("display", "Online BPMDisplay", nullptr));
        radioButtonAutoscale->setText(QCoreApplication::translate("display", "Auto Y-Scale", nullptr));
        radioButtonMaxScale->setText(QCoreApplication::translate("display", "Max Y-Scale", nullptr));
        radioButtonFixedScale->setText(QCoreApplication::translate("display", "Fixed Y-Scale", nullptr));
        checkBox_expertmode->setText(QCoreApplication::translate("display", "expert\n"
"mode", nullptr));
        checkBox_enablecalib->setText(QCoreApplication::translate("display", "enable\n"
"calibration", nullptr));
        pushButton_loadcalib->setText(QCoreApplication::translate("display", "Load calib", nullptr));
        pushButton_savecalib->setText(QCoreApplication::translate("display", "save calib", nullptr));
        label->setText(QCoreApplication::translate("display", "MEAN", nullptr));
        label_4->setText(QCoreApplication::translate("display", "Status", nullptr));
        label_2->setText(QCoreApplication::translate("display", "FOCUS", nullptr));
        label_3->setText(QCoreApplication::translate("display", "MAX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class display: public Ui_display {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAY_H
