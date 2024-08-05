#ifndef WS_AnalogInput_h
#define WS_AnalogInput_h

#include "WS_Device.h"

#include <QVector>

enum ChannelType
{
    Volts_0to5        = 0,
    Volts_1to5        = 1,
    Current_0to20     = 2,
    Current_4to20     = 3,
    DirectValueCode   = 4,
};

class WS_AnalogInput : WS_Device
{

private:


    int m_iChannelSize;

public:

    WS_AnalogInput(QMutex &mSerialPortMutex, QSerialPort &sPort, int iWaitTimeout);

    bool ReadAnalogInput(int iDeviceAddress,int iInitialAddress, int iRegisterCount, QVector<float> & vReturnData);

    bool ReadChannelDataType(int iDeviceAddress,int iAddress, int i, QVector<unsigned short> & vReturnData);

    bool SetSingleChannelDataType(int iDeviceAddress, int iAddress, ChannelType cType);

    bool SetMultipleChannelDataType(int iDeviceAddress, int iInitialAddress, int iRegisterCount, QVector<ChannelType> vType);
};

#endif
