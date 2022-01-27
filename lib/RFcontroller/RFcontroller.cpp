/*
version 2.0
RF led strip controls lib

sends RF signal to LED strip lights via 433mhz transmitter

https://www.amazon.com/dp/B07ZT9LWSH?psc=1&ref=ppx_yo2_dt_b_product_details

Cheers, Mark
*/
#include <Arduino.h>
#include <string.h>
#include <RCSwitch.h>

// custom libs
#include "RFcontroller.h"


// 433mhz transmitter
#define transmitterPin 14 // connected to esp8266 D5
#define pulse_length 431
#define packet_length 24 // number of bits
#define transmit_repeat_num 2 // how many times signal is sent

const unsigned int timeOn = 5 * 60 * 1000; // 5 min
RCSwitch mySwitch = RCSwitch(); // RF driver lib

// assign transmitter pin and transmitter config
void RF_light_controller_c::init(){
    mySwitch.enableTransmit(transmitterPin); // D5
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(pulse_length);
    mySwitch.setRepeatTransmit(transmit_repeat_num); // devices require min 2
}

// turn light on/off, there is no feedback from led strip
void RF_light_controller_c::toggle_light()
{
    mySwitch.send(0b100111000011110000'000100, packet_length); // turn light on/off
    RF_light_controller.light_on = !RF_light_controller.light_on;
}

// change color of light, light needs to be on to work
void RF_light_controller_c::send_color_output(String color_choice)
{
    if (strcmp(color_choice.c_str(), "") != 0) {
        uint8_t colorCode = atoi(color_choice.substring(0, color_choice.length()).c_str());
        if (colorCode >= 0 && colorCode < 11) {
            RF_light_controller.light_color = color_choice;
            switch (colorCode) {
            case 0: // white
                mySwitch.send(0b100111000011110000'001000, packet_length); // last 6 bits are the data packet
                break;
            case 1: // red
                mySwitch.send(0b100111000011110000'000101, packet_length);
                break;
            case 2: // green
                mySwitch.send(0b100111000011110000'000110, packet_length);
                break;
            case 3: // blue
                mySwitch.send(0b100111000011110000'000111, packet_length);
                break;
            case 4: // orange
                mySwitch.send(0b100111'0000'1111'0000'001001, packet_length); 
                break;
            case 5: // yellow
                mySwitch.send(0b100111'0000'1111'0000'010101, packet_length);
                break;
            case 6: // brighter
                mySwitch.send(0b100111000011110000'000001, packet_length);
                break;
            case 7: // darker
                mySwitch.send(0b100111000011110000'000010, packet_length);
                break;
            case 8: // jump3
                mySwitch.send(0b100111000011110000'101001, packet_length);
                break;
            case 9: // jump7
                mySwitch.send(0b100111000011110000'101010, packet_length);
                break;
            case 10: // on/off
                mySwitch.send(0b100111000011110000'000100, packet_length);
                RF_light_controller.light_on = !RF_light_controller.light_on;
                break;
            }
        }
    }
}

/*

led light strip control signal dump:

ON/OFF: Decimal: 10238980 (24Bit) Binary:   100111000011110000000100 Tri-State: not applicable PulseLength: 436 microseconds Protocol: 1
RED: Decimal: 10238981 (24Bit) Binary:      100111000011110000000101 Tri-State: not applicable PulseLength: 431 microseconds Protocol: 1
GREEN: Decimal: 10238982 (24Bit) Binary:    100111000011110000000110 Tri-State: not applicable PulseLength: 431 microseconds Protocol: 1
BLUE: Decimal: 10238983 (24Bit) Binary:     100111000011110000000111 Tri-State: not applicable PulseLength: 436 microseconds Protocol: 1
WHITE: Decimal: 10238984 (24Bit) Binary:    100111000011110000001000 Tri-State: not applicable PulseLength: 436 microseconds Protocol: 1
ORANGE: Decimal: 10238985 (24Bit) Binary:   100111000011110000001001 Tri-State: not applicable PulseLength: 432 microseconds Protocol: 1
YELLOW: Decimal: 10238997 (24Bit) Binary:   100111000011110000010101 Tri-State: not applicable PulseLength: 430 microseconds Protocol: 1
JUMP3: Decimal: 10239017 (24Bit) Binary:    100111000011110000101001 Tri-State: not applicable PulseLength: 431 microseconds Protocol: 1
JUMP7: Decimal: 10239018 (24Bit) Binary:    100111000011110000101010 Tri-State: not applicable PulseLength: 430 microseconds Protocol: 1
QUICK: Decimal: 10239004 (24Bit) Binary:    100111000011110000011100 Tri-State: not applicable PulseLength: 433 microseconds Protocol: 1
SLOW: Decimal: 10239008 (24Bit) Binary:     100111000011110000100000 Tri-State: not applicable PulseLength: 434 microseconds Protocol: 1
FLASH: Decimal: 10239016 (24Bit) Binary:    100111000011110000101000 Tri-State: not applicable PulseLength: 431 microseconds Protocol: 1
MORE RED:Decimal: 10239001 (24Bit) Binary:  100111000011110000011001 Tri-State: not applicable PulseLength: 430 microseconds Protocol: 1
LESS RED:Decimal: 10239005 (24Bit) Binary:  100111000011110000011101 Tri-State: not applicable PulseLength: 431 microseconds Protocol: 1
+ GREEN:Decimal: 10239002 (24Bit) Binary:   100111000011110000011010 Tri-State: not applicable PulseLength: 433 microseconds Protocol: 1
- GREEN:Decimal: 10239006 (24Bit) Binary:   100111000011110000011110 Tri-State: not applicable PulseLength: 433 microseconds Protocol: 1
+ BLUE:Decimal: 10239003 (24Bit) Binary:    100111000011110000011011 Tri-State: not applicable PulseLength: 433 microseconds Protocol: 1
- BLUE:Decimal: 10239007 (24Bit) Binary:    100111000011110000011111 Tri-State: not applicable PulseLength: 433 microseconds Protocol: 1
BRIGHTER:Decimal: 10238977 (24Bit) Binary:  100111000011110000000001 Tri-State: not applicable PulseLength: 431 microseconds Protocol: 1
DARKER:Decimal: 10238978 (24Bit) Binary:    100111000011110000000010 Tri-State: not applicable PulseLength: 430 microseconds Protocol: 1

*/


RF_light_controller_c RF_light_controller;