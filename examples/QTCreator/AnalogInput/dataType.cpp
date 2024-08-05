#include "dataTypedialog.h"
#include "ui_dataTypedialog.h"
#include <QDebug>
#include "WS_AnalogInput.h"


dataTypeDialog::dataTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dataTypeDialog)
{
    ui->setupUi(this);

    ui->comboBox->addItem("");
    ui->comboBox->addItem("Volts 0-5");
    ui->comboBox->addItem("Volts 1-5");
    ui->comboBox->addItem("Current 0-20");
    ui->comboBox->addItem("Current 4-20");
    ui->comboBox->addItem("Direct Value Code");
}

dataTypeDialog::~dataTypeDialog()
{
    delete ui;
}


void dataTypeDialog::on_comboBox_currentIndexChanged(int index)
{
    if(index==1) m_ctReturn = AnalogIOChannelType::Volts_0to5;
    if(index==2) m_ctReturn = AnalogIOChannelType::Volts_1to5;
    if(index==3) m_ctReturn = AnalogIOChannelType::Current_0to20;
    if(index==4) m_ctReturn = AnalogIOChannelType::Current_4to20;
    if(index==5) m_ctReturn = AnalogIOChannelType::DirectValueCode;
}
void dataTypeDialog::on_buttonBox_accepted()
{

}


AnalogIOChannelType dataTypeDialog::GetDataType(void)
{


    return m_ctReturn;
}
