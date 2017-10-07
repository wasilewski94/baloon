/**
* @Author: Michał Kocon
* @Date:   09-01-2017
* @Last modified by:   Michał Kocon
* @Last modified time: 11-01-2017
*/


#include "hoperf_pi_driver.hpp"
#include "hoperf_structures.hpp"
#include <cstring>

using namespace skik::hoperf;

ArduinoDriver::ArduinoDriver(char* uart_path, uint8_t config, uint8_t sleep, uint8_t status, uint8_t reset) :
uart_path_(uart_path),
config_(config),
sleep_(sleep),
status_(status),
reset_(reset)
{
	fd_ = serialOpen(uart_path_.c_str(), 9600);
}


void ArduinoDriver::setUartBaudRate(uint32_t baud_rate){
    serialClose(fd_);
	serialOpen(uart_path_.c_str(), baud_rate);
}
void ArduinoDriver::writeToUart(const uint8_t byte){
    serialPutchar(fd_, byte);
}
void ArduinoDriver::writeToUart(const uint8_t* bytes, size_t length){
	char* buff = new char (length + 1);
	std::memcpy(buff, bytes, length);
	buff[length] = '\0';
    serialPuts(fd_, buff);
	delete[] buff;
}
void ArduinoDriver::writeToUart(const char* bytes){
    serialPuts(fd_, bytes);
}
void ArduinoDriver::readFromUart(uint8_t* dest, size_t length){
	int a=0;
    while(a<length){
		if (serialDataAvail(fd_)) {
			dest[a] = serialGetchar(fd_);
			++a;
		}
	}
}
void ArduinoDriver::readFromUart(char* dest, size_t length){
    readFromUart(reinterpret_cast<uint8_t*>(dest), length);
}
void ArduinoDriver::flushUart(){
    serialFlush(fd_);
}
uint8_t ArduinoDriver::checkUart(){
    return static_cast<uint8_t>(serialDataAvail(fd_));
}

void ArduinoDriver::setPinMode(PinType pin, PinMode mode){
    pinMode(getPinType(pin), getPinMode(mode));
}

void ArduinoDriver::writePin(PinType pin, Level level){
    digitalWrite(getPinType(pin), getPinLevel(level));
}

Level ArduinoDriver::readPin(PinType pin){
    int32_t lv = digitalRead(getPinType(pin));
    if(lv == HIGH)
        return Level::HI;
    else
        return Level::LO;
}
void ArduinoDriver::waitFor(uint64_t wait_time){
    delay(wait_time);
}

uint8_t ArduinoDriver::getPinType(PinType pin){
    uint8_t a_pin;
    switch(pin){
        case PinType::CONFIG:
            a_pin = config_;
            break;
        case PinType::SLEEP:
            a_pin = sleep_;
            break;
        case PinType::RESET:
            a_pin = reset_;
            break;
        case PinType::STATUS:
            a_pin = status_;
            break;
    }
    return a_pin;
}

uint8_t ArduinoDriver::getPinLevel(Level level){
    uint8_t a_level;
    switch(level){
        case Level::HI:
            a_level = HIGH;
            break;
        case Level::LO:
            a_level = LOW;
            break;
    }
    return a_level;
}

uint8_t ArduinoDriver::getPinMode(PinMode mode){
    uint8_t a_mode;
    switch(mode){
        case PinMode::IN:
            a_mode = INPUT;
            break;
        case PinMode::OUT:
            a_mode = OUTPUT;
            break;
    }
    return a_mode;
}
