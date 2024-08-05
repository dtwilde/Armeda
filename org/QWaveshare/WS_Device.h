
#ifndef WS_Device_h
#define WS_Device_h

#include <QVector>
#include <QMutex>
#include <QSerialPort>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>


/* TODO

-Verify when reading responses that your not accessing indexes out of range in the QByteResponse

-Find a better way to compare QByteArrays

 */

enum MessageType
{
    Info  = 0,
    Debug = 1,
    Error  = 2,
    RxTx  = 3,
};

class WS_Device : public QObject
{
Q_OBJECT

public:

    WS_Device(QMutex &mSerialPortMutex, QSerialPort &sPort, int iWaitTimeout);

    QString GetLastError(void);

    bool SetBaudRate(int iDevice, QSerialPort::BaudRate baudRate, QSerialPort::Parity portParity);

    bool ReadDeviceAddress(int & iAddress);

    bool ReadSoftwareVersion(int iAddress, float & fVersion);

    bool SetDeviceAddress(int iCurrentAddress, int iNewAddress);
    
protected:

    QMutex &m_Mutex;
    QSerialPort &m_Port;
    QString m_LastError;

    int m_waitTimeout;


    bool WriteToPort(QByteArray qbMessage, QByteArray & qbResponse);

    void (*m_infoCallback)(QString);

    void dispatchInfo(MessageType mType, QString sMessage);

    bool ValidateResponse(QByteArray qbSent, QByteArray qbReceived);

    unsigned short ByteArraytoUShort(QByteArray array, int iStart, int iLength);

signals:
    void infoCallback(MessageType mType, QString sMessage);

};

#endif
