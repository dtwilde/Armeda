#include "LibSerialPortWrapper.h"
daf ghdagdagf daerg+


/**
 * Class constructor
 *
 * Sets default parity to None, Baud Rate to 9600 and timeout to 100ms
 */
LibSerialPortWrapper::LibSerialPortWrapper()
    : m_sPort(nullptr), m_Timeout(100), m_parity(SP_PARITY_NONE), m_baudRate(WSBaudRates::Baud9600)
{
}

/**
 * Sets the baud rate and parity of the serial port. If the port is already opened
 * it must be closed first then reopened for the change to take effect
 *
 * @param baudRate The desired baudRate
 * @param parity The desired parity
 */
void LibSerialPortWrapper::SetBaudRate(WSBaudRates baudRate, sp_parity parity)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_baudRate = baudRate;
    m_parity = parity;
}

/**
 * Set the timeout for blocking reads of the serial port
 *
 * @param timeout The desired timeout
 */
void LibSerialPortWrapper::SetTimeOut(unsigned int timeout)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_Timeout = timeout;
}

/**
 * Returns the last error message from the serial port
 *
 *
 * @result The error message
 */
std::string LibSerialPortWrapper::Last_Error_Message() const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    char* sError = sp_last_error_message();
    std::string lastError = sError ? sError : "Unknown error";
    sp_free_error_message(sError);
    return lastError;
}

/**
 * Enumerates all the serial ports available
 *
 *
 * @result A vector of strings representing the serial ports
 */
std::vector<std::string> LibSerialPortWrapper::EnumeratePorts() const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    std::vector<std::string> vReturn;
    struct sp_port** port_list = nullptr;

    enum sp_return result = sp_list_ports(&port_list);
    if (result == SP_OK && port_list != nullptr)
    {
        for (int i = 0; port_list[i] != nullptr; ++i)
        {
            struct sp_port* port = port_list[i];
            const char* port_name = sp_get_port_name(port);
            if (port_name)
            {
                vReturn.emplace_back(port_name);
            }
        }
        sp_free_port_list(port_list);
    }

    return vReturn;
}

/**
 * Open the specified serial port
 *
 * @param port The name of the desired port to open acquired from EnumeratePorts()
 * @return Returns true if the port was successfully opened, false otherwise
 */
bool LibSerialPortWrapper::OpenPort(const std::string& port)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_sPort != nullptr)
    {
        ClosePort();  // Ensure any previously opened port is closed
    }

    sp_get_port_by_name(port.c_str(), &m_sPort);
    if (m_sPort == nullptr) return false;

    if (sp_open(m_sPort, SP_MODE_READ_WRITE) == SP_OK)
    {
        sp_set_baudrate(m_sPort, m_baudRate);
        sp_set_bits(m_sPort, 8);
        sp_set_parity(m_sPort, m_parity);
        sp_set_stopbits(m_sPort, 1);
        sp_set_flowcontrol(m_sPort, SP_FLOWCONTROL_NONE);

        return true;
    }

    sp_free_port(m_sPort);
    m_sPort = nullptr;
    return false;
}

/**
 * Performs non-blocking write to the serial port
 *
 * @param buf The data to be written to the port
 * @param count The size of the data
 * @return Number of bytes written
 */
int LibSerialPortWrapper::NonBlocking_Write(const void* buf, size_t count)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    int iReturn = 0;

    if (buf != NULL)
        iReturn = sp_nonblocking_write(m_sPort, buf, count);

    return iReturn;
}

/**
 * Performs blocking read from the serial port
 *
 * @param buf A buffer to hold the data read from the port
 * @param count The size of the data read
 * @return Number of bytes read
 */
int LibSerialPortWrapper::Blocking_Read(void* buf, size_t count)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    int iReturn = 0;

    if (buf != NULL)
        iReturn = sp_blocking_read(m_sPort, buf, count, m_Timeout);

    return iReturn;
}

/**
 * Closes the serial port
 */
void LibSerialPortWrapper::ClosePort()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_sPort)
    {
        sp_close(m_sPort);
        sp_free_port(m_sPort);
        m_sPort = nullptr;
    }
}
