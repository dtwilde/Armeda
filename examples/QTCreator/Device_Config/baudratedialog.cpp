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


void baudRateDialog::SetParity(sp_parity newParity)
{
         if(newParity==sp_parity::SP_PARITY_NONE)     ui->comboBox_2->setCurrentIndex(0);
    else if(newParity==sp_parity::SP_PARITY_EVEN)   ui->comboBox_2->setCurrentIndex(1);
    else if(newParity==sp_parity::SP_PARITY_ODD)    ui->comboBox_2->setCurrentIndex(2);

}
void baudRateDialog::SetBaudRate(WSBaudRates newBaudRate)
{
         if(newBaudRate==WSBaudRates::Baud4800)   ui->comboBox->setCurrentIndex(0);
    else if(newBaudRate==WSBaudRates::Baud9600)   ui->comboBox->setCurrentIndex(1);
    else if(newBaudRate==WSBaudRates::Baud19200)  ui->comboBox->setCurrentIndex(2);
    else if(newBaudRate==WSBaudRates::Baud38400)  ui->comboBox->setCurrentIndex(3);
    else if(newBaudRate==WSBaudRates::Baud57600)  ui->comboBox->setCurrentIndex(4);
    else if(newBaudRate==WSBaudRates::Baud115200) ui->comboBox->setCurrentIndex(5);
}

sp_parity baudRateDialog::GetParity(void)
{
    sp_parity pReturn = sp_parity::SP_PARITY_NONE;

    QString sParity = ui->comboBox_2->currentText();

    if(sParity=="Odd")  pReturn  = sp_parity::SP_PARITY_ODD;
    if(sParity=="Even") pReturn  = sp_parity::SP_PARITY_EVEN;
    if(sParity=="None") pReturn  = sp_parity::SP_PARITY_NONE;

    return pReturn;

}
WSBaudRates baudRateDialog::GetBaudRate(void)
{
    WSBaudRates brReturn = WSBaudRates::Baud9600;

    int iReturn = ui->comboBox->currentText().toInt();

    if(iReturn == 4800 )   brReturn = WSBaudRates::Baud4800;
    if(iReturn == 9600 )   brReturn = WSBaudRates::Baud9600;
    if(iReturn == 19200 )  brReturn = WSBaudRates::Baud19200;
    if(iReturn == 38400 )  brReturn = WSBaudRates::Baud38400;
    if(iReturn == 57600 )  brReturn = WSBaudRates::Baud57600;
    if(iReturn == 115200 ) brReturn = WSBaudRates::Baud115200;


    return brReturn;
}
