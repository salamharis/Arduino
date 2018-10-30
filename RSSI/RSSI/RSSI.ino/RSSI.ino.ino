// WiFiPro.ino  Project name WiFiPro4Blynk by Costas 18th Sept 2016

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ArduinoOTA.h>       // for local OTA updates
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>      // Essential for almost all sketches
SimpleTimer timer;

//********************* SECTION FOR YOU TO COMPLETE WITH YOUR DETAILS *************
// Get Auth Token in the Blynk App.
char auth[] = "xxxx"; // Go to the Project Settings (nut icon).
char cloudserver[16] = "blynk-cloud.com";
char localserver[16] = "192.168.10.229";          // Enter your IP details for the local server
char ssid[] = "Qwertyuiop";                   // Your WiFi credentials.
char pass[] = "123456789";                     // Set password to "" for open networks.
char OTAhost[] = "WiFiPro4Blynk";              // Optional, but very useful
//************************************************************************************************

// pick colours from http://www.w3schools.com/colors/colors_picker.asp
#define BLYNK_RED         "#D3435C"  // used when RSSI is worse than -83 dBm (< 60%)
#define BLYNK_YELLOW      "#ED9D00"  // used when RSSI is between -83 dBm and -57 dBm (60% to 75%)
#define BLYNK_GREEN       "#23C48E"  // used when RSSI is better than -57 dBm (> 75%)
/* other colors, not used
#define BLYNK_BLUE      "#04C0F8"
#define BLYNK_DARK_BLUE "#5F7CD8"
#define BLYNK_BLACK     "#000000"
#define BLYNK_WHITE     "#FFFFFF"
#define BLYNK_MAROON    "#A12345" 
#define BLYNK_PINK      "#FFB3B3"
#define BLYNK_OLIVE     "#808000" */

void reconnectBlynk() {                         // reconnect to server if disconnected, timer checks every 60 seconds
  if (!Blynk.connected()) {
    if(Blynk.connect()) {
      BLYNK_LOG("Reconnected");
    } else {
      BLYNK_LOG("Not reconnected");
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("\n Starting");
  //Blynk.begin(auth, ssid, pass);              // normal Blynk Cloud server connection     
  //Blynk.config(auth, cloudserver);            // for Blynk's cloud server if WiFi already connected
  Blynk.begin(auth, ssid, pass, localserver);   // for a local server requiring WiFi connection
  int mytimeout = millis() / 1000;
  while (Blynk.connect(1000) == false) {        // wait here until connected to the server
    if((millis() / 1000) > mytimeout + 8){      // try to connect to the server for less than 9 seconds
      break;                                    // continue with the sketch regardless of connection to the server
    }
  }  
  Serial.println(map(WiFi.RSSI(), -110, -30, 45, 90) + String('%'));  // only display on bootup
  ArduinoOTA.setHostname(OTAhost);              // for local OTA updates
  ArduinoOTA.begin();                           // for local OTA updates
  timer.setInterval(15000, reconnectBlynk);     // check every 15 seconds if we are connected to the server
  timer.setInterval(300, showRSSI);             // was 600
}

void showRSSI(){
  //Serial.println(map(WiFi.RSSI(), -110, -30, 30, 100) + String('%'));
  if(WiFi.RSSI() < -83){
    Blynk.setProperty(V0, "color", BLYNK_RED);   // red gauge
  }
  else if(WiFi.RSSI() > -57){
    Blynk.setProperty(V0, "color", BLYNK_GREEN);   // green gauge
  }
  else{
    Blynk.setProperty(V0, "color", BLYNK_YELLOW);   // yellow gauge    
  }
  delay(30);
  Blynk.virtualWrite(V0, map(WiFi.RSSI(), -110, -30, 45, 90));
  float cycle = millis() / (1000.0);
  Blynk.virtualWrite(V1, cycle);
}

void loop()
{
  if (Blynk.connected()) {   // to ensure that Blynk.run() function is only called if we are still connected to the server
    Blynk.run();
  }
  timer.run();
  ArduinoOTA.handle();       // for local OTA updates
}
