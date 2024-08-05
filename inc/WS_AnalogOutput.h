#ifndef WS_AnalogOutput_h
#define WS_AnalogOutput_h

#include "LibSerialPortWrapper.h"
#include "WS_Device.h"
#include <vector>

/**
 * Class that contains all the functions to control a 8 Channel Analog Output Device
 *
 */


class WS_AnalogOutput : public WS_Device
{

public:

    WS_AnalogOutput(LibSerialPortWrapper * sPort);

    bool SetSingleChannelOutput(unsigned char deviceAddress,unsigned char address, unsigned int value);

    bool SetMultipleChannelOutput(unsigned char deviceAddress, unsigned char initialAddress, std::vector<unsigned int> & channelOutput);

    bool ReadChannelOutput(unsigned char deviceAddress, unsigned char initialAddress, unsigned char registerCount, std::vector<unsigned int> & channelOutput);

};

#endif
