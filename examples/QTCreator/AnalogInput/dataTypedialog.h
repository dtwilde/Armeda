#ifndef dataTypeDIALOG_H
#define dataTypeDIALOG_H

#include <QDialog>
#include "WS_Device.h"
#include "WS_AnalogInput.h"

namespace Ui { class dataTypeDialog; }

class dataTypeDialog : public QDialog
{
   Q_OBJECT

public:
    explicit dataTypeDialog(QWidget *parent = nullptr);
    ~dataTypeDialog();

    AnalogIOChannelType GetDataType(void);


private slots:
    void on_buttonBox_accepted();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::dataTypeDialog *ui;

    AnalogIOChannelType m_ctReturn;

};

#endif // dataTypeDIALOG_H
