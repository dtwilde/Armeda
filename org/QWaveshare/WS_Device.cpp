#include "WS_Device.h""

#include "Q_CRC16.h"
#include <QByteArray>
#include <QThread>


WS_Device::WS_Device(QMutex &mSerialPortMutex, QSerialPort &sPort, int iWaitTimeout)
    :m_Mutex(mSerialPortMutex), m_Port(sPort), m_waitTimeout(iWaitTimeout)
{
    m_LastError = "";
}




bool WS_Device::WriteToPort(QByteArray qbMessage, QByteArray & qbResponse)
{

    bool bReturn = false;

    m_Mutex.lock();

    //see if the ports open, if not attempt to open it
    if(m_Port.isOpen()==false)
    {
        if (!m_Port.open(QIODevice::ReadWrite))
        {
            dispatchInfo(MessageType::Error,"Can't open port" + m_Port.portName() + ", error code " + m_Port.errorString());
        }
        else
        {
           QString szOpenresult = "";

           szOpenresult = "Sucessfully opened port. Baud Rate:" +
                           QString::number(m_Port.baudRate()) +
                           " Parity=";

           QSerialPort::Parity iParity = m_Port.parity();

           if(iParity==QSerialPort::NoParity)   szOpenresult += "None";
           if(iParity==QSerialPort::EvenParity) szOpenresult += "Even";
           if(iParity==QSerialPort::OddParity)  szOpenresult += "Odd";

           dispatchInfo(MessageType::Info,szOpenresult);
        }
    }

    if(m_Port.isOpen())
    {
        Crc16Out(qbMessage);

        m_Port.clear();

        if(m_Port.write(qbMessage))
        {

            dispatchInfo(MessageType::RxTx, "Sent : " + QString(qbMessage.toHex()));

            if (m_Port.waitForBytesWritten(m_waitTimeout))
            {
                // read response
                if (m_Port.waitForReadyRead(m_waitTimeout))
                {
                    qbResponse = m_Port.readAll();
                    while (m_Port.waitForReadyRead(100))
                        qbResponse += m_Port.readAll();

                    if(ValidateResponse(qbMessage,qbResponse))
                    {

                        dispatchInfo(MessageType::RxTx, "Received: " + QString(qbResponse.toHex()));

                        bReturn = true;
                    }
                    else
                    {
                        dispatchInfo(MessageType::RxTx, "Received: " + QString(qbResponse.toHex()) + " Invalid Response");
                    }

                }
                else
                {
                    dispatchInfo(MessageType::Error, "Wait read response timeout");
                }
            }
            else
            {
                dispatchInfo(MessageType::Error, "Wait write request timeout");
            }
        }
        else
        {
             dispatchInfo(MessageType::Error, "Write to device failed " + m_Port.errorString());
        }

    }

    m_Mutex.unlock();

    return bReturn;
}


bool WS_Device::SetBaudRate(int iDevice, QSerialPort::BaudRate baudRate, QSerialPort::Parity portParity)
{
    bool bReturn = false;


    QByteArray qbRequest;

    qbRequest.append(char(iDevice)); //Broadcast Device Address
    qbRequest.append(0x06); //Command for configuring device

    qbRequest.append(char(0x20)); //Command register for setting baud rate
    qbRequest.append(char(0x00));


    //Set the parity
    if(portParity      ==QSerialPort::OddParity)
        qbRequest.append(char(0x02));
    else if (portParity==QSerialPort::EvenParity)
        qbRequest.append(char(0x01));
    else
        qbRequest.append(char(0x00));


    if(baudRate     ==QSerialPort::Baud4800)   qbRequest.append(char(0x00));
    else if(baudRate==QSerialPort::Baud9600)   qbRequest.append(char(0x01));
    else if(baudRate==QSerialPort::Baud19200)  qbRequest.append(char(0x02));
    else if(baudRate==QSerialPort::Baud38400)  qbRequest.append(char(0x03));
    else if(baudRate==QSerialPort::Baud57600)  qbRequest.append(char(0x04));
    else if(baudRate==QSerialPort::Baud115200) qbRequest.append(char(0x05));
    else
    {
        dispatchInfo(MessageType::Error, "Inavalid baud rate " + QString::number(baudRate));
        return false;
    }


    QByteArray qbResponse;

    if(WriteToPort(qbRequest, qbResponse))
    {
        bReturn = true;
        //the device should repsond with the identical message sent to it
        //for a succesfull write so compare the request and response,
        //the = operator doesnt seem to work for this so a loop is used
        for(int i=0;i<qbRequest.count();i++)
        {
            if(qbRequest[i]!=qbResponse[i])
            {
                bReturn = false;
                break;
            }
        }
    }



    QString szResult = "";

    if(bReturn)
        szResult = "Successfully set device " + QString::number(iDevice) + " Baudrate:" + QString::number(baudRate) + " Parity:";
    else
        szResult = "Failed to set device " + QString::number(iDevice) + " Baudrat: " + QString::number(baudRate) + " Parity:";


    if(portParity==QSerialPort::NoParity)   szResult += "None";
    if(portParity==QSerialPort::EvenParity) szResult += "Even";
    if(portParity==QSerialPort::OddParity)  szResult += "Odd";

    dispatchInfo(MessageType::Info, szResult);

    return bReturn;

}

bool WS_Device::SetDeviceAddress(int iCurrentAddress, int iNewAddress)
{
    bool bReturn = false;

    QByteArray qbRequest;

    qbRequest.append(char(iCurrentAddress)); //Broadcast Device Address
    qbRequest.append(0x06); //Command for configuring device

    qbRequest.append(char(0x40)); //Command register for setting device address
    qbRequest.append(char(0x00));

    qbRequest.append(char(0x00));
    qbRequest.append(char(iNewAddress)); //the new device address

    QByteArray qbResponse;

    qbResponse.clear();

    if(WriteToPort(qbRequest, qbResponse))
    {
        bReturn = true;
        //the device should repsond with the identical message sent to it
        //for a succesfull write so compare the request and response,
        //the = operator doesnt seem to work for this so a loop is used
        for(int i=0;i<qbRequest.count();i++)
        {
            if(qbRequest[i]!=qbResponse[i])
            {
                bReturn = false;
                break;
            }
        }
    }

    if(bReturn)
        dispatchInfo(MessageType::Info, "Successfully changed device address");
    else
        dispatchInfo(MessageType::Info, "Failed to change device address");


    return bReturn;

}


bool WS_Device::ReadDeviceAddress(int & iAddress)
{
    bool bReturn = false;

    QByteArray qbRequest;

    qbRequest.append(char(0x00)); //Broadcast Device Address
    qbRequest.append(0x03); //Command for reading device address (This only works with 1 device on the port at a time)

    qbRequest.append(char(0x40)); //Command register for reading device address
    qbRequest.append(char(0x00));
    qbRequest.append(char(0x00));
    qbRequest.append(char(0x01));

    QByteArray qbResponse;

    qbResponse.clear();

    if(WriteToPort(qbRequest, qbResponse))
    {
        bReturn=true;

       if(qbResponse.count())
       {
            iAddress = qbResponse[0];
            bReturn = true;
       }
       else
       {
           bReturn = false;
       }
    }

    if(bReturn)
        dispatchInfo(MessageType::Info, "Successfully received device address");
    else
        dispatchInfo(MessageType::Info, "Failed to get device address");


    return bReturn;

}

bool WS_Device::ReadSoftwareVersion(int iAddress, float & fVersion)
{
    bool bReturn = false;

    QByteArray qbRequest;

    qbRequest.append(char(iAddress)); // Device Address
    qbRequest.append(0x03); //Command for reading device address (This only works with 1 device on the port at a time)

    qbRequest.append(char(0x80)); //Command register for reading device address
    qbRequest.append(char(0x00));
    qbRequest.append(char(0x00));
    qbRequest.append(char(0x01));

    QByteArray qbResponse;

    qbResponse.clear();

    if(WriteToPort(qbRequest, qbResponse))
    {
       if(qbResponse.count()>=5)
       {
            fVersion = qbResponse[5];
            fVersion = fVersion / 100;
            bReturn = true;
       }
       else
       {
           bReturn = false;
       }
    }


    return bReturn;
}

bool WS_Device::ValidateResponse(QByteArray qbSent, QByteArray qbReceived)
{
    bool bReturn = false;


    //Verify CRC is correct
    if(Crc16In(qbReceived)==false)
    {
        dispatchInfo(MessageType::Error,"Response has invalid CRC");
    }
    //messages are always over 3 bytes
    else if(qbSent.count()     > 3 &&
            qbReceived.count() > 3)
    {
         //if the request is a broadcast then the response address wont match
        if(qbSent[0] == char(0x00))
        {
            bReturn = true;
        }
        //if the request is not a broadcast then the response address and command must match
        else if(
           qbSent[0] == qbReceived[0] &&
           qbSent[1] == qbReceived[1])
        {

            bReturn = true;
        }
        else
        {
            dispatchInfo(MessageType::Error,"Response address/command does not match request");
        }

    }

    return bReturn;

}
void WS_Device::dispatchInfo(MessageType mType, QString sMessage)
{

    emit infoCallback(mType,sMessage);

    if(mType==MessageType::Error)
        m_LastError = sMessage;

    qDebug() << sMessage;

}

QString WS_Device::GetLastError(void)
{
    return m_LastError;
}


unsigned short WS_Device::ByteArraytoUShort(QByteArray array, int iStart, int iLength)
{
    unsigned short usReturn=0;

    QByteArray sArray = array.mid(iStart,iLength);

    for(int i=0;i<sArray.size(); i++)
    {
        usReturn = (usReturn << 8) | static_cast<unsigned char>(sArray[i]);
    }

    return usReturn;
}


