#include "valuedialog.h"
#include "ui_valuedialog.h"

#include <QValidator>

valueDialog::valueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::valueDialog)
{
    ui->setupUi(this);

    QIntValidator * validator = new QIntValidator(0,32767,ui->lineEdit);
    ui->lineEdit->setValidator(validator);

    for(int i = 0 ; i<8 ;i++)
        ui->comboBox->addItem(QString::number(i+1));
}

valueDialog::~valueDialog()
{
    delete ui;
}


unsigned int valueDialog::GetValue()
{
    return m_iValue;
}
unsigned int valueDialog::GetChannel()
{
    return m_Channel;
}
void valueDialog::on_buttonBox_accepted()
{
   m_iValue = ui->lineEdit->text().toUInt();
   m_Channel = ui->comboBox->currentIndex();
}

