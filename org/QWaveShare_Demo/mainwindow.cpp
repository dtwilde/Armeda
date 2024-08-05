#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QDebug>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //find available serial ports and add to combbox
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        ui->comboBox->addItem(info.portName());
    }



    //populate device address combobox
    for (int i=1;i<256;i++)
        ui->comboBox_7->addItem(QString::number(i));

    //populate serial port baud rate combobox
    ui->comboBox_4->addItem("4800");
    ui->comboBox_4->addItem("9600");
    ui->comboBox_4->addItem("19200");
    ui->comboBox_4->addItem("38400");
    ui->comboBox_4->addItem("57600");
    ui->comboBox_4->addItem("115200");
    ui->comboBox_4->setCurrentIndex(1);

    //populate serail port parity combobox
    ui->comboBox_5->addItem("None");
    ui->comboBox_5->addItem("Even");
    ui->comboBox_5->addItem("Odd");

    ui->comboBox_6->addItem("Relay Board 8CH");
    ui->comboBox_6->addItem("Analog Input 8CH");
    ui->comboBox_6->addItem("Analog Output 8CH");
    ui->comboBox_6->addItem("Digital IO Board 8CH");
    ui->comboBox_6->setCurrentIndex(1);

    //configure serial port
    m_SerialPort.setPortName(ui->comboBox->currentText());
    m_SerialPort.setBaudRate(GetSelectedBaud());
    m_SerialPort.setParity(GetSelectedParity());


    //setup Relay board UI
    ui->comboBox_2->addItem("Relay 1");
    ui->comboBox_2->addItem("Relay 2");
    ui->comboBox_2->addItem("Relay 3");
    ui->comboBox_2->addItem("Relay 4");
    ui->comboBox_2->addItem("Relay 5");
    ui->comboBox_2->addItem("Relay 6");
    ui->comboBox_2->addItem("Relay 7");
    ui->comboBox_2->addItem("Relay 8");

    ui->comboBox_3->addItem("On");
    ui->comboBox_3->addItem("Off");

    ui->lineEdit->setValidator(new QIntValidator(0,1000,this));

    m_RelayBoard = new WS_RTURelay(8, m_SerialPortMutex,m_SerialPort,1000);
    m_AnalogInput = new WS_AnalogInput(m_SerialPortMutex,m_SerialPort,1000);

    UpdateRelayUI();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_RelayBoard;
    delete m_AnalogInput;
}


QSerialPort::Parity MainWindow::GetSelectedParity(void)
{

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

int MainWindow::GetDeviceAddress(void)
{
    int iReturn = 0;

    iReturn = ui->comboBox_7->currentText().toInt();

    return iReturn;
}

void MainWindow::UpdateRelayUI(void)
{
    QVector<RelayState> relayStates = m_RelayBoard->ReadStatesofRelays(GetDeviceAddress());

    if(relayStates.count()==8)
    {
        ui->checkBox->setChecked(relayStates[0]);
        ui->checkBox_2->setChecked(relayStates[1]);
        ui->checkBox_3->setChecked(relayStates[2]);
        ui->checkBox_4->setChecked(relayStates[3]);
        ui->checkBox_5->setChecked(relayStates[4]);
        ui->checkBox_6->setChecked(relayStates[5]);
        ui->checkBox_7->setChecked(relayStates[6]);
        ui->checkBox_8->setChecked(relayStates[7]);

        ui->checkBox_9->setChecked(relayStates[0]);
        ui->checkBox_10->setChecked(relayStates[1]);
        ui->checkBox_11->setChecked(relayStates[2]);
        ui->checkBox_12->setChecked(relayStates[3]);
        ui->checkBox_13->setChecked(relayStates[4]);
        ui->checkBox_14->setChecked(relayStates[5]);
        ui->checkBox_15->setChecked(relayStates[6]);
        ui->checkBox_16->setChecked(relayStates[7]);
    }
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    m_SerialPortMutex.lock();
    m_SerialPort.disconnect();
    m_SerialPort.setPortName(ui->comboBox->currentText());
    m_SerialPortMutex.unlock();
}


void MainWindow::on_pushButton_clicked()
{
    m_RelayBoard->ControlAllRelays(GetDeviceAddress(),RelayState::RelayOn);
    UpdateRelayUI();
}


void MainWindow::on_pushButton_2_clicked()
{
    m_RelayBoard->ControlAllRelays(GetDeviceAddress(),RelayState::RelayOff);
    UpdateRelayUI();
}


void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),0,RelayState::RelayOn);
    else
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),0,RelayState::RelayOff);

    UpdateRelayUI();
}


void MainWindow::on_checkBox_2_clicked()
{
    if(ui->checkBox_2->isChecked())
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),1,RelayState::RelayOn);
    else
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),1,RelayState::RelayOff);
    UpdateRelayUI();
}


void MainWindow::on_checkBox_3_clicked()
{
    if(ui->checkBox_3->isChecked())
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),2,RelayState::RelayOn);
    else
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),2,RelayState::RelayOff);
    UpdateRelayUI();
}


void MainWindow::on_checkBox_4_clicked()
{
    if(ui->checkBox_4->isChecked())
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),3,RelayState::RelayOn);
    else
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),3,RelayState::RelayOff);
    UpdateRelayUI();
}


void MainWindow::on_checkBox_5_clicked()
{
    if(ui->checkBox_5->isChecked())
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),4,RelayState::RelayOn);
    else
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),4,RelayState::RelayOff);
    UpdateRelayUI();
}


void MainWindow::on_checkBox_6_clicked()
{
    if(ui->checkBox_6->isChecked())
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),5,RelayState::RelayOn);
    else
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),5,RelayState::RelayOff);
    UpdateRelayUI();
}


void MainWindow::on_checkBox_7_clicked()
{
    if(ui->checkBox_7->isChecked())
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),6,RelayState::RelayOn);
    else
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),6,RelayState::RelayOff);
    UpdateRelayUI();
}


void MainWindow::on_checkBox_8_clicked()
{
    if(ui->checkBox_8->isChecked())
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),7,RelayState::RelayOn);
    else
        m_RelayBoard->ControlSingleRelay(GetDeviceAddress(),7,RelayState::RelayOff);
    UpdateRelayUI();
}


void MainWindow::on_pushButton_3_clicked()
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

    m_RelayBoard->WriteStatesofRelays(GetDeviceAddress(),iRelayState);

    UpdateRelayUI();

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

    m_RelayBoard->RelayFlashOnOff(GetDeviceAddress(),iRelay,iInterval,bOn);

}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    m_SerialPortMutex.lock();
    m_SerialPort.setPortName(ui->comboBox->currentText());
    m_SerialPortMutex.unlock();
}


void MainWindow::on_comboBox_4_currentIndexChanged(int index)
{
    m_SerialPortMutex.lock();
    m_SerialPort.setBaudRate(GetSelectedBaud());
    m_SerialPortMutex.unlock();
}


void MainWindow::on_comboBox_5_currentIndexChanged(int index)
{
     m_SerialPortMutex.lock();
     m_SerialPort.setParity(GetSelectedParity());
     m_SerialPortMutex.unlock();
}


void MainWindow::on_comboBox_6_currentIndexChanged(int index)
{
            ui->stackedWidget->setCurrentIndex(index);

}

/*
 * UI Code for 8 Channel Analog Input
 *
*/

void MainWindow::on_pushButton_5_clicked()
{

    QString szResult = "";


    QVector <float> fResult;

    bool bResult = m_AnalogInput->ReadAnalogInput(1,0,8,fResult);

    if(fResult.size()==8)
    {
        ui->lineEdit_2->setText(QString::number(fResult[0]));
        ui->lineEdit_3->setText(QString::number(fResult[1]));
        ui->lineEdit_4->setText(QString::number(fResult[2]));
        ui->lineEdit_5->setText(QString::number(fResult[3]));
        ui->lineEdit_6->setText(QString::number(fResult[4]));
        ui->lineEdit_7->setText(QString::number(fResult[5]));
        ui->lineEdit_8->setText(QString::number(fResult[6]));
        ui->lineEdit_9->setText(QString::number(fResult[7]));
    }
}

