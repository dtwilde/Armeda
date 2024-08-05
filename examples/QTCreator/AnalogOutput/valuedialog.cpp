#include "valuedialog.h"
#include "ui_valuedialog.h"

#include <QValidator>

valueDialog::valueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::valueDialog)
{
    ui->setupUi(this);

    QIntValidator * validator = new QIntValidator(0,10000,ui->lineEdit);
    ui->lineEdit->setValidator(validator);
}

valueDialog::~valueDialog()
{
    delete ui;
}


unsigned int valueDialog::GetValue()
{
    return m_iValue;
}
void valueDialog::on_buttonBox_accepted()
{
    m_iValue = ui->lineEdit->text().toUInt();
}

