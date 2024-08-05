#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../QWaveshare/WS_Device.h"
#include <QMainWindow>
#include <QMutex>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QThread>
#include "scanthread.h"
#include <QListWidgetItem>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_comboBox_4_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_5_currentIndexChanged(int index);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_itemSelectionChanged();

private:
    Ui::MainWindow *ui;

    WS_Device * m_Config;

    QMutex m_Mutex;
    QSerialPort m_SerialPort;

    int curSeldevice(void);

    ScanThread * m_ScanThread;

    QSerialPort::BaudRate GetSelectedBaud(void);
    QSerialPort::Parity GetSelectedParity(void);

public slots:
    void WSDeviceInfoCallback(MessageType mType, QString sInfo);
    void deviceDiscovered(int iAddress);
    void scanComplete();

};
#endif // MAINWINDOW_H
