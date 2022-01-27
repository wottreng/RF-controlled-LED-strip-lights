/*
my Wifi lib

wifi functionality control functions

*/
#include <Arduino.h>
#include <string.h>
#include <WiFiClientSecure.h> 
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// custom libs
#include "myWifi.h"
#include <myEEPROM.h>
#include <myF.h>
#include <RFcontroller.h>
#include "myHTML.cpp"


// local variables ---------------

// http server
ESP8266WebServer httpServer(80); // port 80 aka http

ESP8266HTTPUpdateServer httpUpdater; // update server
const String hostName = "light_controller"; // access via browser: http://light_controller.local/  or  http://192.168.10.1/ if in AP mode
// AP vars -----
IPAddress apIP(192, 168, 10, 1);
const String APssid = hostName;
const String APpswd = "";
const int chan = 1;
const int hidden = false;
const int max_con = 4;

// eeprom wifi credential location
#define wifiSSIDloc   0
#define wifiPSWDloc  20

// functions ==================================================================

// read wifi creds from eeprom
void myWifi_c::init(){
    myWifi.WIFI_SSID = EEPROM_tools.read_eeprom(wifiSSIDloc); // string
    myWifi.WIFI_PASS = EEPROM_tools.read_eeprom(wifiPSWDloc);
}

// wifi handle client and update MDNS
void myWifi_c::loop()
{
    httpServer.handleClient();
    MDNS.update();
}

// wifi cred html page
void wifiCredentialUpdatePage() {
    //httpServer.
    httpServer.send(200, "text/html", myHTML_return_setup_html(myWifi.WIFI_SSID)); // send string to browser
}

// This routine is executed when you change wifi AP
void APinputChange() {
  myWifi.WIFI_SSID = httpServer.arg("wifi SSID");
  myWifi.WIFI_PASS = httpServer.arg("password"); //string
  EEPROM_tools.write_to_EEPROM(myWifi.WIFI_SSID,wifiSSIDloc);
  EEPROM_tools.write_to_EEPROM(myWifi.WIFI_PASS,wifiPSWDloc);  

  httpServer.send(200, "text/html", ap_change_html);  //Send web page
  httpServer.stop();
  myWifi.connectWifi(true);
}

// url not found
void notFound() {  //when stuff after / is incorrect  
  httpServer.send(200, "text/html", not_found_html);  //Send web page
}



// check wifi status and connect wifi or else create AP
void myWifi_c::connectWifi( bool New_Connection)
{
    if (WiFi.status() != 3 || New_Connection == true) // if not conneted or new connection
    {
        //wifi_set_sleep_type(LIGHT_SLEEP_T); // Auto modem sleep is default, light sleep for power savings
        WiFi.persistent(false);
        WiFi.setOutputPower(20);
        WiFi.mode(WIFI_STA); //WIFI_STA
        WiFi.hostname(hostName.c_str());
        WiFi.begin(WIFI_SSID, WIFI_PASS);
        const uint8_t maxTry = 10; // try this many times to connect
        uint8_t x = 0;
        while (x <= maxTry) {
            delay(800);
            uint8_t conStatus = WiFi.status();
            x += 1;
            if (conStatus == 3) { // connected to AP   
             WiFi.mode(WIFI_STA);             
                x = 100;
                #if mywifi_debug
                  digitalWrite(getLEDpin(), HIGH); // off
                #endif

            } else if (conStatus != 3 && x == maxTry) {
                // access point mode
                WiFi.mode(WIFI_AP); //WIFI_AP
                WiFi.setOutputPower(16); // 20.5 -> 0 in .25 increments
                WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); //#
                WiFi.softAP(APssid, APpswd, chan, hidden, max_con);
                #if mywifi_debug
                    digitalWrite(getLEDpin(), LOW); // on
                    //Serial.println("no AP connection, starting hotspot");
                #endif
            }
        }
        myWifi_c::web_server_config();
    }
}

// for api output
void jsonData()
{
    //unsigned long lastOffsec = (millis() - lastOff) / 1000;
    String output = "{" 
                    "\"color\":\"" + RF_light_controller.light_color + "\","
                    "\"debugText\":\"" + myFunctions.debugText + "\","
                    "\"Wifi_SSID\":\""  + myWifi.WIFI_SSID + "\",";

    uint8_t mode = WiFi.getMode();
    if (mode == 1)  output += "\"Wifi_Mode\":\"Station\",";
    else if (mode == 2)  output += "\"Wifi_Mode\":\"Access Point\",";
    else if (mode == 3)  output += "\"Wifi_Mode\":\"STA_AP\",";
    else if (mode == 0)  output += "\"Wifi_Mode\":\"Off\",";

    output += "\"Wifi_Power_dBm\":\"20\","
              "\"Wifi_PhyMode\":\""   + String(WiFi.getPhyMode()) + "\"," // 3:
                "\"Wifi_Sleep_Mode\":\""  + String(WiFi.getSleepMode()) + "\"," // 1: light_sleep
                "\"Wifi_IP_addr\":\""  + WiFi.localIP().toString() + "\",";

    uint8_t conStatus = WiFi.status();
    if (conStatus == 0)   output += "\"Wifi_Status\":\"Idle\",";
    else if (conStatus == 3)   output += "\"Wifi_Status\":\"Connected\",";
    else if (conStatus == 1)   output += "\"Wifi_Status\":\"not connected\",";
    else if (conStatus == 7)   output += "\"Wifi_Status\":\"Disconnected\",";
    else   output += "\"Wifi_Status\":\"" + String(conStatus) + "\",";

    output += "\"Wifi_Signal_dBm\":\"" + String(WiFi.RSSI()) + "\","
            "\"Core Frequency MHz\":\"" +  String(ESP.getCpuFreqMHz()) +   "\","
            "\"reason last reset\":\"" +    ESP.getResetReason() +    "\","
            "\"free HEAP\":\"" + String(ESP.getFreeHeap()) +  "\"," 
            "\"ESP ID\":\"" + String(ESP.getChipId()) +  "\","
            "\"sketch size\":\"" + String(ESP.getSketchSize()) +  "\","  
            "\"version\":\"" + myFunctions.version + "\""
            "}";

    httpServer.send(200, "application/json", output);
}

// direct api call
void argData()
{
    // change color via api
    if (httpServer.arg("color") != "") {
        RF_light_controller.send_color_output(httpServer.arg("color"));
    }

    jsonData();
}


//===main page builder=========================
void mainPageBuilder()
{
httpServer.send(200, "text/html", myHTML_return_main_page_html(myFunctions.version, myWifi.WIFI_SSID, WiFi.status(), WiFi.localIP().toString(), RF_light_controller.light_on, RF_light_controller.light_color));
}

//main color API for changing led light color
void changeColor()
{
    RF_light_controller.send_color_output(httpServer.arg("color"));
    mainPageBuilder();
}

//
void reboot(){
    myFunctions.restart();
}

// web server config
void myWifi_c::web_server_config(){
    if (WiFi.getMode() == 1) MDNS.begin(hostName.c_str());

    //------server--------------------
    // server.stop();
    httpServer.onNotFound(notFound); // after ip address /
    httpServer.on("/", HTTP_GET, mainPageBuilder);
    httpServer.on("/APsetup", HTTP_GET, wifiCredentialUpdatePage);
    httpServer.on("/input", HTTP_POST, APinputChange);
    httpServer.on("/api0", HTTP_GET, argData);
    httpServer.on("/changeColor", HTTP_GET, changeColor);    
    httpServer.on("/reboot", HTTP_GET, reboot);
    httpUpdater.setup(&httpServer);
    httpServer.begin();
    MDNS.addService("http", "tcp", 80);
}

//
WiFiMode_t myWifi_c::get_wifi_mode(){
   return WiFi.getMode();
}

//
String myWifi_c::return_local_ip(){
    return WiFi.localIP().toString();
}

//
uint8_t myWifi_c::return_connection_status(){
    return WiFi.status();
}

myWifi_c myWifi;