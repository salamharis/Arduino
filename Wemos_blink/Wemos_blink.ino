#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <SimpleTimer.h> // here is the SimpleTimer library
#include <Ethernet.h>
#include <Blynk.h>
#include <SPI.h>
#include <Servo.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "dc7332c255ff451a8aa7c8d5dd041b61";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Qwertyuiop";
char pass[] = "123456789";


BlynkTimer timer;



// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.


Servo servo;

BLYNK_WRITE(V3) {

servo.write(param.asInt());

}

void myTimerEvent()
{

  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  Serial.print("Temp *C = "); Serial.println(t);
  Serial.print("Hum. % = "); Serial.println(h);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1,t);
  Blynk.virtualWrite(V2,h);

  
}

void setup()
{
  Serial.begin(115200);

    if (! sht31.begin(0x45)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }

//  pinMode(D4,OUTPUT);
//  pinMode(D3,OUTPUT);

  Blynk.begin(auth, ssid, pass);

   timer.setInterval(2000L, myTimerEvent);

   servo.attach(D3);
}

void loop(){
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}


