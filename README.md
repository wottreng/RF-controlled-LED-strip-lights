# RF-controlled-strip-lights
I reverse engineered RF controlled strip lights so that they can be controlled over wifi with a browser or/and integrated with IOT device controllers via API

## How to Make It Work
* compile and load onto nodeMCU or just load binary firmware onto MCU
* when first boot occurs, it will create an open access point "light_controller"
* connect and navigate to http://192.168.10.1/ 
* scroll down to "Change Wifi Access Point" and click "Wifi Setup"
* input your wifi credentials and submit
* it will then try connect to the wifi AP you provided
* if successful, you can then connnect to it via http://light_controller.local/ on your wifi network
* if not successful, the open access point will remain.
* on main page you can click the buttons to send different signals to RF controlled light strip

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

Cheers, Mark

![screenShot]()