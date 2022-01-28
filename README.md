# RF-controlled-strip-lights
I reverse engineered RF controlled strip lights so that they can be controlled over wifi with a browser or/and integrated with IOT device controllers via API

## How to Make It Work
* compile and load onto nodeMCU or just load binary firmware onto MCU
* wire up 433Mhz transmitter and motion sensor(optional), see CONNECTIONS below
* when first boot occurs, it will create an open access point "light_controller"
* connect to AP and navigate to http://192.168.10.1/ 
* scroll down to "Change Wifi Access Point" and click "Wifi Setup"
* input your wifi credentials and submit
* it will then try connect to the wifi AP you provided
* if successful, you can then connnect to it via http://light_controller.local/ on your wifi network
* if not successful, the open access point will remain.
* on main page you can click the buttons to send different signals to RF controlled light strip

## How to Use it
* web GUI and click buttons: http://light_controller.local/
* API: http://light_controller.local/api0?color=1 
* GUI API: http://light_controller.local/changeColor?color=1 

NOTE: color/signal values range from 0 to 10 \
0 => white, 1 => red, 2 => green, 3 => blue, 4 => orange, \
5 => yellow, 6 => brighter, 7 => darker, 8 => jump3, 9 => jump7, \
10 => on/off

=========================================================

CONNECTIONS \
motion sensor data pin: physical pin D7 => software pin 13 \
433mhz transmitter data pin: physical pin D5 => software pin 14

HARDWARE \
Novostella 105ft RGB LED Strip Light kit, Color Changing Flexible Dimmable 5050 LEDs, 24V LED Tape with 44 Key RF Remote, LED Ribbon
https://amzn.to/3KMg18w \
ESP8266 nodeMCU: https://amzn.to/3o2HhWl \
433Mhz transmitter:  https://amzn.to/35jImT8 \
Motion sensor: https://amzn.to/3o49Kvc or https://amzn.to/3AAPWEs

DATA SHEETS: \
ESP8266 nodeMCU: https://components101.com/development-boards/nodemcu-esp8266-pinout-features-and-datasheet

SOFTWARE:
Compiled on PlatformIO https://platformio.org/ \
compiled firmware location: /.pio/build/esp01/firmware.bin

NOTE WORTHY LIBS: \
RCSwitch: https://github.com/sui77/rc-switch

Cheers, Mark

![screenShot](https://github.com/wottreng/RF-controlled-strip-lights/blob/main/pics/screenshot.png)
