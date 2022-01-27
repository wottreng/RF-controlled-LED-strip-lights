#pragma once

#include <Arduino.h>

class motion_detector_c
{
public:
    // declare motion sensor pin as input
    void init();

    // check for motion
    void check_motion_status();
};

extern motion_detector_c motion_detector;