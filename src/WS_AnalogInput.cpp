#include "WS_AnalogInput.h"
#include<sstream>

/**
 * Class constructor
 *
 * @param sPort A pointer to an sp_port object. This object can be shared between
 *              multiple instances of WS_Device classes however it is not thread
 *              safe. Blocking will have to be put in place to prevent two instances
 *              from using the object at the same time
 * @param iWaitTimeout The timeout in milliseconds to wait for sending/receiving data
 */
WS_AnalogInput::WS_AnalogInput(LibSerialPortWrapper * sPort)
    :WS_Device(sPort)
{

}

/**
 * Reads analog input from the device
 *
 * @param deviceAddress The address of the device to read from
 * @param initialAddress Initial address of the register
 * @param registerCount How many registers to read
 * @param vReturnData A vector of floats to store the results in
 * @return Returns true if the operation was sucessfull
 */
bool WS_AnalogInput::ReadAnalogInput(unsigned char deviceAddress,unsigned char initialAddress, unsigned char registerCount, std::vector<float> & vReturnData)
{
    bool bReturn = false;

    unsigned char sendData[8];

    sendData[0] = deviceAddress; //Device Address
    sendData[1] = 0x04;           //Command for reading input register
    sendData[2] = 0x00;
    sendData[3] = initialAddress;
    sendData[4] = 0x00;
    sendData[5] = registerCount;

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, sizeof(sendData), receivedData, &iResponse))
    {
        if(validateResponse(sendData, sizeof(sendData), receivedData, iResponse,
                                    Validator::MINIMUM_SIZE, 5,
                                    Validator::ADDRESS_MATCH))
        {
            //the number of bytes returned
            char dataLength = receivedData[2];

            //the size of the message returned should equal the data length + 5
            if((dataLength + 5)== iResponse)
            {
                for(int i=0; i < dataLength; i+=2)
                {
                    unsigned char highByte = receivedData[i + 3];
                    unsigned char lowByte =  receivedData[i + 4];

                    unsigned short registerData = (highByte<<8) | lowByte;

                    vReturnData.push_back((float)registerData);
                }

                bReturn = true;
            }
            else
            {
                m_LastError = "Invalid response from device";
            }
        }
    }

    return bReturn;
}


/**
 * Reads channel data types from the device
 *
 * @param deviceAddress The address of the device to read from
 * @param initialAddress Initial address of the register
 * @param registerCount How many registers to read
 * @param vReturnData A vector of AnalogIOChannelType to store the results in
 * @return Returns true if the operation was sucessfull
 */
bool WS_AnalogInput::ReadChannelDataType(unsigned char deviceAddress,unsigned char initialAddress, unsigned char registerCount, std::vector<AnalogIOChannelType> & vReturnData)
{
    bool bReturn = false;

    unsigned char sendData[8];

    sendData[0] = deviceAddress;  //Device Address
    sendData[1] = 0x03;           //Command for reading the hold register
    sendData[2] = 0x10;
    sendData[3] = initialAddress;
    sendData[4] = 0x00;
    sendData[5] = registerCount;

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, sizeof(sendData), receivedData, &iResponse))
    {
        if(validateResponse(sendData, sizeof(sendData), receivedData, iResponse,
                                    Validator::MINIMUM_SIZE, 5,
                                    Validator::ADDRESS_MATCH))
        {
            //the number of bytes returned
            char dataLength = receivedData[2];

            //the size of the message returned should equal the data length + 5
            if((dataLength + 5)== iResponse)
            {
                for(int i=0; i < dataLength; i+=2)
                {
                    char lowByte =  receivedData[i + 4];

                    vReturnData.push_back(static_cast<AnalogIOChannelType>(lowByte));
                }

                bReturn = true;
            }
            else
            {
                m_LastError = "Invalid response from device";
            }
        }

    }

    return bReturn;
}


/**
 * Sets a single channel data type
 *
 * @param deviceAddress The address of the device to write to
 * @param address The channel address to set
 * @param cType The type to set the channel to
 * @return Returns true if the operation was sucessfull
 */
bool WS_AnalogInput::SetSingleChannelDataType(unsigned char deviceAddress, unsigned char address, AnalogIOChannelType cType)
{
    bool bReturn = false;

    //create a char array to hold the 6 byte message and 2 bytes for the crc
    unsigned char sendData[8] = {0x00};

    sendData[0] = deviceAddress; //Device Address
    sendData[1] = 0x06;          //write a single register command
    sendData[2] = 0x10;
    sendData[3] = address;       //Address to set
    sendData[4] = 0x00;          //Padding

    //The data type to set the channel to
    sendData[5] = static_cast<char>(cType);

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, sizeof(sendData), receivedData, &iResponse))
    {
        bReturn = validateResponse(sendData, sizeof(sendData), receivedData, iResponse,
                                   Validator::IDENTICAL_MSG);
    }

    return bReturn;
}

/**
 * Sets a single channel data type
 *
 * @param deviceAddress The address of the device to write to
 * @param initialAddress The channel address channel to set
 * @param vType A vector of AnalogIOChannelType to write to the device
 * @return Returns true if the operation was sucessfull
 */
bool WS_AnalogInput::SetMultipleChannelDataType(unsigned char deviceAddress, unsigned char initialAddress, std::vector<AnalogIOChannelType> vType)
{
    bool bReturn = false;


    int regToWrite = vType.size();

    if(regToWrite>0)
    {
        //create a char array to hold the maximum size message
        unsigned char sendData[24] = {0x00};

        sendData[0] = deviceAddress;  //Device Address
        sendData[1] = 0x10;           //write a multipe register command
        sendData[2] = 0x10;
        sendData[3] = initialAddress; //initial address
        sendData[4] = 0x00;           //Padding
        sendData[5] = regToWrite;     //how many registers to write

        //check to make sure valid parameters are met
        if(!(vType.size() + initialAddress > 8))
        {
            int byteTosend = 0;

            char commandBytes = vType.size() * 2; //how many bytes are being written

            sendData[6]=commandBytes;

            for(int i = 0, j=0; i<commandBytes; i+=2, j++)
            {
                sendData[7 + i]= 0x00;
                sendData[8 + i]= static_cast<char>(vType[j]);
            }

            byteTosend = commandBytes + 9;

            unsigned char receivedData[XBUFF_SIZE] = {0x0};

            int iResponse = 0;

            if(WriteToPort(sendData, byteTosend, receivedData, &iResponse))
            {
                bReturn = validateResponse(sendData, byteTosend, receivedData, iResponse,
                                           Validator::PARTIAL_COMPARE, 6);
            }
        }
        else
        {
            std::stringstream stream;

            stream  << "Unable to write " << vType.size() <<
                    " registers at starting point " << (int)initialAddress;

            m_LastError = stream.str();

        }
    }
    else
    {
        std::stringstream stream;

        stream  << "Invalid number of registers received. Expected 8 Received " << regToWrite;

        m_LastError = stream.str();
    }

    return bReturn;
}
