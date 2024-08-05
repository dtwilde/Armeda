
#ifndef WS_Device_h
#define WS_Device_h

#include <libserialport.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <cstdarg>

//The max size of the buffer for sending/receiving data
#define XBUFF_SIZE 255

//supported baud rates for device
enum WSBaudRates
{
    Baud4800   = 4800,
    Baud9600   = 9600,
    Baud19200  = 19200,
    Baud38400  = 38400,
    Baud57600  = 57600,
    Baud115200 = 115200,
};

// Forward declaration
class LibSerialPortWrapper;

//validation tests to run on received data
enum Validator {
    IDENTICAL_MSG       = 1,
    ADDRESS_MATCH       = 2,
    EXPECTED_SIZE       = 3,
    MINIMUM_SIZE        = 4,
    PARTIAL_COMPARE     = 5,
    VALIDATE_TERMINATOR = 0xFFFF,
};

#define validateResponse(sentData, sendDataSize, receivedData, response, ...) \
    myValidator(sentData, sendDataSize, receivedData, response, __VA_ARGS__, Validator::VALIDATE_TERMINATOR)

/**
 * Base class that contains all the functions common to all WaveShare RTU Devices
 *
 */

class WS_Device
{

public:

    WS_Device(LibSerialPortWrapper * libSerialPort);

    bool SetBaudRate(unsigned char address, WSBaudRates baudRate, sp_parity portParity);

    bool ReadDeviceAddress(unsigned char & address);

    bool ReadSoftwareVersion(unsigned char address, float & fVersion);

    bool SetDeviceAddress(unsigned char currentAddress, unsigned char newAddress);

    void SetPort(LibSerialPortWrapper * port);

    bool WriteToPort(unsigned char * message, int messageSize, unsigned char * response=NULL,int * responseSize=NULL);

    std::string GetLastError(void);

    void GetLastTX(char * lastTx, int * sizeofTx);
    void GetLastRX(char * lastRx, int * sizeofRx);

protected:

    LibSerialPortWrapper * m_sPort;

    int m_waitTimeout;

    std::string m_LastError;

    char m_lastTx[XBUFF_SIZE];
    char m_lastRx[XBUFF_SIZE];

    int m_sizeofTx;
    int m_sizeofRx;

    void setSerialPortErrorMsg(void);

    bool myValidator(unsigned char *sentData, unsigned int sendDataSize, unsigned char *receivedData, int response, ...);

};

#endif
