/**
* @Author: Michał Kocon
* @Date:   12-01-2017
* @Filename: main.cpp
* @Last modified by:   Michał Kocon
* @Last modified time: 12-01-2017
*/



#include "Arduino.h"

void setup(){
    Serial.begin(115200);
}
double readv;
double humidity;
void loop(){
    Serial.print("#HIH-4030-001# V: ");
    readv = analogRead(A0)*5.0/1024.0;
    humidity = (readv - 0.958)/0.030680;
    Serial.print(readv);
    Serial.print(" | H: ");
    Serial.println(humidity);
}
