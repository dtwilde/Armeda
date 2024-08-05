#include "WS_Digital_IO.h"
#include<sstream>


/**
 * Class constructor
 *
 * @param lbSerialPort A pointer to an LibSerialPortWrapper object. This object can be shared between
 *                     multiple instances of WS_Device classes
 */

WS_Digital_IO::WS_Digital_IO(LibSerialPortWrapper * libSerialPort)
          :WS_Device(libSerialPort)
{
}


/** Controls the value of an individual output channel
 *
 * @param deviceAddress The device address
 * @param address The channel to control
 * @param value The status to write On/Off/Flip
 */
bool WS_Digital_IO::ControlSingleOuputChannel(unsigned char deviceAddress,unsigned char address, DigitalIO_State value)
{
    bool bReturn = false;

    //create a char array to hold the 6 byte message and 2 bytes for the crc
    unsigned char sendData[8] = {0x00};

    sendData[0] = deviceAddress;  //Device Address
    sendData[1] = 0x05;           //Command for controlling relay
    sendData[2] = 0x00;           //Pading
    sendData[3] = address;        //Address to control
    sendData[4] = char(value);    //Set the channel state
    sendData[5] = 0x00;           //Padding

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, 8, receivedData, &iResponse))
    {
        bReturn = validateResponse(sendData, sizeof(sendData), receivedData, iResponse,
                                   Validator::IDENTICAL_MSG);
    }

    return bReturn;
}


/** Controls the value of all output channels
 *
 * @param deviceAddress The device address
 * @param command The status to write On/Off/Flip
 */
bool WS_Digital_IO::AllOutputChannelControl(unsigned char deviceAddress, DigitalIO_State command)
{
    bool bReturn = false;

    //create a char array to hold the 6 byte message and 2 bytes for the crc
    unsigned char sendData[8] = {0x00};

    sendData[0] = deviceAddress;  //Device Address
    sendData[1] = 0x05;           //Command for controlling relay
    sendData[2] = 0x00;           //Padding
    sendData[3] = 0xFF;           //All address control
    sendData[4] = char(command);  //Set the channel state
    sendData[5] = 0x00;           //Padding

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, sizeof(sendData), receivedData, &iResponse))
    {
        bReturn = validateResponse(sendData, sizeof(sendData), receivedData, iResponse,
                                   Validator::IDENTICAL_MSG);
    }

    return bReturn;
}

/** Reads the status of all output channels
 *
 * @param deviceAddress The device address
 * @param channelOutput The status of the channel outputs
 */
bool WS_Digital_IO::ReadOutputChannelStatus(unsigned char deviceAddress, std::vector<bool> & channelOutput)
{
    bool bReturn = false;

    //create a char array to hold the 6 byte message and 2 bytes for the crc
    unsigned char sendData[8] = {0x00};

    sendData[0] = deviceAddress;  //Device Address
    sendData[1] = 0x01;           //Command for read status
    sendData[2] = 0x00;           //Initial address, two bytes, fixed 0x00
    sendData[3] = 0x00;           //
    sendData[4] = 0x00;           //start address, fixed 0x00
    sendData[5] = 0x08;           //number of channels to read, fixed 0x08

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, 8, receivedData, &iResponse))
    {

        bReturn = validateResponse(sendData, sizeof(sendData), receivedData,iResponse,
                                   Validator::ADDRESS_MATCH,
                                   Validator::EXPECTED_SIZE, 6);

        if(bReturn)
        {
                char queryStatus = 0x00;

                queryStatus = receivedData[3];

                for(int i=-0;i < 8; i++)
                {
                    //determine each bit status from the response
                    bool bitStatus = (queryStatus >> i) & 0x01;
                    channelOutput.push_back(bitStatus);
                }
        }
    }
    return bReturn;
}

/** Writes the status of all output channels
 *
 * @param deviceAddress The device address
 * @param channelStatus The status of the channel outputs to write
 */
bool WS_Digital_IO::WriteOutputChannelStatus(unsigned char deviceAddress, std::vector<bool> & channelStatus)
{
    bool bReturn = false;

    if(channelStatus.size()==8)
    {
        //create a char array to hold the 6 byte message and 2 bytes for the crc
        unsigned char sendData[10] = {0x00};

        sendData[0] = deviceAddress; //Device Address
        sendData[1] = 0x0F;          //Write the output channel status command
        sendData[2] = 0x00;          //start address, two bytes, fixed 0x00
        sendData[3] = 0x00;          //
        sendData[4] = 0x00;          //number of channels to write, two bytes fixed 0x08
        sendData[5] = 0x08;          //
        sendData[6] = 0x01;          //number of bytes to write, fixed 0x01


        //generate the status byte
        unsigned char statusByte = 0x00;

        for(int i=channelStatus.size()-1; i>=0 ; i--)
        {
            if(channelStatus[i])
                statusByte |= (1<<(channelStatus.size() -1 - i));
        }

        sendData[7] = statusByte;         //the status byte

        unsigned char receivedData[XBUFF_SIZE] = {0x0};

        int iResponse = 0;

        if(WriteToPort(sendData, 10, receivedData, &iResponse))
        {
            //validate the response
            bReturn = validateResponse(sendData,sizeof(sendData), receivedData,iResponse,
                                       Validator::ADDRESS_MATCH,
                                       Validator::EXPECTED_SIZE, 8);
        }
    }
    else
    {
        m_LastError = "Invalid IO Count Size Received";
        bReturn = false;
    }
    return bReturn;
}


/** Flashes output channels On/Off
 *
 * @param deviceAddress The device address
 * @param command The status of the channel outputs to write
 * @param outputChannelAddress The address of the channel
 * @param intervalTime The time * 100ms to flash on/off
 */
bool WS_Digital_IO::OutputChannelFlashOnOff(unsigned char deviceAddress, DigitalIO_Command command, unsigned char outputChannelAddress, unsigned int intervalTime)
{
    bool bReturn = false;

    //create a char array to hold the 6 byte message and 2 bytes for the crc
    unsigned char sendData[8] = {0x00};

    sendData[0] = deviceAddress;              //Device Address
    sendData[1] = 0x05;                       //Single control command
    sendData[2] = char(command);              //Flash On/Off
    sendData[3] = outputChannelAddress;       //Output channel address
    sendData[4] = (intervalTime >> 8) & 0xFF; //Interval time, 2 bytes
    sendData[5] = intervalTime & 0xFF;

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, 8, receivedData, &iResponse))
    {
        bReturn = validateResponse(sendData,sizeof(sendData),receivedData,iResponse,
                                   Validator::IDENTICAL_MSG);
    }

    return bReturn;
}

/** Reads the status of input channels
 *
 * @param deviceAddress The device address
 * @param channelStatus A vector of bools representing the channel statuses
 */
bool WS_Digital_IO::ReadInputChannelStatus(unsigned char deviceAddress, std::vector<bool> & channelStatus)
{
    bool bReturn = false;

    //create a char array to hold the 6 byte message and 2 bytes for the crc
    unsigned char sendData[8] = {0x00};

    sendData[0] = deviceAddress;  //Device Address
    sendData[1] = 0x02;           //Read the input status command
    sendData[2] = 0x00;           //Inital address, 2 bytes
    sendData[3] = 0x00;           //Fixed 0x00
    sendData[4] = 0x00;           //Number of registers, 2 bytes
    sendData[5] = 0x08;           //Fixed 0x08

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, 8, receivedData, &iResponse))
    {
        bReturn = validateResponse(sendData,sizeof(sendData), receivedData,iResponse,
                                   Validator::ADDRESS_MATCH,
                                   Validator::EXPECTED_SIZE, 6);

        if(bReturn)
        {
            char queryStatus = receivedData[3];

            uint8_t iMask = 0xb00000001;

            for(int i=0; i<8; i++)
            {
                bool bStatus = iMask & queryStatus;

                channelStatus.push_back(bStatus);

                iMask = iMask << 1;
            }
        }
    }

    return bReturn;
}

/** Reads the output channel control modes
 *
 * @param deviceAddress The device address
 * @param initalAddress The initial address to start at
 * @param registerCount The amount of registers to read
 * @param channelMode A reference to a vector to store the results in
 */
bool WS_Digital_IO::ReadOutputChannelControlMode(unsigned char deviceAddress, unsigned char initalAddress, unsigned char registerCount, std::vector<Digital_IO_ControlMode> & channelMode)
{
    bool bReturn = false;

    //create a char array to hold the 6 byte message and 2 bytes for the crc
    unsigned char sendData[8] = {0x00};

    sendData[0] = deviceAddress;  //Device Address
    sendData[1] = 0x03;           //Read the input status command
    sendData[2] = 0x10;           //Inital address, 2 bytes
    sendData[3] = initalAddress;  //
    sendData[4] = 0x00;           //Number of registers, 2 bytes
    sendData[5] = registerCount;  //Register count

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, 8, receivedData, &iResponse))
    {
        bReturn = validateResponse(sendData,sizeof(sendData), receivedData,iResponse,
                                   Validator::ADDRESS_MATCH,
                                   Validator::EXPECTED_SIZE, (registerCount * 2) + 5);
        if(bReturn)
        {

            unsigned char dataBytes = receivedData[2];

            for(int i=0; i<dataBytes; i+=2)
            {
                unsigned char status = receivedData[i+4];

                channelMode.push_back((Digital_IO_ControlMode)status);
            }
        }
    }

    return bReturn;
}

/** Sets a single output channel control mode
 *
 * @param deviceAddress The device address
 * @param initalAddress The initial address to start at
 * @param channelAddress The channel address
 * @param controlMode The mode to set the channel to
 */
bool WS_Digital_IO::SetSingleOutputChannelControlMode(unsigned char deviceAddress,unsigned char outputChannelAddress, Digital_IO_ControlMode controlMode)
{
    bool bReturn = false;

    //create a char array to hold the 6 byte message and 2 bytes for the crc
    unsigned char sendData[8] = {0x00};

    sendData[0] = deviceAddress;              //Device Address
    sendData[1] = 0x06;                       //Single control command
    sendData[2] = 0x10;                       //Address of the register, 2 bytes
    sendData[3] = outputChannelAddress;       //Output channel address
    sendData[4] = 0x00;                       //Control mode, 2 bytes
    sendData[5] = (char)controlMode;

    unsigned char receivedData[XBUFF_SIZE] = {0x0};

    int iResponse = 0;

    if(WriteToPort(sendData, 8, receivedData, &iResponse))
    {
        bReturn = validateResponse(sendData,sizeof(sendData), receivedData,iResponse,
                                   Validator::IDENTICAL_MSG);
    }

    return bReturn;
}

/** Sets a single output channel control mode
 *
 * @param deviceAddress The device address
 * @param initalAddress The initial address to start at
 * @param controlMode A vector of the modes to set the channels too
 */
bool WS_Digital_IO::SetMultipleOutputChannelControlMode(unsigned char deviceAddress,unsigned char initialAddress, std::vector<Digital_IO_ControlMode> controlMode)
{
    bool bReturn = false;

    char regToWrite = controlMode.size();

    if(regToWrite>0)
    {
        //create a char array to hold the maximum size message
        unsigned char sendData[24] = {0x00};

        sendData[0] = deviceAddress;     //Device Address
        sendData[1] = 0x10;              //write a multipe register command

        sendData[2] = 0x10;
        sendData[3] = initialAddress;   //initial address

        sendData[4] = 0x00;             //Padding
        sendData[5] = regToWrite;       //how many registers to write

        //check to make sure the starting point + the amount of registers to write
        //does not go out of bounds
        if(!(regToWrite + initialAddress > 8))
        {
            int byteTosend = 0;

            char outputBytes = regToWrite * 2; //how many bytes are being written

            sendData[6]=outputBytes;

            for(int i = 0, j=0; i<outputBytes; i+=2, j++)
            {
                //the value to set the channel mode ot
                sendData[7 + i] = 0x00;                      //High bits
                sendData[8 + i] = (char)controlMode[j];       //Low bits
            }

            byteTosend = outputBytes + 9;

            unsigned char receivedData[XBUFF_SIZE] = {0x0};

            int iResponse = 0;

            if(WriteToPort(sendData, byteTosend, receivedData, &iResponse))
            {
                bReturn = validateResponse(sendData,sizeof(sendData), receivedData,iResponse,
                                           Validator::EXPECTED_SIZE, 8,
                                           Validator::PARTIAL_COMPARE, 6);
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

    return bReturn;
}
