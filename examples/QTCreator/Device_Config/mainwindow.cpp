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
#include <QMessageBox>

#include "baudratedialog.h"
#include "ui_baudratedialog.h"

#include <sstream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->comboBox->addItem("");

    std::vector<std::string> availPorts = m_sPort.EnumeratePorts();

    for (int i = 0; i<availPorts.size(); i++)
    {
        ui->comboBox->addItem(QString::fromStdString(availPorts[i]));
    }

    m_Config = new WS_Device(&m_sPort);

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


    m_ScanThread = new ScanThread(this,m_Config);

    QObject::connect(m_ScanThread, &ScanThread::deviceDiscovered,
                      this, &MainWindow::deviceDiscovered);
    QObject::connect(m_ScanThread, &ScanThread::scanComplete,
                      this, &MainWindow::scanComplete);

    this->setFixedSize(this->size()); // Fix the size to the current size
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

}

MainWindow::~MainWindow()
{

    m_sPort.ClosePort();
    delete m_Config;

    delete ui;
}

sp_parity MainWindow::GetSelectedParity(void)
{

    sp_parity brSelParity;

    brSelParity = sp_parity::SP_PARITY_NONE;

    switch(ui->comboBox_5->currentIndex())
    {
        case 0:
            brSelParity = sp_parity::SP_PARITY_NONE;
        break;

        case 1:
            brSelParity = sp_parity::SP_PARITY_EVEN;
        break;

        case 2:
            brSelParity = sp_parity::SP_PARITY_ODD;
        break;
    }

    return brSelParity;
}

WSBaudRates MainWindow::GetSelectedBaud(void)
{
    WSBaudRates brSelRate = WSBaudRates::Baud9600;

    switch(ui->comboBox_4->currentIndex())
    {
    case 0:
        brSelRate = WSBaudRates::Baud4800;
    break;
    case 1:
        brSelRate = WSBaudRates::Baud9600;
    break;
    case 2:
        brSelRate = WSBaudRates::Baud19200;
    break;
    case 3:
        brSelRate = WSBaudRates::Baud38400;
    break;
    case 4:
        brSelRate = WSBaudRates::Baud57600;
    break;
    case 5:
        brSelRate = WSBaudRates::Baud115200;
    break;
    }

    return brSelRate;
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

    QIcon myIcon("../ModbusIcon.png");

    myItem->setIcon(myIcon);

    ui->listWidget->addItem(myItem);
}

void MainWindow::on_pushButton_clicked()
{

    unsigned char deviceAddress = 0;

    bool bResult = m_Config->ReadDeviceAddress(deviceAddress);

    if(bResult)
    {
        if(deviceAddress!=0)
        {
            ui->listWidget->clear();

            QListWidgetItem * myItem = new QListWidgetItem();

            myItem->setText("Device " + QString::number(deviceAddress));

            QIcon myIcon("../ModbusIcon.png");

            myItem->setIcon(myIcon);

            ui->listWidget->addItem(myItem);

            if(ui->listWidget->count()!=0)
                ui->listWidget->setCurrentRow(0);

        }
    }


    responseHandler(bResult);
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

            responseHandler(bResult);
        }
    }
}


void MainWindow::on_pushButton_3_clicked()
{

    float fVersion = 0;

    int deviceAddress = curSeldevice();

    if(deviceAddress!=-1)
    {
        bool bResult = m_Config->ReadSoftwareVersion(deviceAddress,fVersion);

        responseHandler(bResult);

        if(bResult)
        {
            QString sVersion = QString::number(fVersion,'f',2);

            ui->textEdit->append("Device " + QString::number(deviceAddress) + " software version: " + sVersion);
        }
    }
    else
    {
        ui->textEdit->append("No Device Selected");
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

            WSBaudRates newBaudRate = brDialog->GetBaudRate();
            sp_parity   newParity   = brDialog->GetParity();

            bool bResult = m_Config->SetBaudRate(iCurrentDevice,newBaudRate,newParity);

            responseHandler(bResult);

        }

        delete brDialog;
    }

}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index!=0)
    {
        QString sPortName = ui->comboBox->currentText();

        if(!m_sPort.OpenPort(sPortName.toStdString()))
        {
            QMessageBox::critical(this,"Error","Port failed to open");
        }
    }
}




void MainWindow::on_listWidget_itemSelectionChanged()
{
    QList<QListWidgetItem *> qItems = ui->listWidget->selectedItems();

    bool bButtonsEnabled = qItems.length();

    ui->pushButton_2->setEnabled(bButtonsEnabled);
    ui->pushButton_3->setEnabled(bButtonsEnabled);
    ui->pushButton_6->setEnabled(bButtonsEnabled);
}

QString MainWindow::charToQstring(char * array, int iSize)
{
    QString qArray;

    for(int i=0;i<iSize;i++)
    {
        qArray += QString("0x%1").arg(array[i],2,16,QLatin1Char('0')) + " ";
    }

    return qArray;
}


void MainWindow::responseHandler(QString response)
{
    qDebug() << response;

    ui->textEdit->append(response);
}

void MainWindow::responseHandler(bool bResult)
{
    char lastTx[XBUFF_SIZE]={0};
    char lastRx[XBUFF_SIZE]={0};

    int sizeofTx= 0;
    int sizeofRx= 0;

    m_Config->GetLastTX(lastTx,&sizeofTx);
    m_Config->GetLastRX(lastRx,&sizeofRx);

    QString qsMessage;

    qsMessage = "Sent " + QString::number(sizeofTx) + " bytes : " + charToQstring(lastTx,sizeofTx);

    responseHandler(qsMessage);


    qsMessage = "Received " + QString::number(sizeofRx) + " bytes : " + charToQstring(lastRx,sizeofRx);

    responseHandler(qsMessage);


    if(!bResult)
    {
        qsMessage = "Error : " + QString::fromStdString(m_Config->GetLastError());

        responseHandler(qsMessage);
    }


}
