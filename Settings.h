/*
 * This file contains all the settings needed to run the sketch without
 * changes.
 * Adapt all the variables to your needs.
 */


/*
 * APP SETTINGS
 */

const char ssid[] = "SSID";         /* Replace with your SSID */
const char password[] = "PASSWORD";   /* Replace with your WPA2 passphrase */
const char hostname[] = "rgbLedSAcnNode";    // Hostname of the node
const int universe = 4;            /* Universe the Node listens to in Multicast mode */
const int startChannel = 1;        /* Start Channel the Node listens to */

// Uncomment the E131 type you want to use
#define MULTICAST
//#define UNICAST

/*
 * OTA UPDATE SETTINGS
 */
const int otaPort = 8266;                       // Port defaults to 8266
const char otaPassword[] = "RGBLED123";         // no default password

/*
 * DEBUG
 */
// uncomment the following line to enable Serial Monitor debugging
// #define DEBUG_ENABLED
