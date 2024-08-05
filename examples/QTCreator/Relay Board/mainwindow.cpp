#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QString>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_deviceAddress = 2;

    ui->comboBox->addItem("");

    std::vector<std::string> availPorts = m_sPort.EnumeratePorts();

    for (int i = 0; i<availPorts.size(); i++)
    {
        ui->comboBox->addItem(QString::fromStdString(availPorts[i]));
    }

    ui->comboBox_3->addItem("On");
    ui->comboBox_3->addItem("Off");

    ui->lineEdit->setValidator(new QIntValidator(0,100,this));

    for(int i = 0; i<8 ;i++)
        ui->comboBox_2->addItem(QString::number((i+1)));

    //setup the relay board class for a 8 channel relay board
    m_RelayBoard = new WS_RTURelay(&m_sPort);
}

MainWindow::~MainWindow()
{
    m_sPort.ClosePort();

    delete m_RelayBoard;
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

    m_RelayBoard->GetLastTX(lastTx,&sizeofTx);
    m_RelayBoard->GetLastRX(lastRx,&sizeofRx);

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
        QString qError = "Error:" + QString::fromStdString(m_RelayBoard->GetLastError());

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
    std::vector<RelayState> vResponse = m_RelayBoard->ReadStatesofRelays(m_deviceAddress, RTUChannelSize::Channel_8);

    //check to see if we got 8 relay states for 8 channel board
    if(vResponse.size()==8)
    {
        ui->checkBox->setChecked(vResponse[0]==RelayState::RelayOn ? true : false);
        ui->checkBox_2->setChecked(vResponse[1]==RelayState::RelayOn ? true : false);
        ui->checkBox_3->setChecked(vResponse[2]==RelayState::RelayOn ? true : false);
        ui->checkBox_4->setChecked(vResponse[3]==RelayState::RelayOn ? true : false);
        ui->checkBox_5->setChecked(vResponse[4]==RelayState::RelayOn ? true : false);
        ui->checkBox_6->setChecked(vResponse[5]==RelayState::RelayOn ? true : false);
        ui->checkBox_7->setChecked(vResponse[6]==RelayState::RelayOn ? true : false);
        ui->checkBox_8->setChecked(vResponse[7]==RelayState::RelayOn ? true : false);

        ui->checkBox_9->setChecked(vResponse[0]==RelayState::RelayOn ? true : false);
        ui->checkBox_10->setChecked(vResponse[1]==RelayState::RelayOn ? true : false);
        ui->checkBox_11->setChecked(vResponse[2]==RelayState::RelayOn ? true : false);
        ui->checkBox_12->setChecked(vResponse[3]==RelayState::RelayOn ? true : false);
        ui->checkBox_13->setChecked(vResponse[4]==RelayState::RelayOn ? true : false);
        ui->checkBox_14->setChecked(vResponse[5]==RelayState::RelayOn ? true : false);
        ui->checkBox_15->setChecked(vResponse[6]==RelayState::RelayOn ? true : false);
        ui->checkBox_16->setChecked(vResponse[7]==RelayState::RelayOn ? true : false);
    }

    responseHandler(vResponse.size());
}




void MainWindow::on_checkBox_clicked()
{
    //turn on or off Relay1
    bool bResult = m_RelayBoard->ControlSingleRelay(m_deviceAddress,
                                     0,
                                     (ui->checkBox->isChecked()) ? RelayOn : RelayOff);

    responseHandler(bResult);

}


void MainWindow::on_checkBox_2_clicked()
{
    //turn on or off Relay2
    bool bResult = m_RelayBoard->ControlSingleRelay(m_deviceAddress,
                                    1,
                                    (ui->checkBox_2->isChecked()) ? RelayOn : RelayOff);
    responseHandler(bResult);
}


void MainWindow::on_checkBox_3_clicked()
{
    //turn on or off Relay3
    bool bResult = m_RelayBoard->ControlSingleRelay(m_deviceAddress,
                                    2,
                                    (ui->checkBox_3->isChecked()) ? RelayOn : RelayOff);
    responseHandler(bResult);
}

void MainWindow::on_checkBox_4_clicked()
{
    //turn on or off Relay4
    bool bResult = m_RelayBoard->ControlSingleRelay(m_deviceAddress,
                                    3,
                                    (ui->checkBox_4->isChecked()) ? RelayOn : RelayOff);
    responseHandler(bResult);
}

void MainWindow::on_checkBox_5_clicked()
{
    //turn on or off Relay5
    bool bResult = m_RelayBoard->ControlSingleRelay(m_deviceAddress,
                                    4,
                                    (ui->checkBox_5->isChecked()) ? RelayOn : RelayOff);
    responseHandler(bResult);
}


void MainWindow::on_checkBox_6_clicked()
{
    //turn on or off Relay6
    bool bResult = m_RelayBoard->ControlSingleRelay(m_deviceAddress,
                                    5,
                                    (ui->checkBox_6->isChecked()) ? RelayOn : RelayOff);
    responseHandler(bResult);
}


void MainWindow::on_checkBox_7_clicked()
{
    //turn on or off Relay7
    bool bResult = m_RelayBoard->ControlSingleRelay(m_deviceAddress,
                                    6,
                                    (ui->checkBox_7->isChecked()) ? RelayOn : RelayOff);
    responseHandler(bResult);
}


void MainWindow::on_checkBox_8_clicked()
{
    //turn on or off Relay8
    bool bResult = m_RelayBoard->ControlSingleRelay(m_deviceAddress,
                                    7,
                                    (ui->checkBox_8->isChecked()) ? RelayOn : RelayOff);
    responseHandler(bResult);
}


void MainWindow::on_pushButton_3_clicked()
{
    on_pushButton_clicked();
}


void MainWindow::on_pushButton_2_clicked()
{
    int iRelayState = 0;
\
    if(ui->checkBox_9->isChecked())
        iRelayState = iRelayState | 0b00000001;
    if(ui->checkBox_10->isChecked())
        iRelayState = iRelayState | 0b00000010;
    if(ui->checkBox_11->isChecked())
        iRelayState = iRelayState | 0b00000100;
    if(ui->checkBox_12->isChecked())
        iRelayState = iRelayState | 0b00001000;
    if(ui->checkBox_13->isChecked())
        iRelayState = iRelayState | 0b00010000;
    if(ui->checkBox_14->isChecked())
        iRelayState = iRelayState | 0b00100000;
    if(ui->checkBox_15->isChecked())
        iRelayState = iRelayState | 0b01000000;
    if(ui->checkBox_16->isChecked())
        iRelayState = iRelayState | 0b10000000;

    bool bResult = false;

    bResult = m_RelayBoard->WriteStatesofRelays(m_deviceAddress, RTUChannelSize::Channel_8, iRelayState);

    responseHandler(bResult);
}


void MainWindow::on_pushButton_4_clicked()
{
    int iRelay = 0;
    int iInterval = 0;


    bool bOn = false;

    if(ui->lineEdit->text()=="") ui->lineEdit->setText("10");

    iRelay = ui->comboBox_2->currentIndex();
    iInterval = ui->lineEdit->text().toInt();

    if(ui->comboBox_3->currentIndex()==0) bOn = true; else bOn = false;

    bool bResult = false;

    bResult = m_RelayBoard->RelayFlashOnOff(m_deviceAddress,iRelay,iInterval,bOn);

    responseHandler(bResult);
}


void MainWindow::on_pushButton_5_clicked()
{
    bool bResult = false;

    bResult = m_RelayBoard->ControlAllRelays(m_deviceAddress,RelayState::RelayOn);

    responseHandler(bResult);
}


void MainWindow::on_pushButton_6_clicked()
{
    bool bResult = false;

    bResult = m_RelayBoard->ControlAllRelays(m_deviceAddress,RelayState::RelayOff);
    \
    responseHandler(bResult);
}


void MainWindow::on_pushButton_7_clicked()
{
    bool bResult = false;

    bResult = m_RelayBoard->ControlAllRelays(m_deviceAddress,RelayState::RelayFlip);

    responseHandler(bResult);
}

