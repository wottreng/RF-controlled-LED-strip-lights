/*
  motion activated (optional) 433Mhz RF LED strip signal sender using esp8266 NodeMCU
  By Mark Wottreng
  https://github.com/wottreng

  I reverse engineered the RF signal for the LED light strip and published the code in /lib/RFcontroller

  This code repository allows you to control the LED light strip via 433Mhz transmitter on an ESP8266 nodeMCU


  motion sensor data pin: physical pin D7 => software pin 13
  433mhz transmitter data pin: physical pin D5 => software pin 14

  opens hotspot AP if it cant connect to a wifi network
  access via browser: http://light_controller.local/ once connected

*/

#include <Arduino.h>
#include <string.h>

// custom libs
#include <myF.h>
#include <RFcontroller.h>
#include <motionDetector.h>
#include <myEEPROM.h>
#include <myWifi.h>
#include <myScheduler.h>

#define DEBUG false

// if no motion sensor, then change to false
#define motion_detection_active true

void setup()
{
    //
    #if DEBUG == true
        Serial.begin(9600);
    #endif
    //
    EEPROM_tools.init();
    //
    myWifi.init();
    //
    #if motion_detection_active == true
    motion_detector.init();
    #endif
    //
    RF_light_controller.init();
    //
    myWifi.connectWifi(true);
    //
    mySchedule.init();
}

void loop()
{
    mySchedule.asap();

#if motion_detection_active == true
    mySchedule.every_5s(); // this is where motion detection sampling occurs
#endif

    mySchedule.every_5m();
}
