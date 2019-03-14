/*
    Name:       RgbLedSACN.ino
    Created:	07.12.2018 17:08:10
    Author:     JonasArnold

	Usage:
	- This software will output the RGBW values from sACN Multicasted universe 4.
	- Starting channel is 1, therefore:
	Channel 1: Red value
	Channel 2: Green value
	Channel 3: Blue value
	Channel 4: White1 value
	Channel 5: White2 value


*/

#include "H801.h"
#include <ESP8266WiFi.h>
#include <E131.h>


const char ssid[] = "...";         /* Replace with your SSID */
const char passphrase[] = "...";   /* Replace with your WPA2 passphrase */
const int universe = 4;
const int startChannel = 1;

E131 e131;
H801 h801;

void setup() {
	Serial.begin(115200);
	delay(10);

	/* Choose one to begin listening for E1.31 data */
	// e131.begin(ssid, passphrase);               /* via Unicast on the default port */
	e131.beginMulticast(ssid, passphrase, 4); /* via Multicast for Universe 4 */
}

void loop() {
	/* Parse a packet */
	uint16_t num_channels = e131.parsePacket();

	/* Process channel data if we have it */
	if (num_channels) {

		// send it to serial
		Serial.printf("Universe %u / %u Channels | Packet#: %u / Errors: %u / CH1: %u\n",
			e131.universe,              // The Universe for this packet
			num_channels,               // Number of channels in this packet
			e131.stats.num_packets,     // Packet counter
			e131.stats.packet_errors,   // Packet error counter
			e131.data[0]);              // Dimmer data for Channel 1

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
