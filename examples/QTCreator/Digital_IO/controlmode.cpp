#include "controlmode.h"
#include "ui_controlmode.h"

ControlMode::ControlMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlMode)
{
    ui->setupUi(this);


    for(int i = 0 ; i<8 ;i++)
        ui->comboBox->addItem(QString::number(i+1));

    ui->comboBox_2->addItem("Normal");
    ui->comboBox_2->addItem("Linkage");
    ui->comboBox_2->addItem("Flip");
}

unsigned int ControlMode::GetMode()
{
    return m_Mode;
}
unsigned int ControlMode::GetChannel()
{
    return m_Channel;
}

void ControlMode::AllChannels(bool allChannels)
{
    m_allChannels = allChannels;

    if(allChannels)
    {
        ui->comboBox->clear();
        ui->comboBox->addItem("ALL");
        ui->comboBox->setDisabled(true);
    }
}

ControlMode::~ControlMode()
{
    delete ui;
}

void ControlMode::on_comboBox_2_currentIndexChanged(int index)
{
    m_Mode = index;
}


void ControlMode::on_comboBox_currentIndexChanged(int index)
{
    m_Channel = index;
}

