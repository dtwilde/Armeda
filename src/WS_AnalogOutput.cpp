#include "WS_AnalogOutput.h"
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
WS_AnalogOutput::WS_AnalogOutput(LibSerialPortWrapper * sPort)
    :WS_Device(sPort)
{

}


/**
 * Sets a signle channels output value
 *
 * @param deviceAddress The device address
 * @param address The channel to set the output value to
 * @param value The value to write to the channel
 * @return Returns true if the operation was succesfull
 */
bool WS_AnalogOutput::SetSingleChannelOutput(unsigned char deviceAddress,unsigned char address, unsigned int value)
{
    bool bReturn = false;

    //create a char array to hold the 6 byte message and 2 bytes for the crc
    unsigned char sendData[8] = {0x00};

    sendData[0] = deviceAddress; //Device Address
    sendData[1] = 0x06;          //write a single register command
    sendData[2] = 0x00;
    sendData[3] = address;        //channel to set

    //the value to set the channel to
    sendData[4] = (value >> 8) & 0xFF; //High bits
    sendData[5] = value & 0xFF;       //Low bits

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
 * Sets a multiple channels output value
 *
 * @param deviceAddress The device address
 * @param initialAddress The channel to set the output value to
 * @param channelOutput A vector of unsigned ints representing the values to write
 * @return Returns true if the operation was succesfull
 */
bool WS_AnalogOutput::SetMultipleChannelOutput(unsigned char deviceAddress, unsigned char initialAddress, std::vector<unsigned int> & channelOutput)
{
    bool bReturn = false;

    char regToWrite = channelOutput.size();

    if(regToWrite>0)
    {
        //create a char array to hold the maximum size message
        unsigned char sendData[24] = {0x00};

        sendData[0] = deviceAddress;   //Device Address
        sendData[1] = 0x10;            //write a multipe register command
        sendData[2] = 0x00;
        sendData[3] = initialAddress;  //initial address
        sendData[4] = 0x00;            //Padding
        sendData[5] = regToWrite;      //how many registers to write

        //check to make sure valid parameters are met
        if(!(regToWrite + initialAddress > 8))
        {
            int byteTosend = 0;
            char commandBytes = regToWrite * 2; //how many bytes are being written

            sendData[6]=commandBytes;

            for(int i = 0, j=0; i<commandBytes; i+=2, j++)
            {
                unsigned int valueToWrite = channelOutput[j];

                //the value to set the channel to
                sendData[7 + i] = (valueToWrite >> 8) & 0xFF; //High bits
                sendData[8 + i] = valueToWrite & 0xFF;       //Low bits

            }

            byteTosend = commandBytes + 9;

            unsigned char receivedData[XBUFF_SIZE] = {0x0};

            int iResponse = 0;

            if(WriteToPort(sendData, byteTosend, receivedData, &iResponse))
            {
                bReturn = validateResponse(sendData, sizeof(sendData), receivedData, iResponse,
                                           Validator::IDENTICAL_MSG);
            }

        }
        else
        {
            std::stringstream stream;

            stream  << "Unable to write " << regToWrite <<
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

/**
 * Reads the value of a output channel
 *
 * @param deviceAddress The device address
 * @param initialAddress The channel to set the output value to
 * @param registerCount The amount of registers to read
 * @param channelOutput A reference to vector of unsigned ints representing the values read
 * @return Returns true if the operation was succesfull
 */
bool WS_AnalogOutput::ReadChannelOutput(unsigned char deviceAddress, unsigned char initialAddress, unsigned char registerCount, std::vector<unsigned int> & channelOutput)
{
    bool bReturn = false;

    unsigned char sendData[8];

    sendData[0] = deviceAddress;  //Device Address
    sendData[1] = 0x03;           //Command for reading output register
    sendData[2] = 0x00;
    sendData[3] = initialAddress;
    sendData[4] = 0x00;
    sendData[5] = registerCount;

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, sizeof(sendData), receivedData, &iResponse))
    {
        if(validateResponse(sendData, sizeof(sendData), receivedData, iResponse,
                            Validator::ADDRESS_MATCH,
                            Validator::MINIMUM_SIZE, 7))
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

                    channelOutput.push_back((float)registerData);
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
