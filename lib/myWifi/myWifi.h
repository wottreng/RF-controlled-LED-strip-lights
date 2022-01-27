#pragma once



#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>

class myWifi_c
{
public:
    // wifi 
    String WIFI_SSID;
    String WIFI_PASS;


    // run in setup loop
    void init();

    // run in main loop
    void loop();

    // try to connect to wifi AP, if none then create hotspot AP
    void connectWifi(bool New_Connection);

    WiFiMode_t get_wifi_mode();

    void web_server_config();

    String return_local_ip();

    uint8_t return_connection_status();
};

extern myWifi_c myWifi;
