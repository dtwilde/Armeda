/********************************************************************************
** Form generated from reading UI file 'baudRate.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BAUDRATE_H
#define UI_BAUDRATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_baudrateDialog
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *comboBox;
    QLabel *label;

    void setupUi(QDialog *baudrateDialog)
    {
        if (baudrateDialog->objectName().isEmpty())
            baudrateDialog->setObjectName(QString::fromUtf8("baudrateDialog"));
        baudrateDialog->resize(428, 72);
        buttonBox = new QDialogButtonBox(baudrateDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(80, 20, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        comboBox = new QComboBox(baudrateDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(108, 25, 121, 22));
        label = new QLabel(baudrateDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 28, 101, 16));

        retranslateUi(baudrateDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), baudrateDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), baudrateDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(baudrateDialog);
    } // setupUi

    void retranslateUi(QDialog *baudrateDialog)
    {
        baudrateDialog->setWindowTitle(QCoreApplication::translate("baudrateDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("baudrateDialog", "New Baud Rate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class baudrateDialog: public Ui_baudrateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BAUDRATE_H
