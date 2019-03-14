# RgbLedSACN
Arduino sketch for **H801 WiFi RGBW LED driver board**. Makes the device controllable by [**streamingACN (sACN)**](https://en.wikipedia.org/wiki/Architecture_for_Control_Networks) protocol, which is often used in the event lighting industry.

---

## Usage
Configure your settings in the **Settings.h** file.  
The software will make the H801 device listen on sACN and output the colors and brightness sent over sACN on the LED terminals.  
The start channel is the first channel of the node and it takes 5 channels to control all 5 led drivers:  
- Channel 1: Red value
- Channel 2: Green value
- Channel 3: Blue value
- Channel 4: White1 value
- Channel 5: White2 value

---

## sACN

By default Multicast type is used, but you can easily switch to Unicast in the Settings.h file:
```
// Uncomment the E131 type you want to use
#define MULTICAST
//#define UNICAST
```

---

## Librarys

The following librarys are needed to compile the sketch:
  - ESP8266WiFi: Install ESP8266 boards according to [this instructions](https://arduino-esp8266.readthedocs.io/en/latest/installing.html).
  - [E131 by Forkineye](https://github.com/forkineye/E131) (not the Async one)

---
  
## Update OTA (over the air)

You can update your node over **Arduino OTA**. [(Documentation)](https://arduino-test.esp8266.com/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html#classic-ota-configuration)  
To configure the hostname, port and password use the **Settings.h** file.

**To update make sure the computer is in the same network as the node!**

### Update via IDE:
Make sure you installed Python 2.7 like described [here](https://arduino-test.esp8266.com/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html#classic-ota-configuration). and Python is not blocked by your computers firewall
1. Select the node in *Tools > Port* in the Arduino IDE
2. Press Upload in the Arduino IDE
3. Type in password you configured in the **Settings.h** file

### Update via Web browser:
The sketch you are trying to upload may not be bigger than 512kB (because the flash memory of the ESP8266 is 1M)
1. Export the binary file of your sketch in the Arduino IDE: *Sketch > Export compiled Binary*
2. In the web browser go to the following URL: `http://<Your Node's IP>/update` (e.g. `http://192.168.1.116/update`)
3. Select the previously exported file
4. Press Upload

---
  
## Compile Settings
**Board: Generic ESP8266 Module**  
Flash mode: DIO  
Flash frequency: 40MHz  
CPU frequency: 80MHz  
**Flash size: 1M (64K SPIFFS)**  
Debug port: Disabled  
Debug level: None  
Reset method: ck  
**Upload speed: 115200**