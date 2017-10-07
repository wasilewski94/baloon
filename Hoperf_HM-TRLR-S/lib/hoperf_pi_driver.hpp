/**
* @Author: Michał Kocon
* @Date:   09-01-2017
* @Last modified by:   Michał Kocon
* @Last modified time: 11-01-2017
*/



#ifndef HOPERF_ARDUINO_DRIVER_HPP_
#define HOPERF_ARDUINO_DRIVER_HPP_

#include <stdint.h>
#include "wiringPi.h"
#include "wiringSerial.h"
#include "hoperf_driver.hpp"
#include <stddef.h>
#include <string>

namespace skik {
namespace hoperf {
class ArduinoDriver : public DriverInterface{
public:
    /**
    Contructor defines pins for specific functions
    */
    ArduinoDriver(char* uart_path, uint8_t config, uint8_t sleep, uint8_t status, uint8_t reset);
    /**
    Sets baud rate of UART
    */
    virtual void setUartBaudRate(uint32_t baud_rate);

    /**
    Writes bytes to UART
    */
    virtual void writeToUart(const uint8_t byte);
    virtual void writeToUart(const uint8_t* bytes, size_t length);
    virtual void writeToUart(const char* string);
    /**
    Reads from Uart()
    */
    virtual void readFromUart(uint8_t* dest, size_t length);
    virtual void readFromUart(char* dest, size_t length);
    /**
    Waits till outgoing buffer is empty
    */
    virtual void flushUart();
    /**
    Checks if data for read is available and returns hom many bytes.
    */
    virtual uint8_t checkUart();
    /**
    Sets pin mode
    */
    virtual void setPinMode(PinType pin, PinMode mode);

    /**
    Writes logic level to specified pin_type
    */
    virtual void writePin(PinType pin, Level level);

    /**
    Reads pin level
    */
    virtual Level readPin(PinType pin);
    /**
    Waits for specified time
    */
    virtual void waitFor(uint64_t wait_time);
private:
    uint8_t getPinType(PinType pin);
    uint8_t getPinLevel(Level level);
    uint8_t getPinMode(PinMode mode);
	
	int fd_;
	std::string uart_path_;
    uint8_t config_;
    uint8_t sleep_;
    uint8_t status_;
    uint8_t reset_;
};
}}

#endif //HOPERF_ARDUINO_DRIVER_HPP_
