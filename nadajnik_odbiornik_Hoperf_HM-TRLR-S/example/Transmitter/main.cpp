/**
* @Author: Michał Kocon
* @Date:   10-01-2017
* @Filename: main.cpp
* @Last modified by:   Michał Kocon
* @Last modified time: 11-01-2017
*/



#include "Arduino.h"
#include "hoperf.hpp"
#include "hoperf_arduino_driver.hpp"


//Treated as main
void setup()
{
    Serial.begin(9600);
    pinMode(13, OUTPUT);
    skik::hoperf::ArduinoDriver drv(2, 3, 4, 5, 6, 7);
    skik::hoperf::RadioModule radio(drv, 9600);

    while(1){
        radio.writeData("Testujemy");
        delay(500);
    }
}
void loop()
{
    //NOT USED
}
