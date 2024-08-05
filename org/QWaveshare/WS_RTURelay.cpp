#include "WS_RTURelay.h"


WS_RTURelay::WS_RTURelay(int iChannelSize, QMutex &mSerialPortMutex, QSerialPort &sPort, int iWaitTimeout)
    :WS_Device(mSerialPortMutex,sPort,iWaitTimeout)
{
    m_iChannelSize = iChannelSize;
}


bool WS_RTURelay::ControlSingleRelay(int iDeviceAddress, int iRelay, RelayState rState)
{
    bool bReturn = false;

    QByteArray qbRequest;

    qbRequest.append(iDeviceAddress); //Device Address
    qbRequest.append(0x05); //Command for controlling relay

    qbRequest.append(char(0x00)); //The register address of the relay
    qbRequest.append(iRelay);

    switch(rState)
    {
        case RelayState::RelayOn:
            qbRequest.append(0xFF); //The command to send to relay
            qbRequest.append(char(0x00));
        break;
        case RelayState::RelayOff:
            qbRequest.append(char(0x00)); //The command to send to relay
            qbRequest.append(char(0x00));
        break;
        case RelayState::RelayFlip:
            qbRequest.append(0x55); //The command to send to relay
            qbRequest.append(char(0x00));
        break;
    }

    QByteArray qbResponse;

    qbResponse.clear();

    if(WriteToPort(qbRequest, qbResponse))
    {
        bReturn=true;

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

        dispatchInfo(MessageType::Error, "Write to relay" + QString::number(iRelay + 1) + "successful");
    else
        dispatchInfo(MessageType::Error, "Write to relay" + QString::number(iRelay + 1) + "failed");


    return bReturn;

}

bool WS_RTURelay::ControlAllRelays(int iDeviceAddress, RelayState rState)
{
    bool bReturn = false;

    QByteArray qbRequest;

    qbRequest.append(iDeviceAddress); //Device Address
    qbRequest.append(0x05); //Command for controlling relay

    qbRequest.append(char(0x00)); //The register address of the relay
    qbRequest.append(0xFF); //Command for all controlling all relays

    switch(rState)
    {
        case RelayState::RelayOn:
            qbRequest.append(0xFF);        //All Relays On
            qbRequest.append(char(0x00));
        break;
        case RelayState::RelayOff:
            qbRequest.append(char(0x00)); //All Relays Off
            qbRequest.append(char(0x00));
        break;
        case RelayState::RelayFlip:
            qbRequest.append(0x55); //Flip All Relays
            qbRequest.append(char(0x00));
        break;
    }

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
        dispatchInfo(MessageType::Info, "Write to all relays successful");
    else
        dispatchInfo(MessageType::Info, "Write to all relays failed");


    return bReturn;
}

QVector<RelayState> WS_RTURelay::ReadStatesofRelays(int iDeviceAddress)
{
    QVector<RelayState> vReturn;


    QByteArray qbRequest;

    qbRequest.append(iDeviceAddress); //Device Address
    qbRequest.append(0x01); //Command for reading all relays

    qbRequest.append(char(0x00)); //Fixed command for reading relays
    qbRequest.append(char(0x00));
    qbRequest.append(char(0x00));
    qbRequest.append(char(0x08));

    QByteArray qbResponse;

    if(WriteToPort(qbRequest, qbResponse))
    {

       //01 01 01 80 5028
       //the answer to this request is in the 4th byte

        if(qbResponse.size() > 4)
        {
            QString szRelayStates= qbResponse.mid(3,1).toHex();

            bool bOk=false;
            int iRelayStates = szRelayStates.toShort(&bOk,16);

            dispatchInfo(MessageType::Info, "Relay States Response " + QString::number(iRelayStates,2));

            if(iRelayStates & 0b00000001){vReturn.append(RelayState::RelayOn);}else{vReturn.append(RelayState::RelayOff);}
            if(iRelayStates & 0b00000010){vReturn.append(RelayState::RelayOn);}else{vReturn.append(RelayState::RelayOff);}
            if(iRelayStates & 0b00000100){vReturn.append(RelayState::RelayOn);}else{vReturn.append(RelayState::RelayOff);}
            if(iRelayStates & 0b00001000){vReturn.append(RelayState::RelayOn);}else{vReturn.append(RelayState::RelayOff);}
            if(iRelayStates & 0b00010000){vReturn.append(RelayState::RelayOn);}else{vReturn.append(RelayState::RelayOff);}
            if(iRelayStates & 0b00100000){vReturn.append(RelayState::RelayOn);}else{vReturn.append(RelayState::RelayOff);}
            if(iRelayStates & 0b01000000){vReturn.append(RelayState::RelayOn);}else{vReturn.append(RelayState::RelayOff);}
            if(iRelayStates & 0b10000000){vReturn.append(RelayState::RelayOn);}else{vReturn.append(RelayState::RelayOff);}

        }

    }


    return vReturn;

}


bool WS_RTURelay::WriteStatesofRelays(int iDeviceAddress, QVector<RelayState> vStates)
{

    bool bReturn = false;

    int iStatusByte = 0;


    if(vStates.count()==m_iChannelSize)
    {
        for(int i=0;i<vStates.count();i++)
        {
            int iBit = 0xb00000001;

            iBit = iBit << i;

            if(vStates[i]==RelayState::RelayOn)
            {
                iStatusByte = iStatusByte & iBit;
            }
        }

        bReturn =  WriteStatesofRelays(iDeviceAddress, iStatusByte);
    }
    else
    {
        dispatchInfo(MessageType::Error,"Invalid relay vector size");
    }

    return bReturn;

}

bool WS_RTURelay::WriteStatesofRelays(int iDeviceAddress, int iStatusByte)
{
    bool bReturn=false;

    QByteArray qbRequest;

    qbRequest.append(iDeviceAddress); //Device Address
    qbRequest.append(0x0F); //Command for writting all relays

    qbRequest.append(char(0x00)); //Fixed command for writting to all relays
    qbRequest.append(char(0x00));
    qbRequest.append(char(0x00));
    qbRequest.append(char(0x08));

    qbRequest.append(char(0x01)); //Number of bytes


    //Generate the relay status byte

    qbRequest.append(char(iStatusByte)); //Status of relays

    QByteArray qbResponse;


    if(WriteToPort(qbRequest, qbResponse))
    {
        dispatchInfo(MessageType::Info,"Sucessfull write to all relays" + QString::number(iStatusByte,2));
    }
    else
    {
        dispatchInfo(MessageType::Info, "Failed write to all relays" + QString::number(iStatusByte,2));
    }


    return bReturn;
}


bool WS_RTURelay::RelayFlashOnOff(int iDeviceAddress,int iRelay, int iInterval, bool bFlashOn)
{

    bool bReturn=false;

    QByteArray qbRequest;

    qbRequest.append(iDeviceAddress); //Device Address
    qbRequest.append(0x05); //Single control command

    if(bFlashOn)
        qbRequest.append(char(0x02)); //Flash On
    else
        qbRequest.append(char(0x04)); //Flash Off

    qbRequest.append(char(iRelay)); //Relay to control

    qbRequest.append(char(0x00));
    qbRequest.append(char(iInterval)); //Interval Time  = iInterval * 100ms


    QByteArray qbResponse;


    if(WriteToPort(qbRequest, qbResponse))
    {
        dispatchInfo(MessageType::Info, "Sucessfull write to flash relay:" + QString::number(iRelay) + "Interval:" + QString::number(iInterval) + "Flash On:" + QString::number(bFlashOn));
    }
    else
    {
        dispatchInfo(MessageType::Info, "Failed write to flash relay:" + QString::number(iRelay) + "Interval:" + QString::number(iInterval) + "Flash On:" + QString::number(bFlashOn));
    }

    return bReturn;
}
