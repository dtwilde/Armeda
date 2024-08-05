/********************************************************************************
** Form generated from reading UI file 'dataTypedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATATYPEDIALOG_H
#define UI_DATATYPEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_dataTypeDialog
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *comboBox;
    QLabel *label;

    void setupUi(QDialog *dataTypeDialog)
    {
        if (dataTypeDialog->objectName().isEmpty())
            dataTypeDialog->setObjectName(QString::fromUtf8("dataTypeDialog"));
        dataTypeDialog->resize(425, 67);
        buttonBox = new QDialogButtonBox(dataTypeDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(60, 25, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        comboBox = new QComboBox(dataTypeDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 30, 211, 22));
        label = new QLabel(dataTypeDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 91, 16));

        retranslateUi(dataTypeDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), dataTypeDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dataTypeDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(dataTypeDialog);
    } // setupUi

    void retranslateUi(QDialog *dataTypeDialog)
    {
        dataTypeDialog->setWindowTitle(QCoreApplication::translate("dataTypeDialog", "Change Data Types", nullptr));
        label->setText(QCoreApplication::translate("dataTypeDialog", "Data Type", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dataTypeDialog: public Ui_dataTypeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATATYPEDIALOG_H
