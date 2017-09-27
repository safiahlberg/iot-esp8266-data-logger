/*********************************************************************

*********************************************************************/

/************************* I2C protocol **************************************/
#include <SPI.h>
#include <Wire.h>

/************************* SSD1306 display ***********************************/
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);

// Verify that the correct LCD height is set
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

/************************* MQTT setup ****************************************/
#define DEBUG_SSL
#define DEBUGV
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* Private data **************************************/
#include "private_data.h"

/************************* Push Button ***************************************/
#include "pushbutton.h"

/************************* Timers ********************************************/
#include "scutil/sc_timer_service.h"

/************************* Generated control *********************************/
#include "src-gen/Datalogger.h"
#include "src-gen/DataloggerRequired.h"

// Private data should contain the following definitions
// #define WLAN_SSID       "<Your SSID>"
// #define WLAN_PASS       "<Your WiFi password key>"
// #define AIO_SERVER      "<The server you wish to publish to, for example io.adafruit.com>"
// #define AIO_SERVERPORT  8883                   // 8883 for MQTTS
// #define AIO_USERNAME    "<Username>"
// #define AIO_KEY         "<Key>"

/************ Global State (you don't need to change this!) ******************/

// WiFiFlientSecure for SSL/TLS support
WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// io.adafruit.com SHA1 fingerprint
const char* fingerprint = "AD 4B 64 B3 67 40 B5 FC 0E 51 9B BD 25 E9 7F 88 B6 2A A3 5B";

/****************************** Feeds ***************************************/

// Setup a feed called 'press' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish feed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/press");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();
void verifyFingerprint();

//! As we make use of time triggers (after & every) we make use of a generic timer implementation and need a defined number of timers.
#define MAX_TIMERS 20

//! The timers are managed by a timer service. */
static sc_timer_service_t timer_service;

// Pushbutton that activates the screen among other things
pushbutton_t pushbutton;
const int button_pin = 3;    // the number of the pushbutton pin

static Datalogger datalogger;

//! We allocate the desired array of timers.
static sc_timer_t timers[MAX_TIMERS];

//! callback implementation for the setting up time events
void dataloggerCtrl_setTimer(Datalogger* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic){
	sc_timer_start(&timer_service, (void*) handle, evid, time_ms, periodic);
}

//! callback implementation for canceling time events.
void dataloggerCtrl_unsetTimer(Datalogger* handle, const sc_eventid evid) {
	sc_timer_cancel(&timer_service, evid);
}

static void button_changed(pushbutton_t *button) {
	if (!pushbutton.state) dataloggerIface_raise_wakeDisplay(&datalogger);
}

void setup() {
  Serial.begin(115200);
  setup_pushbutton(&pushbutton, button_pin, button_changed);

  sc_timer_service_init(
  				&timer_service,
  				timers, MAX_TIMERS,
  				(sc_raise_time_event_fp) &datalogger_raiseTimeEvent);

  datalogger_init(&datalogger);

  datalogger_enter(&datalogger);

}


#define CYCLE_PERIOD (10)
static unsigned long cycle_count = 0L;
static unsigned long last_cycle_time = 0L;



uint32_t x=0;

void loop() {


	unsigned long current_millies = millis();

	read_pushbutton(&pushbutton);

	if ( cycle_count == 0L || (current_millies >= last_cycle_time + CYCLE_PERIOD) ) {

		sc_timer_service_proceed(&timer_service, current_millies - last_cycle_time);

		datalogger_runCycle(&datalogger);

		last_cycle_time = current_millies;
		cycle_count++;
	}

  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // Now we can publish stuff!
  Serial.print(F("\nSending val "));
  Serial.print(x);
  Serial.print(F(" to feed feed..."));
  if (! feed.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

  // wait a couple seconds to avoid rate limit
  delay(5000);

}

void dataloggerIface_synchronize(const Datalogger *handle) {

}

void initDisplay(void) {
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C this is different than the 0x3D addres that should be used for 128x64 default
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(500);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  void resetDisplay();
}

void resetDisplay(void) {
  // Clear the buffer.
  display.clearDisplay();
  display.display();
}

void mqttConnection(void) {
  Serial.setDebugOutput(false);

  Serial.println(F("Data collector MQTTS (SSL/TLS)"));
  display.println(F("Data collector MQTTS (SSL/TLS)"));
  display.display();

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to WiFi SSID: ");
  Serial.println(WLAN_SSID);

  delay(1000);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  delay(2000);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());

  // check the fingerprint of io.adafruit.com's SSL cert
  verifyFingerprint();
}


void verifyFingerprint() {

  const char* host = AIO_SERVER;

  Serial.print("Connecting to host: ");
  Serial.println(host);

  if (! client.connect(host, AIO_SERVERPORT)) {
    Serial.println("Connection failed. Halting execution.");
    while (1);
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("Fingerprint verified. Connection secure.");
  } else {
    Serial.println("Could not verify fingerprint. Connection insecure! Halting execution.");
    while (1);
  }

}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }

  Serial.println("MQTT Connected!");
}

