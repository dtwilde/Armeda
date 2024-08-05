#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "libserialport.h"

#include "WS_Device.h"
#include "WS_Digital_IO.h"
#include "LibSerialPortWrapper.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_comboBox_currentIndexChanged(int index);


    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_5_clicked();

    void on_checkBox_6_clicked();

    void on_checkBox_7_clicked();

    void on_checkBox_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

private:
    Ui::MainWindow *ui;

    QString charToQstring(char * array, int iSize);
    void responseHandler(bool bResult);

    WS_Digital_IO * m_DigitalIO;

    LibSerialPortWrapper m_sPort;

    char m_deviceAddress;
};
#endif // MAINWINDOW_H
