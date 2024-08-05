#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "WS_Device.h"
#include <QMainWindow>
#include <QMutex>
#include <QThread>
#include "scanthread.h"
#include <QListWidgetItem>
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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_listWidget_itemSelectionChanged();

private:
    Ui::MainWindow *ui;

    WS_Device * m_Config;

    int curSeldevice(void);

    ScanThread * m_ScanThread;

    WSBaudRates GetSelectedBaud(void);
    sp_parity GetSelectedParity(void);

    void responseHandler(bool bResult);

    void responseHandler(QString response);

    QString charToQstring(char * array, int iSize);

    LibSerialPortWrapper m_sPort;

public slots:
    void deviceDiscovered(int iAddress);
    void scanComplete();

};
#endif // MAINWINDOW_H
