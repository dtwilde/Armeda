
#include <QVector>
#include "WS_Device.h"

#ifndef WS_RTURelay_h
#define WS_RTURelay_h

enum RelayState
{
    RelayOff  = 0,
    RelayOn   = 1,
    RelayFlip = 3,
};

class WS_RTURelay : WS_Device
{

private:


    int m_iChannelSize;

public:

    WS_RTURelay(int iChannelSize, QMutex &mSerialPortMutex, QSerialPort &sPort, int iWaitTimeout);

    bool ControlSingleRelay(int iDeviceAddress,int iRelay, RelayState rState);

    bool ControlAllRelays(int iDeviceAddress, RelayState rState);

    QVector<RelayState> ReadStatesofRelays(int iDeviceAddress);

    bool WriteStatesofRelays(int iDeviceAddress, QVector<RelayState> vStates);

    bool WriteStatesofRelays(int iDeviceAddress, int iStatusByte);

    bool RelayFlashOnOff(int iDeviceAddress, int iRelay, int iInterval, bool bFlashOn);
};

#endif
