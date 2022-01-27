/*
motion detector lib
purpose: control motion I/O signal and reporting
*/

#include <Arduino.h>
#include <string.h>
// custom libs -----
#include "motionDetector.h"
#include <RFcontroller.h>

// motion sensor pin
#define motionDetectorPin 13 //esp8266 nodeMCU pin D7
unsigned long motion_detected_time;
unsigned long light_on_interval;

// declare pin as input and config motion vars
void motion_detector_c::init(){
    pinMode(motionDetectorPin, INPUT);
    light_on_interval = 5 * 60 * 1000; // 5min, light will stay on for 5 minutes then shut off if no motion detected
}

void motion_detector_c::check_motion_status(){
    // check for motion, turn light on or reset timer
    if (digitalRead(motionDetectorPin) == 1 ) // motion detected
        { 
            if (RF_light_controller.light_on == true) { // light already on
                motion_detected_time = millis(); // reset on time interval
            } else {
                // note time of motion
                motion_detected_time = millis();
                // turn light on
                RF_light_controller.toggle_light();
                delay(1); // just a quick delay between signals
                RF_light_controller.send_color_output("1"); // red
            }
        }
    // turn light off after light on interval delay and no motion
    if ((digitalRead(motionDetectorPin) == 0) && (RF_light_controller.light_on == true) && ((millis() - motion_detected_time) > light_on_interval)) {
        RF_light_controller.toggle_light();
        RF_light_controller.light_on = false;
    }
}

motion_detector_c motion_detector;
