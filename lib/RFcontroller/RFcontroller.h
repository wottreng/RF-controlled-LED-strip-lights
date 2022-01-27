#pragma once

#include <Arduino.h>
#include <string.h>

class RF_light_controller_c {

    public:
        String light_color = "1";
        bool light_on = false; // there is no feedback from led strip so this is not always accurate

        void init();

        void toggle_light();

        void send_color_output(String colorChoice);

};

extern RF_light_controller_c RF_light_controller;