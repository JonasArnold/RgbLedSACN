/*
    Name:       RgbLedSACN.ino
    Created:	  07.12.2018 17:08:10
    Author:     JonasArnold

  Librarys needed:
  - ESP8266 Librarys: Install ESP8266 boards according to this instructions: https://arduino-esp8266.readthedocs.io/en/latest/installing.html
  - E131 by Forkineye (not the Async one): https://github.com/forkineye/E131

	Usage:
	- This software will output the RGBW values from sACN Multicasted universe 4.
	- Starting channel is 1, therefore:
	Channel 1: Red value
	Channel 2: Green value
	Channel 3: Blue value
	Channel 4: White1 value
	Channel 5: White2 value

*/

#include <ESP8266WiFi.h>
#include <E131.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "H801.h"
#include "Settings.h"



E131 e131;
H801 h801;

void setup() {
#ifdef DEBUG_ENABLED
  Serial.begin(115200);
  delay(10);
#endif

  /* OTA SETUP */
#ifdef DEBUG_ENABLED
  Serial.println("Booting");
#endif
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
#ifdef DEBUG_ENABLED
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
#endif
    ESP.restart();
  }

  // Port defaults to 8266
  ArduinoOTA.setPort(otaPort);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname(hostname);

  // No authentication by default
  ArduinoOTA.setPassword(otaPassword);

  // Safety methods to help handling the OTA Update
  ArduinoOTA.onStart([]() {
#ifdef DEBUG_ENABLED
    Serial.println("Start");
#endif
  });
  ArduinoOTA.onEnd([]() {
#ifdef DEBUG_ENABLED
    Serial.println("\nEnd");
#endif
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
#ifdef DEBUG_ENABLED
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
#endif
  });
  ArduinoOTA.onError([](ota_error_t error) {
#ifdef DEBUG_ENABLED
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
#endif
  });

  ArduinoOTA.begin();

#ifdef DEBUG_ENABLED
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
#endif

  /* E131 SETUP */
#ifdef MULTICAST
  e131.begin(E131_MULTICAST, universe); /* start e131 listening in multicast mode and set universe */
#elif UNICAST
  e131.begin(E131_UNICAST);  /* start e131 listening in unicast - no need to set universe */
#endif
}

void loop() {
  /* Handle OTA */
  ArduinoOTA.handle();

  /* Handle sACN */
  /* Parse a packet */
  uint16_t num_channels = e131.parsePacket();

  /* Process channel data if we have it */
  if (num_channels) {

    // send it to serial if debug enabled
#ifdef DEBUG_ENABLED
    Serial.printf("Universe %u / %u Channels | Packet#: %u / Errors: %u / CH1: %u\n",
                  e131.universe,              // The Universe for this packet
                  num_channels,               // Number of channels in this packet
                  e131.stats.num_packets,     // Packet counter
                  e131.stats.packet_errors,   // Packet error counter
                  e131.data[0]);              // Dimmer data for Channel 1
#endif

    // Set LEDs
    if (e131.universe == universe)
    {
      h801.setR(e131.data[startChannel - 1]);  // start channel is 0
      h801.setG(e131.data[startChannel]);
      h801.setB(e131.data[startChannel + 1]);
      h801.setW1(e131.data[startChannel + 2]);
      h801.setW2(e131.data[startChannel + 3]);
    }

  }
}
