#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "1d6e9491c57348a2a0cb094062ca6b7d";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Qwertyuiop";
char pass[] = "123456789";

WidgetLED led1(V3);

// We make these values volatile, as they are used in interrupt context
volatile bool pinChanged = false;
volatile int  pinValue   = 0;

// Most boards won't send data to WiFi out of interrupt handler.
// We just store the value and process it in the main loop.
void checkPin()
{
  // Invert state, since button is "Active LOW"
  pinValue = !digitalRead(13);

  // Mark pin value changed
  pinChanged = true;
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  // Make pin 2 HIGH by default
  pinMode(13, INPUT_PULLUP);
  // Attach INT to our handler
  attachInterrupt(digitalPinToInterrupt(13), checkPin, CHANGE);
}

void loop()
{
  Blynk.run();
  if (pinChanged) {

    // Process the value
    if (pinValue) {
      led1.on();
    } else {
      led1.off();
    }

    // Clear the mark, as we have processed the value
    pinChanged = false;
  }
}
