/**
* @Author: Michał Kocon
* @Date:   10-01-2017
* @Filename: main.cpp
* @Last modified by:   Michał Kocon
* @Last modified time: 11-01-2017
*/


#include "wiringPi.h"
#include "wiringSerial.h"
#include "hoperf.hpp"
#include "hoperf_arduino_driver.hpp"

#define UART_TX1 15
#define UART_RX1 16
#define HCONFIG 3
#define HSLEEP 9
#define HSTATUS 7
#define HRESET 0

//Treated as main
int main()
{
	pinMode(UART_TX1, OUTPUT);
	pinMode(UART_RX1, INPUT);
	
	int fd;
    //if(fd = serialOpen("/dev/ttyS1", 9600)) printf("Error uart");
    skik::hoperf::ArduinoDriver drv("/dev/ttyS1", HCONFIG, HSLEEP, HSTATUS, HRESET);
    skik::hoperf::RadioModule radio(drv, 9600);

    while(1){
        radio.writeData("Testujemy");
        delay(500);
    }
}
