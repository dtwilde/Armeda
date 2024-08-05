#ifndef WS_AnalogInput_h
#define WS_AnalogInput_h

#include "WS_Device.h"
#include <vector>

enum AnalogIOChannelType
{
    Volts_0to5        = 0,
    Volts_1to5        = 1,
    Current_0to20     = 2,
    Current_4to20     = 3,
    DirectValueCode   = 4,
};



/**
 * Class that contains all the functions to control a 8 Channel Analog Input Device
 *
 */
class WS_AnalogInput : public WS_Device
{

public:

    WS_AnalogInput(LibSerialPortWrapper * sPort);

    bool ReadAnalogInput(unsigned char deviceAddress,unsigned char initialAddress, unsigned char registerCount, std::vector<float> & vReturnData);

    bool ReadChannelDataType(unsigned char deviceAddress,unsigned char initialAddress, unsigned char registerCount, std::vector<AnalogIOChannelType> & vReturnData);

    bool SetSingleChannelDataType(unsigned char iDeviceAddress, unsigned char address, AnalogIOChannelType cType);

    bool SetMultipleChannelDataType(unsigned char iDeviceAddress, unsigned char initialAddress, std::vector<AnalogIOChannelType> vType);
};

#endif
