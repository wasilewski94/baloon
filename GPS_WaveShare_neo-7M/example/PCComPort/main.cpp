/**
* @Author: Michał Kocon
* @Date:   13-01-2017
* @Filename: main.cpp
* @Last modified by:   Michał Kocon
* @Last modified time: 13-01-2017
*/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include <stdint.h>

void externalGPS(){
    SoftwareSerial gps(6, 7);
    gps.begin(9600);
    while(1){
        if(Serial.available()){
            gps.write(Serial.read());
        }
        if(gps.available()){
            Serial.write(gps.read());
        }
    }
}



void setup(){
    Serial.begin(115200);
    externalGPS();
}

void loop(){

}
