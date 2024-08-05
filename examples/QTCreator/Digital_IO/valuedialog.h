#ifndef VALUEDIALOG_H
#define VALUEDIALOG_H

#include <QDialog>

namespace Ui {
class valueDialog;
}

class valueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit valueDialog(QWidget *parent = nullptr);
    ~valueDialog();


    unsigned int GetValue();
    unsigned int GetChannel();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::valueDialog *ui;

    unsigned int m_iValue;
    unsigned int m_Channel;


};

#endif // VALUEDIALOG_H
