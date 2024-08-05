#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "../QWaveshare/WS_RTURelay.h"

#include "../QWaveshare/WS_AnalogInput.h"

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

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_5_clicked();

    void on_checkBox_6_clicked();

    void on_checkBox_7_clicked();

    void on_checkBox_8_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_4_currentIndexChanged(int index);

    void on_comboBox_5_currentIndexChanged(int index);

    void on_comboBox_6_currentIndexChanged(int index);

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;

    WS_RTURelay * m_RelayBoard;
    WS_AnalogInput * m_AnalogInput;

    QMutex m_SerialPortMutex;
    QSerialPort m_SerialPort;

    void UpdateRelayUI(void);


    QSerialPort::BaudRate GetSelectedBaud(void);
    QSerialPort::Parity GetSelectedParity(void);
    int GetDeviceAddress(void);

};
#endif // MAINWINDOW_H
