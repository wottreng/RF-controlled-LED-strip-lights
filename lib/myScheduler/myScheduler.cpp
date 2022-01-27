/*
Scheduler lib

this lib runs tasks at defined times.
*/
#include <Arduino.h>
#include <string.h>

// custom libs
#include "myScheduler.h"
#include <myWifi.h>
#include <motionDetector.h>

// local vars
unsigned long last_check_5m ;
unsigned long last_check_5s ;

// init timer
void mySchedule_c::init(){
    last_check_5s = millis();
    last_check_5m = millis();
}

//
void mySchedule_c::asap(){
    myWifi.loop();    
}

// tasks to complete every 5 seconds
void mySchedule_c::every_5s()
{
    if (millis() - last_check_5s >= 5000) {
        last_check_5s = millis();
        //
        motion_detector.check_motion_status(); // check for motion
    }
}

// tasks to complete every 5 min
void mySchedule_c::every_5m()
{
    if (millis() - last_check_5m >= 300000) {
        last_check_5m = millis();
        //
        myWifi.connectWifi(false); // check wifi connection
    }
}

mySchedule_c mySchedule;