/********************************************************************************
** Form generated from reading UI file 'controlmode.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLMODE_H
#define UI_CONTROLMODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ControlMode
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLabel *label_2;

    void setupUi(QDialog *ControlMode)
    {
        if (ControlMode->objectName().isEmpty())
            ControlMode->setObjectName(QString::fromUtf8("ControlMode"));
        ControlMode->resize(409, 70);
        buttonBox = new QDialogButtonBox(ControlMode);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(50, 22, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(ControlMode);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 71, 16));
        comboBox = new QComboBox(ControlMode);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(20, 30, 79, 22));
        comboBox_2 = new QComboBox(ControlMode);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(120, 30, 79, 22));
        label_2 = new QLabel(ControlMode);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(120, 10, 101, 16));

        retranslateUi(ControlMode);
        QObject::connect(buttonBox, SIGNAL(accepted()), ControlMode, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ControlMode, SLOT(reject()));

        QMetaObject::connectSlotsByName(ControlMode);
    } // setupUi

    void retranslateUi(QDialog *ControlMode)
    {
        ControlMode->setWindowTitle(QCoreApplication::translate("ControlMode", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ControlMode", "Channel", nullptr));
        label_2->setText(QCoreApplication::translate("ControlMode", "Control Mode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlMode: public Ui_ControlMode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLMODE_H
