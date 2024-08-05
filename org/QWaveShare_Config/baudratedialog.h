#ifndef BAUDRATEDIALOG_H
#define BAUDRATEDIALOG_H

#include <QDialog>
#include "../QWaveshare/WS_Device.h"
#include<QSerialPort>

namespace Ui { class baudRateDialog; }

class baudRateDialog : public QDialog
{
   Q_OBJECT

public:
    explicit baudRateDialog(QWidget *parent = nullptr);
    ~baudRateDialog();

    QSerialPort::Parity GetParity(void);
    QSerialPort::BaudRate GetBaudRate(void);
    void SetParity(QSerialPort::Parity newParity);
    void SetBaudRate(QSerialPort::BaudRate);


private slots:
    void on_buttonBox_accepted();

private:
    Ui::baudRateDialog *ui;
};

#endif // BAUDRATEDIALOG_H
