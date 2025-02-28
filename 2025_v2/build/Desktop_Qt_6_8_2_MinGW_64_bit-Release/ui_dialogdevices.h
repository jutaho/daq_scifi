/********************************************************************************
** Form generated from reading UI file 'dialogdevices.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDEVICES_H
#define UI_DIALOGDEVICES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogDevices
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *spinNrDevices;
    QTableWidget *tableDevices;

    void setupUi(QDialog *DialogDevices)
    {
        if (DialogDevices->objectName().isEmpty())
            DialogDevices->setObjectName("DialogDevices");
        DialogDevices->resize(573, 233);
        buttonBox = new QDialogButtonBox(DialogDevices);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(210, 190, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(DialogDevices);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 10, 531, 171));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        spinNrDevices = new QSpinBox(verticalLayoutWidget);
        spinNrDevices->setObjectName("spinNrDevices");
        spinNrDevices->setMinimum(1);

        horizontalLayout_2->addWidget(spinNrDevices);


        verticalLayout->addLayout(horizontalLayout_2);

        tableDevices = new QTableWidget(verticalLayoutWidget);
        tableDevices->setObjectName("tableDevices");

        verticalLayout->addWidget(tableDevices);


        retranslateUi(DialogDevices);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, DialogDevices, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, DialogDevices, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DialogDevices);
    } // setupUi

    void retranslateUi(QDialog *DialogDevices)
    {
        DialogDevices->setWindowTitle(QCoreApplication::translate("DialogDevices", "Devices", nullptr));
        label->setText(QCoreApplication::translate("DialogDevices", "Number of devices", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogDevices: public Ui_DialogDevices {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDEVICES_H
