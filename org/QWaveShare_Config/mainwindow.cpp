#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIcon>
#include <QListWidgetItem>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QApplication>
#include <QDebug>
#include <QInputDialog>
#include <QWaitCondition>

#include "baudratedialog.h"
#include "ui_baudratedialog.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        ui->comboBox->addItem(info.portName());
    }


    for (int i=1;i<256;i++)
    {
        QString szNum = QString::number(i);

        ui->comboBox_2->addItem(szNum);
        ui->comboBox_3->addItem(szNum);

    }
    ui->comboBox_3->setCurrentIndex(11);


    ui->comboBox_4->addItem("4800");
    ui->comboBox_4->addItem("9600");
    ui->comboBox_4->addItem("19200");
    ui->comboBox_4->addItem("38400");
    ui->comboBox_4->addItem("57600");
    ui->comboBox_4->addItem("115200");
    ui->comboBox_4->setCurrentIndex(1);

    ui->comboBox_5->addItem("None");
    ui->comboBox_5->addItem("Even");
    ui->comboBox_5->addItem("Odd");


    ui->groupBox->setStyleSheet("font-weight: normal;");

    m_SerialPort.setPortName(ui->comboBox->currentText());
    m_SerialPort.setBaudRate(GetSelectedBaud());
    m_SerialPort.setParity(GetSelectedParity());


    m_Config = new WS_Device(m_Mutex,m_SerialPort,250);
    m_ScanThread = new ScanThread(this,m_Config);

    QObject::connect(m_Config, &WS_Device::infoCallback,
                      this, &MainWindow::WSDeviceInfoCallback);

    QObject::connect(m_ScanThread, &ScanThread::deviceDiscovered,
                      this, &MainWindow::deviceDiscovered);
    QObject::connect(m_ScanThread, &ScanThread::scanComplete,
                      this, &MainWindow::scanComplete);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSerialPort::Parity MainWindow::GetSelectedParity(void)
{

    //NoParity = 0,EvenParity = 2,OddParity = 3,

    QSerialPort::Parity brSelParity;

    brSelParity = QSerialPort::NoParity;

    switch(ui->comboBox_5->currentIndex())
    {
        case 0:
            brSelParity = QSerialPort::NoParity;
        break;

        case 1:
            brSelParity = QSerialPort::EvenParity;
        break;

        case 2:
            brSelParity = QSerialPort::OddParity;
        break;
    }

    return brSelParity;
}

QSerialPort::BaudRate MainWindow::GetSelectedBaud(void)
{
    QSerialPort::BaudRate brSelRate = QSerialPort::Baud9600;

    switch(ui->comboBox_4->currentIndex())
    {
    case 0:
        brSelRate = QSerialPort::Baud4800;
    break;
    case 1:
        brSelRate = QSerialPort::Baud9600;
    break;
    case 2:
        brSelRate = QSerialPort::Baud19200;
    break;
    case 3:
        brSelRate = QSerialPort::Baud38400;
    break;
    case 4:
        brSelRate = QSerialPort::Baud57600;
    break;
    case 5:
        brSelRate = QSerialPort::Baud115200;
    break;
    }

    return brSelRate;
}


void MainWindow::WSDeviceInfoCallback(MessageType  mType, QString sInfo)
{
    ui->textEdit->append(sInfo);
}

void MainWindow::scanComplete()
{
    ui->pushButton->setDisabled(false);
    ui->pushButton_4->setDisabled(false);

    ui->pushButton_5->setDisabled(true);
    ui->comboBox->setDisabled((false));
    ui->comboBox_2->setDisabled((false));
    ui->comboBox_3->setDisabled((false));
    ui->comboBox_4->setDisabled((false));
    ui->comboBox_5->setDisabled((false));

    if(ui->listWidget->count()!=0)
        ui->listWidget->setCurrentRow(0);
}


void MainWindow::deviceDiscovered(int iAddress)
{
    //a device was found
    QListWidgetItem * myItem = new QListWidgetItem();

    myItem->setText("Device " + QString::number(iAddress));

    QIcon myIcon("/home/dean/Desktop/WaveShareProject/QWaveShare_Config/ModbusIcon.png");

    myItem->setIcon(myIcon);

    ui->listWidget->addItem(myItem);
}

void MainWindow::on_pushButton_clicked()
{

    int iAddress = 0;

    bool bResult = m_Config->ReadDeviceAddress(iAddress);

    if(bResult)
    {
        if(iAddress!=0)
        {
            ui->listWidget->clear();

            QListWidgetItem * myItem = new QListWidgetItem();

            myItem->setText("Device " + QString::number(iAddress));

            QIcon myIcon("/home/dean/Desktop/WaveShareProject/QWaveShare_Config/ModbusIcon.png");

            myItem->setIcon(myIcon);

            ui->listWidget->addItem(myItem);

            if(ui->listWidget->count()!=0)
                ui->listWidget->setCurrentRow(0);

        }
    }
    else
    {
        WSDeviceInfoCallback(MessageType::Error, "Failed to read device address: This only works with 1 device connected");
    }

}


int MainWindow::curSeldevice(void)
{
    int deviceAddress = -1;

    QListWidgetItem * curItem = ui->listWidget->currentItem();

    if(curItem!=NULL)
    {
        deviceAddress = curItem->text().replace("Device ","").toInt();
    }

    return deviceAddress;

}
void MainWindow::on_pushButton_2_clicked()
{
    int deviceAddress = curSeldevice();

    bool bOk = false;

    if(deviceAddress!=-1)
    {
        int iNewAddress =  QInputDialog::getInt(this,"  ","New Address",deviceAddress,1,255,1,&bOk);

        if(bOk)
        {
            bool bResult = m_Config->SetDeviceAddress(deviceAddress,iNewAddress);


            QListWidgetItem * curItem = ui->listWidget->currentItem();

            if(curItem)
                ui->listWidget->takeItem(ui->listWidget->row(curItem));


            m_ScanThread->beginScan(iNewAddress, iNewAddress+1);

        }
    }
}


void MainWindow::on_pushButton_3_clicked()
{

    int iCurrentDevice = curSeldevice();

    float fVersion = 0;

    if(iCurrentDevice!=-1)
    {
        if(m_Config->ReadSoftwareVersion(iCurrentDevice,fVersion))
        {
            QString sVersion = QString::number(fVersion,'f',2);

            WSDeviceInfoCallback(MessageType::Info, "Device " + QString::number(iCurrentDevice) + " is running software version " + sVersion);
        }

    }

}


void MainWindow::on_pushButton_4_clicked()
{

    int iStartRange = ui->comboBox_2->currentText().toInt();
    int iEndRange = ui->comboBox_3->currentText().toInt();


    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(false);
    ui->pushButton_6->setDisabled(true);

    ui->comboBox->setDisabled((true));
    ui->comboBox_2->setDisabled((true));
    ui->comboBox_3->setDisabled((true));
    ui->comboBox_4->setDisabled((true));
    ui->comboBox_5->setDisabled((true));


    m_ScanThread->beginScan(iStartRange, iEndRange);

    ui->listWidget->clear();

}


void MainWindow::on_pushButton_5_clicked()
{

    m_ScanThread->stopScan();

}


void MainWindow::on_pushButton_6_clicked()
{

    int iCurrentDevice = curSeldevice();

    if(iCurrentDevice!=-1)
    {

        baudRateDialog * brDialog = new baudRateDialog(this);

        brDialog->SetParity(GetSelectedParity());
        brDialog->SetBaudRate(GetSelectedBaud());

        if(brDialog->exec()==QDialog::Accepted)
        {

            QSerialPort::BaudRate newBaudRate = brDialog->GetBaudRate();
            QSerialPort::Parity   newParity   = brDialog->GetParity();


            m_Config->SetBaudRate(iCurrentDevice,newBaudRate,newParity);

        }

        delete brDialog;
    }

}


void MainWindow::on_comboBox_4_currentIndexChanged(int index)
{
    m_SerialPort.setBaudRate(GetSelectedBaud());
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    m_SerialPort.setPortName(ui->comboBox->currentText());
}


void MainWindow::on_comboBox_5_currentIndexChanged(int index)
{
    m_SerialPort.setParity(GetSelectedParity());
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

}


void MainWindow::on_listWidget_itemSelectionChanged()
{
    QList<QListWidgetItem *> qItems = ui->listWidget->selectedItems();

    bool bButtonsEnabled = qItems.length();

    ui->pushButton_2->setEnabled(bButtonsEnabled);
    ui->pushButton_3->setEnabled(bButtonsEnabled);
    ui->pushButton_6->setEnabled(bButtonsEnabled);
}

