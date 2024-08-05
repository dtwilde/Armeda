#include "WS_AnalogInput.h"


WS_AnalogInput::WS_AnalogInput(QMutex &mSerialPortMutex, QSerialPort &sPort, int iWaitTimeout)
    :WS_Device(mSerialPortMutex,sPort,iWaitTimeout)
{
}


bool WS_AnalogInput::ReadAnalogInput(int iDeviceAddress,int iInitialAddress, int iRegisterCount, QVector<float> & vReturnData)
{
    bool bReturn = false;


    QByteArray qbRequest;

    qbRequest.append(iDeviceAddress); //Device Address
    qbRequest.append(0x04); //Command for reading input register

    qbRequest.append(char(0x00)); //Initial register address
    qbRequest.append(char(iInitialAddress));

    qbRequest.append(char(0x00)); //register numbers
    qbRequest.append(char(iRegisterCount));

    QByteArray qbResponse;

    qbResponse.clear();

    if(WriteToPort(qbRequest, qbResponse))
    {
        if(qbResponse.count() > 5) //the minimum response message can be 5 bytes
        {

            int iDataLength = qbResponse[2];

            int iLen = iDataLength + 5;

            //the size of the message returned should equal the data length + 5
            if(qbResponse.count()==iLen)
            {

                for(int i=0; i<iDataLength; i+=2)
                {
                    unsigned short usResult = ByteArraytoUShort(qbResponse,i+3,2);

                    vReturnData.append((float)usResult/1000);

                }

                bReturn = true;
            }
            else
            {
                dispatchInfo(MessageType::Error, "Invalid data length received");
            }

        }

    }


    return bReturn;
}


bool WS_AnalogInput::ReadChannelDataType(int iDeviceAddress,int iAddress, int i, QVector<unsigned short> & vReturnData)
{
    bool bReturn = false;


    return bReturn;
}

bool WS_AnalogInput::SetSingleChannelDataType(int iDeviceAddress, int iAddress, ChannelType cType)
{
    bool bReturn = false;


    return bReturn;
}

bool WS_AnalogInput::SetMultipleChannelDataType(int iDeviceAddress, int iInitialAddress, int iRegisterCount, QVector<ChannelType> vType)
{
    bool bReturn = false;


    return bReturn;
}
