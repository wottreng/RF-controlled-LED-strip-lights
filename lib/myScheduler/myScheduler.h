#pragma once

#include <Arduino.h>
#include <string.h>

class mySchedule_c
{
public:
    void init();

    void asap();

    void every_5s();

    void every_5m();
};

extern mySchedule_c mySchedule;