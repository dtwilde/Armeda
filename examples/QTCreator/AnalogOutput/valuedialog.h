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

private slots:
    void on_buttonBox_accepted();

private:
    Ui::valueDialog *ui;

    unsigned int m_iValue;


};

#endif // VALUEDIALOG_H
