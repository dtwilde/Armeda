#ifndef WS_AnalogOutput_h
#define WS_AnalogOutput_h

#include "WS_Device.h"
#include <vector>

//States of relays
enum DigitalIO_State
{
    ON   = 0xFF,
    OFF  = 0x00,
    FLIP = 0x55,
};

enum DigitalIO_Command
{
    FlashOn  = 0x02,
    FlashOff = 0x04,
};

enum Digital_IO_ControlMode
{
    Normal  = 0x0000,
    Linkage = 0x0001,
    Flip    = 0x0002,
};

/**
 * Class that contains all the functions to control a 8 Channel Analog Output Device
 *
 */


class WS_Digital_IO : public WS_Device
{

public:

    WS_Digital_IO(LibSerialPortWrapper * lbSerialPort);

    bool ControlSingleOuputChannel(unsigned char deviceAddress,unsigned char address, DigitalIO_State value);

    bool AllOutputChannelControl(unsigned char deviceAddress, DigitalIO_State command);

    bool ReadOutputChannelStatus(unsigned char deviceAddress, std::vector<bool> & channelOutput);

    bool WriteOutputChannelStatus(unsigned char deviceAddress, std::vector<bool> & channelStatus);

    bool OutputChannelFlashOnOff(unsigned char deviceAddress, DigitalIO_Command command, unsigned char outputChannelAddress, unsigned int intervalTime);

    bool ReadInputChannelStatus(unsigned char deviceAddress, std::vector<bool> & channelStatus);

    bool ReadOutputChannelControlMode(unsigned char deviceAddress, unsigned char initalAddress, unsigned char registerCount, std::vector<Digital_IO_ControlMode> & channelMode);

    bool SetSingleOutputChannelControlMode(unsigned char deviceAddress,unsigned char outputChannelAddress, Digital_IO_ControlMode controlMode);

    bool SetMultipleOutputChannelControlMode(unsigned char deviceAddress,unsigned char initialAddress, std::vector<Digital_IO_ControlMode> controlMode);
};

#endif
