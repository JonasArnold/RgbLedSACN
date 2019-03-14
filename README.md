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

By default Multicast technology is enabled, but you can easily switch to Unicast by uncommenting this line:

```
e131.begin(ssid, passphrase);               /* via Unicast on the default port */
```

and commenting this line:

```
e131.beginMulticast(ssid, passphrase, 4); /* via Multicast for Universe 4 */
```

---

## Librarys

The following librarys are needed to compile the sketch:
  - ESP8266WiFi: Install ESP8266 boards according to this instructions: https://arduino-esp8266.readthedocs.io/en/latest/installing.html
  - [E131 by Forkineye](https://github.com/forkineye/E131) (not the Async one)

---
  
## Compile Settings
**Board: Generic ESP8266 Module**

Flash mode: DIO  
Flash frequency: 40MHz  
CPU frequency: 80MHz  
**Flash size: 512K (64K SPIFFS)**  
Debug port: Disabled  
Debug level: None  
Reset method: ck  
Upload speed: 512000