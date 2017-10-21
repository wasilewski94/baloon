/**
* @Date:   2017-01-09T23:19:48+01:00
* @Last modified time: 11-01-2017
*/

#include "hoperf.hpp"
#include "hoperf_structures.hpp"
#include <string.h>
//#include "Arduino.h"

using namespace skik::hoperf;

RadioModule::RadioModule(DriverInterface& driver, size_t uart_baud_rate) :
driver_(driver){
    driver_.setPinMode(PinType::RESET, PinMode::OUT);
    driver_.setPinMode(PinType::CONFIG, PinMode::OUT);
    driver_.setPinMode(PinType::SLEEP, PinMode::OUT);
    driver_.setPinMode(PinType::STATUS, PinMode::IN);
    driver_.writePin(PinType::CONFIG, Level::HI);
    driver_.writePin(PinType::SLEEP, Level::LO);

    driver_.writePin(PinType::RESET, Level::LO);
    driver_.waitFor(2);
    driver_.writePin(PinType::RESET, Level::HI);

    driver_.waitFor(13);
    driver_.setUartBaudRate(uart_baud_rate);
    driver_.flushUart();
}
//RadioModule::~RadioModule(){
//}
void RadioModule::writeCommand(const char* command, const char* param) const {
    driver_.writePin(PinType::CONFIG, Level::LO);
    driver_.waitFor(6);
    driver_.writeToUart("AT+");
    driver_.writeToUart(command);
    driver_.writeToUart("=");
    driver_.writeToUart(param);
    driver_.writeToUart("\n");
    driver_.writePin(PinType::CONFIG, Level::HI);
    driver_.waitFor(5);
    /*if(reply_status != nullptr){C
        int i = 0;
        while(driver_.checkUart()){
            driver.readFromUart(uint8_t *dest, size_t length)
        }
    }*/
    driver_.writePin(PinType::CONFIG, Level::HI);
}
bool RadioModule::testModule(){
    driver_.writePin(PinType::CONFIG, Level::LO);
    driver_.waitFor(6);
    driver_.writeToUart("AT\n");
    driver_.flushUart();
    char buffer[10];
    driver_.readFromUart(buffer, 10);
    driver_.writePin(PinType::CONFIG, Level::HI);
    driver_.waitFor(5);
    if(strcmp(buffer, "OK"))
        return true;
    else
        return false;
}
void RadioModule::writeData(const uint8_t data) const{
    driver_.writeToUart(data);
    driver_.writeToUart("\n");
    driver_.flushUart();
}

void RadioModule::writeData(const uint8_t* data, size_t length) const{
    driver_.writeToUart(data, length);
    driver_.writeToUart("\n");
    driver_.flushUart();
}
void RadioModule::writeData(const char* data) const{
    driver_.writeToUart(data);
    driver_.writeToUart("\n");
    driver_.flushUart();
}
void RadioModule::readData(uint8_t* dest, size_t length) const{
    uint8_t data_len = driver_.checkUart();
    if(length-1 <= data_len){
        driver_.readFromUart(dest, length);
    }
    else{
        driver_.readFromUart(dest, data_len);
    }
}
void RadioModule::readData(char* dest, size_t length) const{
    uint8_t data_len = driver_.checkUart();
    if(length <= data_len){
        driver_.readFromUart(dest, length);
        dest[length-1] = 0;
    }
    else{
        driver_.readFromUart(dest, data_len);
        dest[data_len] = 0;
    }
}

void RadioModule::reset() const {
    driver_.writePin(PinType::RESET, Level::LO);
    //while(driver_.readPin(PinType::STATUS) == Level::HI);
    driver_.waitFor(2);
    driver_.writePin(PinType::RESET, Level::HI);
    //while(driver_.readPin(PinType::CONFIG) == Level::LO);
}
