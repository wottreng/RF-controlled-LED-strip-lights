#pragma once

#include <Arduino.h>
#include <string.h>

class myFunctions_c {
public:
    const String version = "2.0";
    String debugText;

    void blink();

    void restart();
};

extern myFunctions_c myFunctions;
