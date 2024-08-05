
#ifndef LibSerialPortWrapper_h
#define LibSerialPortWrapper_h

#include <mutex>
#include <vector>
#include <string>
#include "libserialport.h"
#include "WS_Device.h"

/**
 * A thread safe wrapper class for the libserialport library to make sharing the serial port
 * among WS_Device classes easier.
 *
 */

class LibSerialPortWrapper
{
public:
    LibSerialPortWrapper();

    void SetBaudRate(WSBaudRates baudRate, sp_parity parity);
    void SetTimeOut(unsigned int timeout);
    std::string Last_Error_Message() const;
    std::vector<std::string> EnumeratePorts() const;
    bool OpenPort(const std::string& port);
    int NonBlocking_Write(const void* buf, size_t count);
    int Blocking_Read(void* buf, size_t count);
    void ClosePort();

private:
    mutable std::mutex m_mutex;  // Mutex for thread safety
    sp_port* m_sPort;
    unsigned int m_Timeout;
    sp_parity m_parity;
    WSBaudRates m_baudRate;
};

#endif
