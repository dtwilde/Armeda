#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits> // For std::numeric_limits
#include "libserialport.h"
#include "WS_RTURelay.h"
#include "LibSerialPortWrapper.h"

using namespace std;

void printHex(const char* array, size_t size);

int main()
{
    LibSerialPortWrapper sPort;

    int selectedPort = 0;
    int deviceAddress = 0;
    int relayChannel = 0;
    int discoveredPorts = 0;
    int relayState = 0;

    WS_RTURelay relayBoard(&sPort);

    // Get all available ports
    vector<string> ports = sPort.EnumeratePorts();
    discoveredPorts = ports.size();

    cout << "Discovered " << discoveredPorts << " ports" << endl << endl;

    if (discoveredPorts == 0)
    {
        cout << "No ports discovered. Exiting." << endl;
        return 1; // Return non-zero to indicate error
    }

    // Print the available ports
    for (int i = 0; i < discoveredPorts; i++)
    {
        cout << (i + 1) << " : " << ports[i] << endl;
    }

    // Select a port
    while (true)
    {
        cout << endl << "Enter port to use : ";
        cin >> selectedPort;

        // Validate the port selection
        if (cin.fail() || selectedPort < 1 || selectedPort > discoveredPorts)
        {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid port number. Please enter a number between 1 and " << discoveredPorts << "." << endl;
        }
        else
        {
            break; // Valid input, exit loop
        }
    }

    string strPort = ports[selectedPort - 1];

    if (!sPort.OpenPort(strPort))
    {
        cout << "Failed to open port: " << sPort.Last_Error_Message() << endl;
        return 1; // Return non-zero to indicate error
    }
    else
    {
        cout << "Port " << strPort << " opened" << endl;
    }

    // Select a device address
    while (true)
    {
        cout << "Enter device address (1-255): ";
        cin >> deviceAddress;

        // Validate the device address
        if (cin.fail() || deviceAddress < 1 || deviceAddress > 255)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid address. Please enter a number between 1 and 255." << endl;
        }
        else
        {
            break; // Valid input, exit loop
        }
    }

    // Main loop for relay control
    while (true)
    {
        // Select a relay channel
        while (true)
        {
            cout << "Enter relay channel (1-8): ";
            cin >> relayChannel;

            // Validate the relay channel
            if (cin.fail() || relayChannel < 1 || relayChannel > 8)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 8." << endl;
            }
            else
            {
                relayChannel--; // Convert to 0-based index
                break; // Valid input, exit loop
            }
        }

        // Select relay state
        while (true)
        {
            cout << "Enter 1 for On, 0 for Off: ";
            cin >> relayState;

            // Validate the relay state
            if (cin.fail() || (relayState != 0 && relayState != 1))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter 1 for On or 0 for Off." << endl;
            }
            else
            {
                break; // Valid input, exit loop
            }
        }

        // Control the relay
        bool bResult = (relayState == 1)
            ? relayBoard.ControlSingleRelay(deviceAddress, relayChannel, RelayState::RelayOn)
            : relayBoard.ControlSingleRelay(deviceAddress, relayChannel, RelayState::RelayOff);

        char sentData[XBUFF_SIZE] = { 0x00 };
        char receivedData[XBUFF_SIZE] = { 0x00 };
        int txSize = 0;
        int rxSize = 0;

        relayBoard.GetLastTX(sentData, &txSize);
        relayBoard.GetLastRX(receivedData, &rxSize);

        cout << endl << "Write to comm port " << selectedPort << " Device [" << deviceAddress
            << "] Relay [" << (relayChannel + 1) << "]";

        if (bResult)
        {
            cout << " Succeeded" << endl << endl;
        }
        else
        {
            cout << " Failed: " << relayBoard.GetLastError() << endl;
        }

        cout << "Sent ";
        printHex(sentData, txSize);

        cout << "Received ";
        printHex(receivedData, rxSize);

        cout << endl;

        relayChannel = -1; // Reset relay channel for the next iteration
    }

    return 0;
}



// Function to print hexadecimal representation of data
void printHex(const char* array, size_t size)
{
    cout << ": ";
    for (size_t i = 0; i < size; ++i)
    {
        cout << "0x" << hex << setfill('0') << setw(2) << static_cast<int>(static_cast<unsigned char>(array[i]));
        if (i < size - 1)
        {
            cout << " "; // Space between hexadecimal values
        }
    }
    cout << endl;
}