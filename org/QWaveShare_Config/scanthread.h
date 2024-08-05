#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSerialPort>
#include "../QWaveshare/WS_Device.h"

class ScanThread : public QThread
{
    Q_OBJECT

public:
    explicit ScanThread(QObject *parent, WS_Device * configParent);
    ~ScanThread();

    void beginScan(int iStartRange, int iEndRange);

    void stopScan(void);


signals:
    void deviceDiscovered(int iAddress);
    void scanComplete();

private:
    void run() override;

    bool m_stopScan;

    WS_Device * m_Config;

    int m_iStartRange;
    int m_iEndRange;
};

#endif // SCANTHREAD_H
