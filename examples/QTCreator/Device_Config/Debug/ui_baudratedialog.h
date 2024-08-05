/********************************************************************************
** Form generated from reading UI file 'baudratedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BAUDRATEDIALOG_H
#define UI_BAUDRATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_baudRateDialog
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox_2;

    void setupUi(QDialog *baudRateDialog)
    {
        if (baudRateDialog->objectName().isEmpty())
            baudRateDialog->setObjectName(QString::fromUtf8("baudRateDialog"));
        baudRateDialog->resize(442, 67);
        buttonBox = new QDialogButtonBox(baudRateDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(83, 25, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        comboBox = new QComboBox(baudRateDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 30, 131, 22));
        label = new QLabel(baudRateDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 91, 16));
        label_2 = new QLabel(baudRateDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 10, 71, 16));
        comboBox_2 = new QComboBox(baudRateDialog);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(150, 30, 91, 22));

        retranslateUi(baudRateDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), baudRateDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), baudRateDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(baudRateDialog);
    } // setupUi

    void retranslateUi(QDialog *baudRateDialog)
    {
        baudRateDialog->setWindowTitle(QCoreApplication::translate("baudRateDialog", "Change Baud Rate", nullptr));
        label->setText(QCoreApplication::translate("baudRateDialog", "Baud Rate", nullptr));
        label_2->setText(QCoreApplication::translate("baudRateDialog", "Parity", nullptr));
    } // retranslateUi

};

namespace Ui {
    class baudRateDialog: public Ui_baudRateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BAUDRATEDIALOG_H
