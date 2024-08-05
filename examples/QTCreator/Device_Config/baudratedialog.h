#ifndef BAUDRATEDIALOG_H
#define BAUDRATEDIALOG_H

#include <QDialog>
#include "WS_Device.h"
#include <libserialport.h>

namespace Ui { class baudRateDialog; }

class baudRateDialog : public QDialog
{
   Q_OBJECT

public:
    explicit baudRateDialog(QWidget *parent = nullptr);
    ~baudRateDialog();

    sp_parity GetParity(void);
    WSBaudRates GetBaudRate(void);
    void SetParity(sp_parity newParity);
    void SetBaudRate(WSBaudRates);


private slots:
    void on_buttonBox_accepted();

private:
    Ui::baudRateDialog *ui;
};

#endif // BAUDRATEDIALOG_H
