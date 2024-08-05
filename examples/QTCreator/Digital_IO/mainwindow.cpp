#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QString>
#include <QDebug>
#include "valuedialog.h"
#include "controlmode.h"
#include <QRandomGenerator>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_deviceAddress = 1;

    ui->comboBox->addItem("");

    std::vector<std::string> availPorts = m_sPort.EnumeratePorts();

    for (int i = 0; i<availPorts.size(); i++)
    {
        ui->comboBox->addItem(QString::fromStdString(availPorts[i]));
    }

   m_DigitalIO = new WS_Digital_IO(&m_sPort);

   ui->checkBox_9->setAttribute(Qt::WA_TransparentForMouseEvents);
   ui->checkBox_9->setFocusPolicy(Qt::NoFocus);
   ui->checkBox_10->setAttribute(Qt::WA_TransparentForMouseEvents);
   ui->checkBox_10->setFocusPolicy(Qt::NoFocus);
   ui->checkBox_11->setAttribute(Qt::WA_TransparentForMouseEvents);
   ui->checkBox_11->setFocusPolicy(Qt::NoFocus);
   ui->checkBox_12->setAttribute(Qt::WA_TransparentForMouseEvents);
   ui->checkBox_12->setFocusPolicy(Qt::NoFocus);
   ui->checkBox_13->setAttribute(Qt::WA_TransparentForMouseEvents);
   ui->checkBox_13->setFocusPolicy(Qt::NoFocus);
   ui->checkBox_14->setAttribute(Qt::WA_TransparentForMouseEvents);
   ui->checkBox_14->setFocusPolicy(Qt::NoFocus);
   ui->checkBox_15->setAttribute(Qt::WA_TransparentForMouseEvents);
   ui->checkBox_15->setFocusPolicy(Qt::NoFocus);
   ui->checkBox_16->setAttribute(Qt::WA_TransparentForMouseEvents);
   ui->checkBox_16->setFocusPolicy(Qt::NoFocus);
}

MainWindow::~MainWindow()
{
    m_sPort.ClosePort();

    delete m_DigitalIO;
    delete ui;
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //free up the last serial port opened
    m_sPort.ClosePort();

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

    m_DigitalIO->GetLastTX(lastTx,&sizeofTx);
    m_DigitalIO->GetLastRX(lastRx,&sizeofRx);

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
        QString qError = "Error:" + QString::fromStdString(m_DigitalIO->GetLastError());

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
    std::vector<bool> vResults;

    bool bResult = m_DigitalIO->ReadOutputChannelStatus(m_deviceAddress,vResults);

    responseHandler(bResult);

    if(vResults.size()==8)
    {
        ui->checkBox->setChecked(vResults[0]);
        ui->checkBox_2->setChecked(vResults[1]);
        ui->checkBox_3->setChecked(vResults[2]);
        ui->checkBox_4->setChecked(vResults[3]);
        ui->checkBox_5->setChecked(vResults[4]);
        ui->checkBox_6->setChecked(vResults[5]);
        ui->checkBox_7->setChecked(vResults[6]);
        ui->checkBox_8->setChecked(vResults[7]);
    }

}



void MainWindow::on_pushButton_4_clicked()
{

    bool bResult = m_DigitalIO->AllOutputChannelControl(m_deviceAddress,DigitalIO_State::ON);

    responseHandler(bResult);
}


void MainWindow::on_pushButton_3_clicked()
{
    bool bResult = m_DigitalIO->AllOutputChannelControl(m_deviceAddress,DigitalIO_State::OFF);

    responseHandler(bResult);
}


void MainWindow::on_checkBox_clicked()
{
    bool bResult = false;

    if(ui->checkBox->isChecked())
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x00,DigitalIO_State::ON);
    else
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x00,DigitalIO_State::OFF);

    responseHandler(bResult);
}


void MainWindow::on_checkBox_2_clicked()
{
    bool bResult = false;

    if(ui->checkBox_2->isChecked())
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x01,DigitalIO_State::ON);
    else
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x01,DigitalIO_State::OFF);

    responseHandler(bResult);
}


void MainWindow::on_checkBox_3_clicked()
{
    bool bResult = false;

    if(ui->checkBox_3->isChecked())
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x02,DigitalIO_State::ON);
    else
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x02,DigitalIO_State::OFF);

    responseHandler(bResult);

}


void MainWindow::on_checkBox_4_clicked()
{
    bool bResult = false;

    if(ui->checkBox_4->isChecked())
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x03,DigitalIO_State::ON);
    else
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x03,DigitalIO_State::OFF);

    responseHandler(bResult);

}


void MainWindow::on_checkBox_5_clicked()
{
    bool bResult = false;

    if(ui->checkBox_5->isChecked())
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x04,DigitalIO_State::ON);
    else
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x04,DigitalIO_State::OFF);

    responseHandler(bResult);

}


void MainWindow::on_checkBox_6_clicked()
{
    bool bResult = false;

    if(ui->checkBox_6->isChecked())
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x05,DigitalIO_State::ON);
    else
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x05,DigitalIO_State::OFF);

    responseHandler(bResult);

}


void MainWindow::on_checkBox_7_clicked()
{
    bool bResult = false;

    if(ui->checkBox_7->isChecked())
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x06,DigitalIO_State::ON);
    else
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x06,DigitalIO_State::OFF);

    responseHandler(bResult);

}


void MainWindow::on_checkBox_8_clicked()
{
    bool bResult = false;

    if(ui->checkBox_8->isChecked())
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x07,DigitalIO_State::ON);
    else
        bResult = m_DigitalIO->ControlSingleOuputChannel(m_deviceAddress,0x07,DigitalIO_State::OFF);

    responseHandler(bResult);

}


void MainWindow::on_pushButton_6_clicked()
{
    bool bResult = false;

    std::vector<bool> bStatus;

    for(int i=0;i<8;i++)
    {
        bStatus.push_back(QRandomGenerator::global()->bounded(2)==0);
    }

    bResult = m_DigitalIO->WriteOutputChannelStatus(m_deviceAddress,bStatus);

    responseHandler(bResult);
}


void MainWindow::on_pushButton_5_clicked()
{
    valueDialog * channelType = new valueDialog(this);

    if(channelType->exec()==QDialog::Accepted)
    {

        int iVal = channelType->GetValue();
        unsigned char channel = channelType->GetChannel();

        bool bResult = m_DigitalIO->OutputChannelFlashOnOff(m_deviceAddress,DigitalIO_Command::FlashOn,channel,iVal);

        responseHandler(bResult);

    }

    delete channelType;
}


void MainWindow::on_pushButton_11_clicked()
{
    std::vector<bool> channelStatus;

    bool bResult = m_DigitalIO->ReadInputChannelStatus(m_deviceAddress,channelStatus);
    responseHandler(bResult);

    if(channelStatus.size()==8)
    {
        ui->checkBox_9->setChecked(channelStatus[0]);
        ui->checkBox_10->setChecked(channelStatus[1]);
        ui->checkBox_11->setChecked(channelStatus[2]);
        ui->checkBox_12->setChecked(channelStatus[3]);
        ui->checkBox_13->setChecked(channelStatus[4]);
        ui->checkBox_14->setChecked(channelStatus[5]);
        ui->checkBox_15->setChecked(channelStatus[6]);
        ui->checkBox_16->setChecked(channelStatus[7]);
    }
}


void MainWindow::on_pushButton_12_clicked()
{
    std::vector<Digital_IO_ControlMode> channelStatus;

    bool bResult = m_DigitalIO->ReadOutputChannelControlMode(m_deviceAddress,0,8,channelStatus);
    responseHandler(bResult);

    for(int i=0;i<channelStatus.size();i++)
    {
        QString szMode;

        switch(channelStatus[i])
        {
            case Digital_IO_ControlMode::Normal:
                szMode = "Normal";
            break;
            case Digital_IO_ControlMode::Linkage:
                szMode = "Linkage";
            break;
            case Digital_IO_ControlMode::Flip:
                szMode = "Flip";
            break;
        }

        ui->textEdit->append("Channel " + QString::number(i+1) + " control mode " + szMode);
    }
}


void MainWindow::on_pushButton_13_clicked()
{
    ControlMode * modeType = new ControlMode(this);

    if(modeType->exec()==QDialog::Accepted)
    {

        unsigned char mode = modeType->GetMode();
        unsigned char channel = modeType->GetChannel();

        bool bResult = m_DigitalIO->SetSingleOutputChannelControlMode(m_deviceAddress,channel,(Digital_IO_ControlMode)mode);

        responseHandler(bResult);

    }

    delete modeType;

}


void MainWindow::on_pushButton_14_clicked()
{
    ControlMode * modeType = new ControlMode(this);

    modeType->AllChannels(true);

    if(modeType->exec()==QDialog::Accepted)
    {

        unsigned char mode = modeType->GetMode();


        std::vector<Digital_IO_ControlMode> cModes;

        for(int i=0;i<8;i++)
            cModes.push_back((Digital_IO_ControlMode)mode);

        bool bResult = m_DigitalIO->SetMultipleOutputChannelControlMode(m_deviceAddress,0,cModes);

        responseHandler(bResult);

    }

    delete modeType;
}

