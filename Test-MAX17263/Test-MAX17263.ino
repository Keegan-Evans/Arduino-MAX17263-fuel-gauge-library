bool debug17263 = 0; // print all values for testing the software

/*
This software has used: https://github.com/AwotG/Arduino-MAX17055_Driver/blob/master/Arduino-MAX17055_Driver.cpp

/**********************************************************************
*
* MIT License
*
* Copyright (c) 2018 Awot Ghirmai
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* 
* Authors: 
* Awot Ghirmai; ghirmai.awot@gmail.com
* Ole Dreessen; ole.dreessen@maximintegrated.com
* 
**********************************************************************

15-11-2019
Author:
Albert van Dalen 
https://www.avdweb.nl/arduino/hardware-interfacing/max17263-fuel-gauge

Todo:
saveHistoryEEPROM()
restoreHistoryEEPROM()
AvgVCell has wrong value

Note that with a 40V battery, the power loss caused by the LEDbar is high: 40V * 20mA = 0.8 W. The LED bar is on when:
1. The LEDbar push button is pressed constantly (this cannot be changed)
2. During charging (this can be switched off)

This is printed:
FuelGaugeResults:
SOC 58.4 % Vcell 3.88 V
Cap 30.3 mAH
Current -0.01 A
TTE 102.40 h
Temp 24.9 C
AvgVCell 11 V
*/ 

#include <Streaming.h>
#include <Wire.h> 
#include <avdweb_VirtualDelay.h>
#include "Definitions.h"
#include "Albert_MAX17263.h"

MAX17263 max17263;
history_t history; // todo in EEPROM
VirtualDelay fuelGaugeDelay; // default = millis

void setup() 
{ Wire.begin();
  Serial.begin(115200); 
  delay(500); // just a small delay before first communications to the MAX17263
  while(!Serial); // wait until serial port opens for native USB devices
  if(debug17263) printMultipliers();
  setMax17263memberVariables(); 
}

void loop() 
{ fuelGaugeDelay.start(2000); 
  if(fuelGaugeDelay.elapsed() && max17263.batteryPresent())
  { manageMAX17263init(); // Values are stored in RAM, so they must be written any time the power is applied or restored to the device
    printFuelGaugeResults(); // Step 3.3 read the Fuel-Gauge Results 
    manageMAX17263historyRead(); // do at certain intervals
  }
}
