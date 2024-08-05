#ifndef CONTROLMODE_H
#define CONTROLMODE_H

#include <QDialog>

namespace Ui {
class ControlMode;
}

class ControlMode : public QDialog
{
    Q_OBJECT

public:
    explicit ControlMode(QWidget *parent = nullptr);
    ~ControlMode();
    unsigned int GetMode(void);
    unsigned int GetChannel(void);

    void AllChannels(bool allChannels);
private slots:
    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::ControlMode *ui;


    bool m_allChannels;
    unsigned int m_Mode;
    unsigned int m_Channel;
};

#endif // CONTROLMODE_H
