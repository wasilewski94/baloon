/**
* @Author: Michał Kocon
* @Date:   12-01-2017
* @Filename: main.cpp
* @Last modified by:   Michał Kocon
* @Last modified time: 12-01-2017
*/



//
// FILE: TwoPin_DS18B20.ino
// AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: two pins for two sensors demo
// DATE: 2014-06-13
// URL: http://forum.arduino.cc/index.php?topic=216835.msg1764333#msg1764333
//
// Released to the public domain
//
#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS_0 2
#define ONE_WIRE_BUS_1 3
#define ONE_WIRE_BUS_2 4
OneWire oneWire_0(ONE_WIRE_BUS_0);
OneWire oneWire_1(ONE_WIRE_BUS_1);
OneWire oneWire_2(ONE_WIRE_BUS_2);

DallasTemperature sensor_0(&oneWire_0);
DallasTemperature sensor_1(&oneWire_1);
DallasTemperature sensor_2(&oneWire_2);

void setup(void)
{
    Serial.begin(115200);

    sensor_0.begin();
    sensor_1.begin();
    sensor_2.begin();
}

void loop(void)
{
    sensor_0.requestTemperatures();
    Serial.print("#DS18S20# s0: ");
    Serial.print(sensor_0.getTempCByIndex(0));
    Serial.print(" | s1: ");
    sensor_1.requestTemperatures();
    Serial.print(sensor_1.getTempCByIndex(0));
    Serial.write(" | s2: ");
    sensor_2.requestTemperatures();
    Serial.println(sensor_2.getTempCByIndex(0));
}
