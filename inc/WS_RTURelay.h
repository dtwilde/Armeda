
#ifndef WS_RTURelay_h
#define WS_RTURelay_h

#include "WS_Device.h"
#include <vector>

//States of relays
enum RelayState
{
    RelayOff  = 0x00,
    RelayOn   = 0xFF,
    RelayFlip = 0x55,
};

//Support relay board sizes
enum RTUChannelSize
{
    Channel_8  = 8,
    Channel_16 = 16,
    Channel_32 = 32,
};

/**
 * Contains the specific command functions for RTU Relay devices
 *
 */
class WS_RTURelay : public WS_Device
{

private:

    void generateRelayVector(unsigned char receivedByte, std::vector<RelayState> * vState);

public:
    WS_RTURelay(LibSerialPortWrapper * libSerialPort);

    bool ControlSingleRelay(unsigned char deviceAddress,unsigned char relay, RelayState rState);

    bool ControlAllRelays(unsigned char deviceAddress, RelayState rState);

    std::vector<RelayState> ReadStatesofRelays(unsigned char iDeviceAddress,RTUChannelSize channelSize);

    bool WriteStatesofRelays(unsigned char deviceAddress, std::vector<RelayState> vStates);

    bool WriteStatesofRelays(unsigned char deviceAddress, RTUChannelSize channelSize, unsigned int statusByte);

    bool RelayFlashOnOff(unsigned char deviceAddress, unsigned char iRelay, unsigned char iInterval, bool bFlashOn);

};

#endif
