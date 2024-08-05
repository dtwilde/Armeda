#include "WS_Device.h"
#include "LibSerialPortWrapper.h"
#include "crc16.c"
#include <ctime>
#include <sstream>

uint16_t crc_modbus( const unsigned char *input_str, size_t num_bytes ) ;


/**
 * Class constructor
 *
 * @param lbSerialPort A pointer to an LibSerialPortWrapper object. This object can be shared between
 *                     multiple instances of WS_Device classes
 */

WS_Device::WS_Device(LibSerialPortWrapper * libSerialPort)
          :m_sPort(libSerialPort)
{
    m_sizeofRx = 0;
    m_sizeofTx = 0;
}


/**
 * Returns the last error encountered
 *
 * @result The error
 */
std::string WS_Device::GetLastError(void)
{
    return m_LastError;
}

/**
 * Returns the last transmitted data
 *
 * @param lastTx A pointer to an array to copy the data into. Must be of size XBUFF_SIZE
 * @param lastTx A pointer to a integer to store the size of the data
 */
void WS_Device::GetLastTX(char * lastTx, int * sizeofTx)
{
    if(NULL!=lastTx && sizeofTx!=NULL)
    {
        memcpy(lastTx,m_lastTx,XBUFF_SIZE);
        *sizeofTx = m_sizeofTx;
    }
}


/**
 * Returns the last received data
 *
 * @param lastTx A pointer to an array to copy the data into. Must be of size XBUFF_SIZE
 * @param lastTx A pointer to a integer to store the size of the data
 */
void WS_Device::GetLastRX(char * lastRx, int*  sizeofRx)
{
    if(NULL!=lastRx)
    {
        memcpy(lastRx,m_lastRx,XBUFF_SIZE);
        *sizeofRx = m_sizeofRx;
    }
}

/**
 * Sets a new port for the class to use
 *
 * @param theory The new port to use
 */
void WS_Device::SetPort(LibSerialPortWrapper * port)
{
    m_sPort = port;
}

/**
 * Writes data to the serial port and returns TRUE if sucessfull
 *
 * @param message The data to send to the serial port
 * @param messageSize The size of the data to send to the serial port
 * @param response A pointer to the char array to store the result in
 *                 the array must be the size of XBUFF_SIZE
 * @param responseSize The amount of data read from the serial port
 *                     or a negative error code
 * @result The result of the write attempt
 */

bool WS_Device::WriteToPort(unsigned char *message, int messageSize, unsigned char *response, int *responseSize)
{
    if (m_sPort == nullptr) return false; // Ensure there's a port to write to

    // Add the CRC to the message to be sent, checking message size to avoid out of bounds errors
    if (messageSize > 2)
    {
        uint16_t iCrc = crc_modbus(message, messageSize - 2);
        message[messageSize - 2] = iCrc & 0xff;
        message[messageSize - 1] = (iCrc >> 8) & 0xff;
    }

    // Store the last written data
    memcpy(m_lastTx, message, messageSize);
    m_sizeofTx = messageSize;

    // Write to the port
    int sendResult = m_sPort->NonBlocking_Write(message, messageSize);

    if (sendResult != messageSize) // Error writing
    {
        char *sError = sp_last_error_message();
        m_LastError = std::string(sError);
        sp_free_error_message(sError);
        return false;
    }

    // Allocate a buffer to receive data
    unsigned char buf[XBUFF_SIZE] = {0x00};
    int readResult = m_sPort->Blocking_Read(&buf, XBUFF_SIZE);

    // Store the last read data
    memcpy(m_lastRx, buf, XBUFF_SIZE);
    m_sizeofRx = readResult;

    if (readResult <= 0) // Error reading
    {
        memset(m_lastRx, 0, XBUFF_SIZE); // Wipe the last data received
        char *sError = sp_last_error_message();
        m_LastError = std::string(sError);
        sp_free_error_message(sError);
        return false;
    }

    // Return what was read from the port in the function parameters
    if (response != nullptr && responseSize != nullptr)
    {
        memcpy(response, buf, XBUFF_SIZE);
        *responseSize = readResult;
    }

    // Verify the CRC is correct on the response
    if (readResult > 2)
    {
        uint16_t iCrc = crc_modbus(response, readResult - 2);
        int high_byte = (iCrc >> 8) & 0xff;
        int low_byte = iCrc & 0xff;
        char result_highByte = buf[readResult - 1];
        char result_lowByte = buf[readResult - 2];

        if (result_highByte == high_byte && result_lowByte == low_byte)
        {
            return true;
        }
        else
        {
            std::stringstream stream;
            stream << "Invalid CRC. Expected 0x" << std::hex << low_byte << " 0x" << high_byte
                   << " Received 0x" << std::hex << (int)result_lowByte << " 0x" << (int)result_highByte;
            m_LastError = stream.str();
        }
    }
    else
    {
        m_LastError = "Invalid CRC Response";
    }

    return false;
}

/**
 * Changes the baud rate of a specific device
 *
 * @param device The address of the device to control
 * @param baudRate The new baud rate for the device to use
 * @param portParity The new parity for the device to use
 * @result The result of the changing the baud rate
 */
bool WS_Device::SetBaudRate(unsigned char device, WSBaudRates baudRate, sp_parity portParity)
{
    unsigned char sendData[8] = {0x00};
    unsigned char receivedData[XBUFF_SIZE] = {0x00};
    int iResponse = 0;

    sendData[0] = device;
    sendData[1] = 0x06;
    sendData[2] = 0x20;
    sendData[3] = 0x00;

    // Set parity
    switch (portParity)
    {
        case sp_parity::SP_PARITY_EVEN: sendData[4] = 0x01; break;
        case sp_parity::SP_PARITY_ODD:  sendData[4] = 0x02; break;
        case sp_parity::SP_PARITY_NONE: sendData[4] = 0x00; break;
    }

    // Set baud rate
    switch (baudRate)
    {
        case WSBaudRates::Baud4800:   sendData[5] = 0x00; break;
        case WSBaudRates::Baud9600:   sendData[5] = 0x01; break;
        case WSBaudRates::Baud19200:  sendData[5] = 0x02; break;
        case WSBaudRates::Baud38400:  sendData[5] = 0x03; break;
        case WSBaudRates::Baud57600:  sendData[5] = 0x04; break;
        case WSBaudRates::Baud115200: sendData[5] = 0x05; break;
        default:
            m_LastError = "Invalid Baud Rate Specified";
            return false;
    }

    // Write to the port and validate response
    if (WriteToPort(sendData, 8, receivedData, &iResponse))
    {
        // The device should respond with the identical message sent for a successful write
        return validateResponse(receivedData, iResponse, sendData, 8, true);
    }

    return false;
}


/**
 * Changes the address of the specified device
 *
 * @param currentAddress The current address of the device
 * @param newAddress The new address for the device
 * @result The result of setting the device address
 */
bool WS_Device::SetDeviceAddress(unsigned char currentAddress, unsigned char newAddress)
{
    unsigned char sendData[8] = {0x00};
    unsigned char receivedData[XBUFF_SIZE] = {0x00};
    int iResponse = 0;

    // Prepare the data to be sent
    sendData[0] = currentAddress;
    sendData[1] = 0x06;
    sendData[2] = 0x40;
    sendData[3] = 0x00;
    sendData[4] = 0x00;
    sendData[5] = newAddress;

    // Write to the port and validate response
    if (WriteToPort(sendData, 8, receivedData, &iResponse))
    {
        // The device should respond with the identical message sent for a successful write
        return validateResponse(receivedData, iResponse, sendData, 8, true);
    }

    return false;
}


/**
 * Sends out a broadcast message on the modbus network to get the
 * current address of the device connected to it. Since all devices
 * will respond to this request at the same time This will ONLY
 * work with 1 device connected at a time
 *
 * @param address A reference to the device found
 * @result The result of the read attempt
 */
bool WS_Device::ReadDeviceAddress(unsigned char & address)
{
    bool bReturn = false;

    int iResponse = 0;
    unsigned char receivedData[XBUFF_SIZE] = {0x00};
    unsigned char sendData[8] = {0x00};

    sendData[0]=0x00;
    sendData[1]=0x03;
    sendData[2]=0x40;
    sendData[3]=0x00;
    sendData[4]=0x00;
    sendData[5]=0x01;

    if(WriteToPort(sendData, 8, receivedData, &iResponse))
    {
        if(iResponse > 1)
        {
            address = receivedData[0];

            bReturn = true;
        }
    }

    return bReturn;
}

/**
 * Reads the software version of the given device
 *
 * @param address The device address to quiry
 * @param fVersion A reference to store the result
 * @result The result of the read attempt
 */
bool WS_Device::ReadSoftwareVersion(unsigned char address, float & fVersion)
{
    bool bReturn = false;

    int iResponse = 0;
    unsigned char receivedData[XBUFF_SIZE] = {0x00};
    unsigned char sendData[8] = {0x00};

    sendData[0]=address;
    sendData[1]=0x03;
    sendData[2]=0x80;
    sendData[3]=0x00;
    sendData[4]=0x00;
    sendData[5]=0x01;

    if(WriteToPort(sendData, 8, receivedData, &iResponse))
    {
        if(iResponse>=6)
        {
             fVersion = receivedData[4] / 100;
             bReturn = true;
        }
    }

    return bReturn;
}



/**
 * Utility function for validating responses from the device
 *
    @param  sentData The data sent
    @param  sendDataSize The size of the sent data
    @param  receivedData  The data received
    @param  response The response from reading the data
    @param  (...) Variadic arguments from emun Validator
                  validation test are carried out in the order the
                  arguments are passed to the function

                  When using EXPECTED_SIZE the argument that follows must be the size to check for
                  When using MINIMUM_SIZE  the argument that follows must be the size to check for
                  When using PARTIAL_COMPARE the argument that follows must be the first bytes
                                             to check for a partial match
    @return The result of the validation check
*/

bool WS_Device::myValidator(unsigned char *sentData, unsigned int sentDataSize, unsigned char *receivedData, int response, ...)
{
    // Check for valid arguments; response should be greater than zero if a read was successful
    if (!sentData || sentDataSize <= 0 || !receivedData || response < 0)
        return false;

    bool bReturn = true;
    va_list args;
    va_start(args, response);

    // Continue parsing arguments until the end terminator argument is reached
    //or a bad validation occured
    int validatorArg;
    while ((validatorArg = va_arg(args, int)) != Validator::VALIDATE_TERMINATOR && bReturn==true)
    {
        switch (validatorArg)
        {
            /*
             * Validator for checking the addresses sent/received are the same
             */
            case ADDRESS_MATCH:
            {
                if (sentDataSize > 0 && receivedData[0] != sentData[0])
                {
                    std::stringstream errorStream;
                    errorStream << "Invalid device address received in response. Expected 0x"
                                << std::hex << static_cast<int>(sentData[0])
                                << " Received: 0x"
                                << std::hex << static_cast<int>(receivedData[0]);

                    m_LastError = errorStream.str();
                    bReturn = false;
                }
                else
                {
                    bReturn = true;
                }
                break;
            }

            /*
             * Validator for checking if messages are identical
             */
            case IDENTICAL_MSG:
            {
                // Make sure the sizes are the same first
                if (sentDataSize != response)
                {
                    m_LastError = "Response size mismatch";
                    break;
                }

                bool isIdentical = true;
                // Compare the sent and received data
                for (unsigned int i = 0; i < sentDataSize; ++i)
                {
                    if (sentData[i] != receivedData[i])
                    {
                        isIdentical = false;
                        break;
                    }
                }

                if (!isIdentical)
                {
                    std::stringstream streamSentData, streamReceivedData;

                    for (unsigned int i = 0; i < sentDataSize; ++i)
                    {
                        streamSentData << "0x" << std::hex << static_cast<int>(sentData[i]) << " ";
                    }

                    for (int i = 0; i < response; ++i)
                    {
                        streamReceivedData << "0x" << std::hex << static_cast<int>(receivedData[i]) << " ";
                    }

                    m_LastError = "Invalid response received. Expecting " + streamSentData.str() +
                                  " Received " + streamReceivedData.str();
                    bReturn = false;
                }
                else
                {
                    bReturn = true;
                }
                break;
            }

            /*
             * Validator for checking if the received data size matches what was expected
             */
            case EXPECTED_SIZE:
            {
                int expectedSize = va_arg(args, int);

                if (response != expectedSize)
                {
                    m_LastError = "Invalid response received. Expecting " + std::to_string(expectedSize) +
                                  " bytes. Received " + std::to_string(response);
                    bReturn = false;
                }
                else
                {
                    bReturn = true;
                }
                break;
            }


            /*
             * Validator for checking the minimumn size of the message
             */
            case MINIMUM_SIZE:
            {
                int minSize = va_arg(args, int);

                if (response < minSize)
                {
                    m_LastError = "Invalid response received. Expecting at least " + std::to_string(minSize) +
                                  " bytes. Received " + std::to_string(response);
                    bReturn = false;
                }
                else
                {
                    bReturn = true;
                }
                break;
            }


            /*
             * Validator for doing a partial compare on the first specified bytes of data
             */
            case PARTIAL_COMPARE:
            {
                unsigned int compareVal = va_arg(args, int);

                if (compareVal > 0 && response >= compareVal && sentDataSize >= compareVal)
                {
                    bool isIdentical = true;

                    // Compare the sent and received data
                    for (unsigned int i = 0; i < compareVal; ++i)
                    {
                        if (sentData[i] != receivedData[i])
                        {
                            isIdentical = false;
                            break;
                        }
                    }

                    if (isIdentical)
                    {
                        bReturn = true;
                    }
                    else
                    {
                        m_LastError = "Invalid response received. Expecting first " + std::to_string(compareVal) +
                                      " bytes to match sent data";
                        bReturn = false;
                    }
                }
                break;
            }

            default:
                m_LastError = "Unknown validator argument";
                bReturn = false;
                break;
        }
    }

    va_end(args);
    return bReturn;
}
