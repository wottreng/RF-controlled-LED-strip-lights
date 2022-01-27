/*
my functions lib
just random functions that dont fit in anywhere else
*/
#include <Arduino.h>
#include <string.h>
//
#include "myF.h"
#include <RFcontroller.h>



// blink onboard LED
void myFunctions_c::blink()
{
    digitalWrite(16, 1);
    delay(500);
    digitalWrite(16, 0);
}

// reboot command
void myFunctions_c::restart()
{
    ESP.restart(); // reboot
}

myFunctions_c myFunctions;


