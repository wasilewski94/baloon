/**
* @Author: Michał Kocon
* @Date:   10-01-2017
* @Last modified by:   Michał Kocon
* @Last modified time: 10-01-2017
*/



#ifndef HOPERF_DRIVER_HPP
#define HOPERF_DRIVER_HPP

#include "hoperf_structures.hpp"
#include <stdint.h>
#include <stddef.h>


namespace skik {
namespace hoperf {
class DriverInterface{
public:
    /**
    Sets baud rate of UART
    */
    virtual void setUartBaudRate(uint32_t baud_rate) = 0;
    /**
    Writes bytes to UART
    */
    virtual void writeToUart(const uint8_t byte) = 0;
    virtual void writeToUart(const uint8_t* bytes, size_t length) = 0;
    virtual void writeToUart(const char* string) = 0;

    /**
    Reads from Uart()
    */
    virtual void readFromUart(uint8_t* dest, size_t length) = 0;
    virtual void readFromUart(char* dest, size_t length) = 0;
    /**
    Waits till outgoing buffer is empty
    */
    virtual void flushUart() = 0;
    /**
    Checks if data for read is available
    */
    virtual uint8_t checkUart() = 0;
    /**
    Sets pin mode
    */
    virtual void setPinMode(PinType pin, PinMode mode) = 0;

    /**
    Writes logic level to specified pin_type
    */
    virtual void writePin(PinType pin, Level level) = 0;

    /**
    Reads pin level
    */
    virtual Level readPin(PinType pin) = 0;

    /**
    Waits for specified time in miliseconds
    */
    virtual void waitFor(uint64_t wait_time) = 0;
};
}
}

#endif //HOPERF_DRIVER_HPP
