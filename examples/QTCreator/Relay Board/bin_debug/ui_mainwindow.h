/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *comboBox;
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_6;
    QPushButton *pushButton;
    QWidget *tab_2;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_14;
    QCheckBox *checkBox_15;
    QCheckBox *checkBox_16;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QWidget *tab_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton_4;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QTextEdit *textEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(414, 467);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(50, 20, 331, 22));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(15, 24, 57, 14));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 60, 361, 281));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        checkBox_5 = new QCheckBox(tab);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(200, 30, 85, 20));
        checkBox_4 = new QCheckBox(tab);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(60, 120, 85, 20));
        checkBox_2 = new QCheckBox(tab);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(60, 60, 85, 20));
        checkBox_3 = new QCheckBox(tab);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(60, 90, 85, 20));
        checkBox = new QCheckBox(tab);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(60, 30, 85, 20));
        checkBox_7 = new QCheckBox(tab);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setGeometry(QRect(200, 90, 85, 20));
        checkBox_8 = new QCheckBox(tab);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setGeometry(QRect(200, 120, 85, 20));
        checkBox_6 = new QCheckBox(tab);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setGeometry(QRect(200, 60, 85, 20));
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 210, 141, 22));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        checkBox_9 = new QCheckBox(tab_2);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
        checkBox_9->setGeometry(QRect(60, 30, 85, 20));
        checkBox_10 = new QCheckBox(tab_2);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));
        checkBox_10->setGeometry(QRect(60, 60, 85, 20));
        checkBox_11 = new QCheckBox(tab_2);
        checkBox_11->setObjectName(QString::fromUtf8("checkBox_11"));
        checkBox_11->setGeometry(QRect(60, 90, 85, 20));
        checkBox_12 = new QCheckBox(tab_2);
        checkBox_12->setObjectName(QString::fromUtf8("checkBox_12"));
        checkBox_12->setGeometry(QRect(60, 120, 85, 20));
        checkBox_13 = new QCheckBox(tab_2);
        checkBox_13->setObjectName(QString::fromUtf8("checkBox_13"));
        checkBox_13->setGeometry(QRect(200, 30, 85, 20));
        checkBox_14 = new QCheckBox(tab_2);
        checkBox_14->setObjectName(QString::fromUtf8("checkBox_14"));
        checkBox_14->setGeometry(QRect(200, 60, 85, 20));
        checkBox_15 = new QCheckBox(tab_2);
        checkBox_15->setObjectName(QString::fromUtf8("checkBox_15"));
        checkBox_15->setGeometry(QRect(200, 90, 85, 20));
        checkBox_16 = new QCheckBox(tab_2);
        checkBox_16->setObjectName(QString::fromUtf8("checkBox_16"));
        checkBox_16->setGeometry(QRect(200, 120, 85, 20));
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(200, 210, 141, 22));
        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 210, 141, 22));
        pushButton_5 = new QPushButton(tab_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(20, 180, 91, 22));
        pushButton_6 = new QPushButton(tab_2);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(140, 180, 91, 22));
        pushButton_7 = new QPushButton(tab_2);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(250, 180, 91, 22));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        lineEdit = new QLineEdit(tab_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(200, 80, 51, 22));
        pushButton_4 = new QPushButton(tab_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(260, 80, 80, 22));
        comboBox_2 = new QComboBox(tab_3);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(20, 80, 91, 22));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(200, 60, 57, 14));
        comboBox_3 = new QComboBox(tab_3);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(120, 80, 71, 22));
        tabWidget->addTab(tab_3, QString());
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 360, 361, 70));
        textEdit->setReadOnly(true);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        checkBox_5->setText(QCoreApplication::translate("MainWindow", "Relay 5", nullptr));
        checkBox_4->setText(QCoreApplication::translate("MainWindow", "Relay 4", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "Relay 2", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "Relay 3", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Relay 1", nullptr));
        checkBox_7->setText(QCoreApplication::translate("MainWindow", "Relay 7", nullptr));
        checkBox_8->setText(QCoreApplication::translate("MainWindow", "Relay 8", nullptr));
        checkBox_6->setText(QCoreApplication::translate("MainWindow", "Relay 6", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Get Relay States", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Individual Control", nullptr));
        checkBox_9->setText(QCoreApplication::translate("MainWindow", "Relay 1", nullptr));
        checkBox_10->setText(QCoreApplication::translate("MainWindow", "Relay 2", nullptr));
        checkBox_11->setText(QCoreApplication::translate("MainWindow", "Relay 3", nullptr));
        checkBox_12->setText(QCoreApplication::translate("MainWindow", "Relay 4", nullptr));
        checkBox_13->setText(QCoreApplication::translate("MainWindow", "Relay 5", nullptr));
        checkBox_14->setText(QCoreApplication::translate("MainWindow", "Relay 6", nullptr));
        checkBox_15->setText(QCoreApplication::translate("MainWindow", "Relay 7", nullptr));
        checkBox_16->setText(QCoreApplication::translate("MainWindow", "Relay 8", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Set Relay States", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Get Relay States", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "All On", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "All Off", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Toggle", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Group Control", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Flash", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Interval", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Flash On/Off", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
