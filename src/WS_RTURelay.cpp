#include "WS_RTURelay.h"
#include "WS_Device.h"
#include <vector>
#include <sstream>

/**
 * Turns a single relay on or off
 *
 * @param iChannelSize The size of the relay board 4/8/16/32
 * @param sPort A pointer to the serial sp_port object to use
 * @param iWaitTimeout The desired timeout for read/writes
 */

WS_RTURelay::WS_RTURelay(LibSerialPortWrapper * libSerialPort)
    :WS_Device(libSerialPort)
{
}

/**
 * Turns a single relay on or off
 *
 * @param iDeviceAddress The address of the device
 * @param iRelay The relay to control
 * @param rState The desired state of the relay
 */
bool WS_RTURelay::ControlSingleRelay(unsigned char deviceAddress, unsigned char relay, RelayState rState)
{
    bool bReturn = false;

    //create a char array to hold the 6 byte message and 2 bytes for the crc
    unsigned char sendData[8] = {0x00};

    sendData[0] = deviceAddress;  //Device Address
    sendData[1] = 0x05;           //Command for controlling relay

    sendData[2] = 0x00;
    sendData[3] = relay;          //Relay to control

    
    sendData[4] = char(rState);   //Set the command to send the relay
    sendData[5] = 0x00;           //Padding

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, sizeof(sendData), receivedData, &iResponse))
    {
         bReturn = validateResponse(sendData, sizeof(sendData), receivedData, iResponse, Validator::IDENTICAL_MSG);
    }

    return bReturn;
}

/**
 * Turns on/off or flips all relays
 *
 * @param iDeviceAddress The address of the device
 * @param rState The state to write to all relays
 */
bool WS_RTURelay::ControlAllRelays(unsigned char deviceAddress, RelayState rState)
{
    bool bReturn = false;

    //create a char array to hold the 6 byte message and 2 bytes for the crc
    unsigned char sendData[8] = {0x00};

    sendData[0] = deviceAddress; //Device Address
    sendData[1] = 0x05;           //Command for controlling relays

    sendData[2] = 0x00;
    sendData[3] = 0xFF;  //Command for controlling all relays

    switch(rState)
    {
        case RelayState::RelayOn:
            sendData[4] = 0xFF;
        break;
        case RelayState::RelayOff:
            sendData[4] = 0x00;
        break;
        case RelayState::RelayFlip:
            sendData[4] = 0x55;
        break;
    }

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, sizeof(sendData), receivedData, &iResponse))
    {
        bReturn = validateResponse(sendData, sizeof(sendData), receivedData, iResponse, Validator::IDENTICAL_MSG);
    }

    return bReturn;
}

/**
 * Reads the current state of all relays
 *
 * @param iDeviceAddress The address of the device
 */
 //TODO change the return type to a bool to match the rest of the library 
std::vector<RelayState> WS_RTURelay::ReadStatesofRelays(unsigned char deviceAddress, RTUChannelSize channelSize)
{

    std::vector<RelayState> vReturn;

    //create a char array to hold the 6 byte message and 2 bytes for the crc
    unsigned char sendData[8] = {0x00};

    sendData[0] = deviceAddress; //Device Address
    sendData[1] = 0x01;           //Command for reading all relays
    sendData[2] = 0x00;
    sendData[3] = 0x00;

    //end address
    sendData[4] = 0x00;
    sendData[5] = static_cast<char>(channelSize);

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, sizeof(sendData), receivedData, &iResponse))
    {
        if(validateResponse(sendData,sizeof(sendData),receivedData, iResponse, Validator::ADDRESS_MATCH) &&
           iResponse > 2)
        {
            //the number of bytes returned
            char bytesReturned = receivedData[2];

            //a response from a 8 channel board
            if(bytesReturned==1 && iResponse==6)
            {
                generateRelayVector(receivedData[3], &vReturn);
            }
            //a response from a 16 channel board
            if(bytesReturned==2  && iResponse==7)
            {
                generateRelayVector(receivedData[3], &vReturn);
                generateRelayVector(receivedData[4], &vReturn);
            }
            //a response from a 32 channel board
            if(bytesReturned==4  && iResponse==9)
            {
                generateRelayVector(receivedData[3], &vReturn);
                generateRelayVector(receivedData[4], &vReturn);
                generateRelayVector(receivedData[5], &vReturn);
                generateRelayVector(receivedData[6], &vReturn);
            }
        }

    }

    return vReturn;
}

/**
 * Helper function for converting bytes representing relay status's into a more readable vector
 *
 * @param receivedByte The byte to convert
 * @param relayVector A vector of RelayStates representing the states
 */
void WS_RTURelay::generateRelayVector(unsigned char receivedByte, std::vector<RelayState> * relayVector)
{
    if(NULL!=relayVector)
    {
        if(receivedByte & 0b00000001){relayVector->push_back(RelayState::RelayOn);}else{relayVector->push_back(RelayState::RelayOff);}
        if(receivedByte & 0b00000010){relayVector->push_back(RelayState::RelayOn);}else{relayVector->push_back(RelayState::RelayOff);}
        if(receivedByte & 0b00000100){relayVector->push_back(RelayState::RelayOn);}else{relayVector->push_back(RelayState::RelayOff);}
        if(receivedByte & 0b00001000){relayVector->push_back(RelayState::RelayOn);}else{relayVector->push_back(RelayState::RelayOff);}
        if(receivedByte & 0b00010000){relayVector->push_back(RelayState::RelayOn);}else{relayVector->push_back(RelayState::RelayOff);}
        if(receivedByte & 0b00100000){relayVector->push_back(RelayState::RelayOn);}else{relayVector->push_back(RelayState::RelayOff);}
        if(receivedByte & 0b01000000){relayVector->push_back(RelayState::RelayOn);}else{relayVector->push_back(RelayState::RelayOff);}
        if(receivedByte & 0b10000000){relayVector->push_back(RelayState::RelayOn);}else{relayVector->push_back(RelayState::RelayOff);}
    }
}
/**
 * Write the state of all relays in one message to the device
 *
 * @param iDeviceAddress The address of the device
 * @param vStates A vector of RelayStates representing the desired states
 */
bool WS_RTURelay::WriteStatesofRelays(unsigned char deviceAddress, std::vector<RelayState> vStates)
{
    bool bReturn = false;

    unsigned char statusByte = 0;

    int iVectorSize = vStates.size();

    //verify the correct amount of relays for this device have been passed to the function
    if(iVectorSize==RTUChannelSize::Channel_8 ||
       iVectorSize==RTUChannelSize::Channel_16 ||
       iVectorSize==RTUChannelSize::Channel_32)
    {
        for(int i=0;i<iVectorSize;i++)
        {
            unsigned char byteMask = 0xb00000001;

            byteMask = byteMask << i;

            if(vStates[i]==RelayState::RelayOn)
            {
                statusByte = statusByte & byteMask;
            }
        }

        //use the other overloaded version of this function to perform the write
        bReturn =  WriteStatesofRelays(deviceAddress, static_cast<RTUChannelSize>(iVectorSize), statusByte);
    }
    else
    {
        m_LastError = "Invalid amount of relay states received 8,16 and 32 supported only";
    }

    return bReturn;

}

/**
 * Write the state of all relays in one message to the device
 *
 * @param iDeviceAddress The address of the device
 * @param channelSize The number of relays on the board
 * @param iStatusByte The binary representation of the relay states to be sent
 */
bool WS_RTURelay::WriteStatesofRelays(unsigned char deviceAddress, RTUChannelSize channelSize, unsigned int statusByte)
{
    bool bReturn=false;

    unsigned char sendData[13]; //allocate 13 bytes for the largest 32 channel relay

    int iMessageSize = 0;

    sendData[0] = deviceAddress; //Device Address
    sendData[1] = 0x0F;           //Command for writting all relays
    sendData[2] = 0x00;
    sendData[3] = 0x00;
    sendData[4] = 0x00;
    sendData[5] = 0x08;  //command for writting all relay states

    char * individualBytes = reinterpret_cast<char *>(&statusByte);

    switch(channelSize)
    {
        case RTUChannelSize::Channel_8:
            sendData[6] = 0x01;  //Number of bytes the relay state is
            sendData[7] = individualBytes[0];
            iMessageSize=10;
        break;

        case RTUChannelSize::Channel_16:
            sendData[6] = 0x02;  //Number of bytes the relay state is
            sendData[7] = individualBytes[0];
            sendData[8] = individualBytes[1];
            iMessageSize=11;
        break;

        case RTUChannelSize::Channel_32:
            sendData[6]  = 0x04;  //Number of bytes the relay state is
            sendData[7]  = individualBytes[0];
            sendData[8]  = individualBytes[1];
            sendData[9]  = individualBytes[2];
            sendData[10] = individualBytes[3];
            iMessageSize=13;
        break;
    }

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, iMessageSize, receivedData, &iResponse))
    {
        bReturn = validateResponse(sendData,iMessageSize,receivedData,iResponse, Validator::PARTIAL_COMPARE, 6);
    }

    return bReturn;
}


/**
 * Flashes a relay on or off at a given interal
 *
 * @param iDeviceAddress The address of the device
 * @param iInterval Delay time of flash x by 100ms
 *        ex  10 = 1 second, 50 = 5 seconds
 * @param bFlashOn Flash on or off
 */
bool WS_RTURelay::RelayFlashOnOff(unsigned char deviceAddress,unsigned char relay, unsigned char interval, bool bFlashOn)
{
    bool bReturn=false;

    unsigned char sendData[8];

    sendData[0] = deviceAddress; //Device Address
    sendData[1] = 0x05;           //Single control command


    if(bFlashOn)
       sendData[2] = 0x02; //Flash On
    else
       sendData[2] = 0x04; //Flash Off

    sendData[3] = relay;

    sendData[4] = 0x00;
    sendData[5] = interval;  //Interval Time  = iInterval * 100ms

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, sizeof(sendData), receivedData, &iResponse))
    {
        bReturn = validateResponse(sendData,sizeof(sendData),receivedData,iResponse, Validator::IDENTICAL_MSG);
    }

    return bReturn;
}
