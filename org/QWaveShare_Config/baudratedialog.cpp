#include "baudratedialog.h"
#include "ui_baudratedialog.h"
#include <QDebug>

baudRateDialog::baudRateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::baudRateDialog)
{
    ui->setupUi(this);

    ui->comboBox->addItem("4800");
    ui->comboBox->addItem("9600");
    ui->comboBox->addItem("19200");
    ui->comboBox->addItem("38400");
    ui->comboBox->addItem("57600");
    ui->comboBox->addItem("115200");


    ui->comboBox_2->addItem("None");
    ui->comboBox_2->addItem("Even");
    ui->comboBox_2->addItem("Odd");
}

baudRateDialog::~baudRateDialog()
{
    delete ui;
}

void baudRateDialog::on_buttonBox_accepted()
{

}


void baudRateDialog::SetParity(QSerialPort::Parity newParity)
{
         if(newParity==QSerialPort::NoParity)     ui->comboBox_2->setCurrentIndex(0);
    else if(newParity==QSerialPort::EvenParity)   ui->comboBox_2->setCurrentIndex(1);
    else if(newParity==QSerialPort::OddParity)    ui->comboBox_2->setCurrentIndex(2);

}
void baudRateDialog::SetBaudRate(QSerialPort::BaudRate newBaudRate)
{
         if(newBaudRate==QSerialPort::Baud4800)   ui->comboBox->setCurrentIndex(0);
    else if(newBaudRate==QSerialPort::Baud9600)   ui->comboBox->setCurrentIndex(1);
    else if(newBaudRate==QSerialPort::Baud19200)  ui->comboBox->setCurrentIndex(2);
    else if(newBaudRate==QSerialPort::Baud38400)  ui->comboBox->setCurrentIndex(3);
    else if(newBaudRate==QSerialPort::Baud57600)  ui->comboBox->setCurrentIndex(4);
    else if(newBaudRate==QSerialPort::Baud115200) ui->comboBox->setCurrentIndex(5);
}

QSerialPort::Parity baudRateDialog::GetParity(void)
{
    QSerialPort::Parity pReturn = QSerialPort::NoParity;

    QString sParity = ui->comboBox_2->currentText();

    if(sParity=="Odd")  pReturn  = QSerialPort::OddParity;
    if(sParity=="Even") pReturn  = QSerialPort::EvenParity;
    if(sParity=="None") pReturn  = QSerialPort::NoParity;

    return pReturn;

}
QSerialPort::BaudRate baudRateDialog::GetBaudRate(void)
{
    QSerialPort::BaudRate brReturn = QSerialPort::Baud9600;

    int iReturn = ui->comboBox->currentText().toInt();

    if(iReturn == 4800 )   brReturn = QSerialPort::Baud4800;
    if(iReturn == 9600 )   brReturn = QSerialPort::Baud9600;
    if(iReturn == 19200 )  brReturn = QSerialPort::Baud19200;
    if(iReturn == 38400 )  brReturn = QSerialPort::Baud38400;
    if(iReturn == 57600 )  brReturn = QSerialPort::Baud57600;
    if(iReturn == 115200 ) brReturn = QSerialPort::Baud115200;


    return brReturn;
}
