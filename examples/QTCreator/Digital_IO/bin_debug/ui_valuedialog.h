/********************************************************************************
** Form generated from reading UI file 'valuedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VALUEDIALOG_H
#define UI_VALUEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_valueDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QLineEdit *lineEdit;

    void setupUi(QDialog *valueDialog)
    {
        if (valueDialog->objectName().isEmpty())
            valueDialog->setObjectName(QString::fromUtf8("valueDialog"));
        valueDialog->resize(516, 66);
        buttonBox = new QDialogButtonBox(valueDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(150, 20, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(valueDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 29, 71, 16));
        comboBox = new QComboBox(valueDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(90, 25, 61, 22));
        label_2 = new QLabel(valueDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 29, 71, 16));
        lineEdit = new QLineEdit(valueDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(238, 25, 61, 22));

        retranslateUi(valueDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), valueDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), valueDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(valueDialog);
    } // setupUi

    void retranslateUi(QDialog *valueDialog)
    {
        valueDialog->setWindowTitle(QCoreApplication::translate("valueDialog", "New Value", nullptr));
        label->setText(QCoreApplication::translate("valueDialog", "Channel", nullptr));
        label_2->setText(QCoreApplication::translate("valueDialog", "Interval", nullptr));
    } // retranslateUi

};

namespace Ui {
    class valueDialog: public Ui_valueDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VALUEDIALOG_H
