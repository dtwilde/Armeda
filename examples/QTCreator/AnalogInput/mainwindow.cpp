#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QString>
#include <QDebug>
#include "dataTypedialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_deviceAddress = 1;

    std::vector<std::string> availPorts = m_sPort.EnumeratePorts();

    for (int i = 0; i<availPorts.size(); i++)
    {
        ui->comboBox->addItem(QString::fromStdString(availPorts[i]));
    }

    m_AnalogInput = new WS_AnalogInput(&m_sPort);
}

MainWindow::~MainWindow()
{

    m_sPort.ClosePort();

    delete m_AnalogInput;

    delete ui;
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

void MainWindow::responseHandler(bool bResult)
{
    char lastTx[XBUFF_SIZE]={0};
    char lastRx[XBUFF_SIZE]={0};

    int sizeofTx= 0;
    int sizeofRx= 0;

    m_AnalogInput->GetLastTX(lastTx,&sizeofTx);
    m_AnalogInput->GetLastRX(lastRx,&sizeofRx);

    if(sizeofTx!=0)
    {
        QString txData =  "Sent " + QString::number(sizeofTx) + " bytes     :" + charToQstring(lastTx,sizeofTx);
        QString rxData =  "Received " + QString::number(sizeofRx) + " bytes :" + charToQstring(lastRx,sizeofRx);

        ui->textEdit->append(txData);
        ui->textEdit->append(rxData);

        qDebug() << txData;
        qDebug() << rxData;
    }
    if(!bResult)
    {
        QString qError = "Error:" + QString::fromStdString(m_AnalogInput->GetLastError());

        ui->textEdit->append(qError);

        qDebug() << qError;

    }
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

void MainWindow::on_pushButton_clicked()
{
    std::vector<float> vResults;

    bool bResult = m_AnalogInput->ReadAnalogInput(m_deviceAddress,0,8,vResults);

    responseHandler(bResult);


    if(vResults.size()==8)
    {
        ui->lineEdit_1->setText(QString::number(vResults[0]/1000));
        ui->lineEdit_2->setText(QString::number(vResults[1]/1000));
        ui->lineEdit_3->setText(QString::number(vResults[2]/1000));
        ui->lineEdit_4->setText(QString::number(vResults[3]/1000));
        ui->lineEdit_5->setText(QString::number(vResults[4]/1000));
        ui->lineEdit_6->setText(QString::number(vResults[5]/1000));
        ui->lineEdit_7->setText(QString::number(vResults[6]/1000));
        ui->lineEdit_8->setText(QString::number(vResults[7]/1000));
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    std::vector<AnalogIOChannelType> vResults;

    bool bResult = m_AnalogInput->ReadChannelDataType(m_deviceAddress,0,8,vResults);

    responseHandler(bResult);

    for(int i=0; i<vResults.size();i++)
    {
        QString channelType = "";

        if(vResults[i] == AnalogIOChannelType::Volts_0to5)      channelType = "0-5 V";
        if(vResults[i] == AnalogIOChannelType::Volts_1to5)      channelType = "1-5 V";
        if(vResults[i] == AnalogIOChannelType::Current_0to20)   channelType = "0-20 mA";
        if(vResults[i] == AnalogIOChannelType::Current_4to20)   channelType = "4 to 20 mA";
        if(vResults[i] == AnalogIOChannelType::DirectValueCode) channelType = "DirectValueCode";

        ui->textEdit->append("Channel " + QString::number(i+1) + " Data Type: " + channelType);
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    dataTypeDialog * channelType = new dataTypeDialog(this);


    if(channelType->exec()==QDialog::Accepted)
    {

        bool bResult = m_AnalogInput->SetSingleChannelDataType(m_deviceAddress,0,channelType->GetDataType());

        responseHandler(bResult);

    }

    delete channelType;
}


void MainWindow::on_pushButton_4_clicked()
{
    dataTypeDialog * channelType = new dataTypeDialog(this);


    if(channelType->exec()==QDialog::Accepted)
    {

        bool bResult = m_AnalogInput->SetSingleChannelDataType(m_deviceAddress,1,channelType->GetDataType());

        responseHandler(bResult);

    }

}


void MainWindow::on_pushButton_5_clicked()
{
    dataTypeDialog * channelType = new dataTypeDialog(this);


    if(channelType->exec()==QDialog::Accepted)
    {

        bool bResult = m_AnalogInput->SetSingleChannelDataType(m_deviceAddress,2,channelType->GetDataType());

        responseHandler(bResult);

    }

}


void MainWindow::on_pushButton_6_clicked()
{
    dataTypeDialog * channelType = new dataTypeDialog(this);


    if(channelType->exec()==QDialog::Accepted)
    {

        bool bResult = m_AnalogInput->SetSingleChannelDataType(m_deviceAddress,3,channelType->GetDataType());

        responseHandler(bResult);

    }

}


void MainWindow::on_pushButton_7_clicked()
{
    dataTypeDialog * channelType = new dataTypeDialog(this);


    if(channelType->exec()==QDialog::Accepted)
    {

        bool bResult = m_AnalogInput->SetSingleChannelDataType(m_deviceAddress,4,channelType->GetDataType());

        responseHandler(bResult);

    }

}


void MainWindow::on_pushButton_8_clicked()
{
    dataTypeDialog * channelType = new dataTypeDialog(this);


    if(channelType->exec()==QDialog::Accepted)
    {

        bool bResult = m_AnalogInput->SetSingleChannelDataType(m_deviceAddress,5,channelType->GetDataType());

        responseHandler(bResult);

    }

}


void MainWindow::on_pushButton_9_clicked()
{
    dataTypeDialog * channelType = new dataTypeDialog(this);


    if(channelType->exec()==QDialog::Accepted)
    {

        bool bResult = m_AnalogInput->SetSingleChannelDataType(m_deviceAddress,6,channelType->GetDataType());

        responseHandler(bResult);

    }

}


void MainWindow::on_pushButton_10_clicked()
{
    dataTypeDialog * channelType = new dataTypeDialog(this);


    if(channelType->exec()==QDialog::Accepted)
    {

        bool bResult = m_AnalogInput->SetSingleChannelDataType(m_deviceAddress,7,channelType->GetDataType());

        responseHandler(bResult);

    }

}


void MainWindow::on_pushButton_11_clicked()
{
    dataTypeDialog * channelType = new dataTypeDialog(this);


    if(channelType->exec()==QDialog::Accepted)
    {

        std::vector<AnalogIOChannelType> vNewTypes;

        AnalogIOChannelType requestedType = channelType->GetDataType();

        for(int i=0;i<8;i++)
            vNewTypes.push_back(requestedType);

        bool bResult = m_AnalogInput->SetMultipleChannelDataType(m_deviceAddress,0,vNewTypes);

        responseHandler(bResult);

    }
}

