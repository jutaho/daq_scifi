/********************************************************************************
** Form generated from reading UI file 'dialoghostip.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGHOSTIP_H
#define UI_DIALOGHOSTIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogHostIp
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineIp;

    void setupUi(QDialog *DialogHostIp)
    {
        if (DialogHostIp->objectName().isEmpty())
            DialogHostIp->setObjectName("DialogHostIp");
        DialogHostIp->resize(185, 99);
        buttonBox = new QDialogButtonBox(DialogHostIp);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(10, 60, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        horizontalLayoutWidget = new QWidget(DialogHostIp);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 160, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineIp = new QLineEdit(horizontalLayoutWidget);
        lineIp->setObjectName("lineIp");

        horizontalLayout->addWidget(lineIp);


        retranslateUi(DialogHostIp);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, DialogHostIp, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, DialogHostIp, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DialogHostIp);
    } // setupUi

    void retranslateUi(QDialog *DialogHostIp)
    {
        DialogHostIp->setWindowTitle(QCoreApplication::translate("DialogHostIp", "Host IP", nullptr));
        label->setText(QCoreApplication::translate("DialogHostIp", "Host IP:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogHostIp: public Ui_DialogHostIp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGHOSTIP_H
