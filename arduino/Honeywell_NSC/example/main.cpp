/**
* @Author: Michał Kocon
* @Date:   12-01-2017
* @Filename: main.cpp
* @Last modified by:   Michał Kocon
* @Last modified time: 13-01-2017
*/

#include "Arduino.h"

void setup(){
    Serial.begin(115200);
}

void loop(){
    Serial.println((analogRead(A2) - analogRead(A1)));
}
