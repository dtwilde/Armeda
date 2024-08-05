#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QString>
#include <QDebug>
#include "valuedialog.h"


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

    m_AnalogOutput = new WS_AnalogOutput(&m_sPort);
}

MainWindow::~MainWindow()
{
    m_sPort.ClosePort();

    delete m_AnalogOutput;

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

    m_AnalogOutput->GetLastTX(lastTx,&sizeofTx);
    m_AnalogOutput->GetLastRX(lastRx,&sizeofRx);

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
        QString qError = "Error:" + QString::fromStdString(m_AnalogOutput->GetLastError());

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


void MainWindow::on_pushButton_2_clicked()
{
    std::vector<unsigned int> vResults;

    bool bResult = m_AnalogOutput->ReadChannelOutput(m_deviceAddress,0,8,vResults);

    responseHandler(bResult);

    for(int i=0; i<vResults.size();i++)
    {
        ui->textEdit->append("Channel " + QString::number(i+1) + " Value : " + QString::number(vResults[i]));
    }

    if(vResults.size()==8)
    {
        ui->lineEdit_1->setText(QString::number(vResults[0]));
        ui->lineEdit_2->setText(QString::number(vResults[1]));
        ui->lineEdit_3->setText(QString::number(vResults[2]));
        ui->lineEdit_4->setText(QString::number(vResults[3]));
        ui->lineEdit_5->setText(QString::number(vResults[4]));
        ui->lineEdit_6->setText(QString::number(vResults[5]));
        ui->lineEdit_7->setText(QString::number(vResults[6]));
        ui->lineEdit_8->setText(QString::number(vResults[7]));
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    valueDialog * channelType = new valueDialog(this);

    if(channelType->exec()==QDialog::Accepted)
    {
        int iVal = channelType->GetValue();

        bool bResult = m_AnalogOutput->SetSingleChannelOutput(m_deviceAddress,0,iVal);

        responseHandler(bResult);

        if(bResult) ui->lineEdit_1->setText(QString::number(iVal));
    }

    delete channelType;
}


void MainWindow::on_pushButton_4_clicked()
{
    valueDialog * channelType = new valueDialog(this);

    if(channelType->exec()==QDialog::Accepted)
    {

        int iVal = channelType->GetValue();

        bool bResult = m_AnalogOutput->SetSingleChannelOutput(m_deviceAddress,1,iVal);

        responseHandler(bResult);

        if(bResult) ui->lineEdit_2->setText(QString::number(iVal));
    }

    delete channelType;
}


void MainWindow::on_pushButton_5_clicked()
{
    valueDialog * channelType = new valueDialog(this);

    if(channelType->exec()==QDialog::Accepted)
    {

        int iVal = channelType->GetValue();

        bool bResult = m_AnalogOutput->SetSingleChannelOutput(m_deviceAddress,2,iVal);

        responseHandler(bResult);

        if(bResult) ui->lineEdit_3->setText(QString::number(iVal));
    }

    delete channelType;
}


void MainWindow::on_pushButton_6_clicked()
{
    valueDialog * channelType = new valueDialog(this);

    if(channelType->exec()==QDialog::Accepted)
    {

        int iVal = channelType->GetValue();

        bool bResult = m_AnalogOutput->SetSingleChannelOutput(m_deviceAddress,3,iVal);

        responseHandler(bResult);

        if(bResult) ui->lineEdit_4->setText(QString::number(iVal));
    }

    delete channelType;
}


void MainWindow::on_pushButton_7_clicked()
{
    valueDialog * channelType = new valueDialog(this);

    if(channelType->exec()==QDialog::Accepted)
    {

        int iVal = channelType->GetValue();

        bool bResult = m_AnalogOutput->SetSingleChannelOutput(m_deviceAddress,4,iVal);

        responseHandler(bResult);

        if(bResult) ui->lineEdit_5->setText(QString::number(iVal));
    }

    delete channelType;
}


void MainWindow::on_pushButton_8_clicked()
{
    valueDialog * channelType = new valueDialog(this);

    if(channelType->exec()==QDialog::Accepted)
    {

        int iVal = channelType->GetValue();

        bool bResult = m_AnalogOutput->SetSingleChannelOutput(m_deviceAddress,5,iVal);

        responseHandler(bResult);

        if(bResult) ui->lineEdit_6->setText(QString::number(iVal));
    }

    delete channelType;
}


void MainWindow::on_pushButton_9_clicked()
{
    valueDialog * channelType = new valueDialog(this);

    if(channelType->exec()==QDialog::Accepted)
    {

        int iVal = channelType->GetValue();

        bool bResult = m_AnalogOutput->SetSingleChannelOutput(m_deviceAddress,6,iVal);

        responseHandler(bResult);

        if(bResult) ui->lineEdit_7->setText(QString::number(iVal));
    }

    delete channelType;
}


void MainWindow::on_pushButton_10_clicked()
{
    valueDialog * channelType = new valueDialog(this);

    if(channelType->exec()==QDialog::Accepted)
    {

        int iVal = channelType->GetValue();

        bool bResult = m_AnalogOutput->SetSingleChannelOutput(m_deviceAddress,7,iVal);

        responseHandler(bResult);

        if(bResult) ui->lineEdit_8->setText(QString::number(iVal));
    }

    delete channelType;
}


void MainWindow::on_pushButton_11_clicked()
{
    valueDialog * vDialog = new valueDialog(this);


    if(vDialog->exec()==QDialog::Accepted)
    {

        std::vector<unsigned int> vNewValues;

        unsigned int requestedValue = vDialog->GetValue();

        for(int i=0;i<8;i++)
            vNewValues.push_back(requestedValue);

        bool bResult = m_AnalogOutput->SetMultipleChannelOutput(m_deviceAddress,0,vNewValues);

        responseHandler(bResult);

    }
}

