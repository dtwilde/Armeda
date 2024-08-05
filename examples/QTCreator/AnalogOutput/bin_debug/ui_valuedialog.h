/********************************************************************************
** Form generated from reading UI file 'valueDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VALUEDIALOG_H
#define UI_VALUEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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
    QLineEdit *lineEdit;

    void setupUi(QDialog *valueDialog)
    {
        if (valueDialog->objectName().isEmpty())
            valueDialog->setObjectName(QString::fromUtf8("valueDialog"));
        valueDialog->resize(406, 67);
        buttonBox = new QDialogButtonBox(valueDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 25, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(valueDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 32, 91, 16));
        lineEdit = new QLineEdit(valueDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(70, 30, 113, 22));

        retranslateUi(valueDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), valueDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), valueDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(valueDialog);
    } // setupUi

    void retranslateUi(QDialog *valueDialog)
    {
        valueDialog->setWindowTitle(QCoreApplication::translate("valueDialog", "Change Data Types", nullptr));
        label->setText(QCoreApplication::translate("valueDialog", "Value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class valueDialog: public Ui_valueDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VALUEDIALOG_H
