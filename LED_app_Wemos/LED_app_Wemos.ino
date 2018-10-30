#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();
 
const char* ssid = "Qwertyuiop"; // Enter Your wifi SSID here
const char* password = "123456789"; // Enter Your Wifi Password Here
 
ESP8266WebServer server(80);
 
const int led = D0;
 
void led_on() {
  digitalWrite(led, 1);
}

void led_off() {
  digitalWrite(led, 0);
}

void readsensor() {
 
//  String val = String(analogRead(A0),DEC);
//  String val2 = String(analogRead(D0),DEC);

  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  String val = String(t);
  String val2 = String(h);
  
  Serial.println("Humidity : "+val+'\n'+ "Temperature : "+val2);
  server.send(200, "text/plain", "Humidity : "+val+'\n'+"Temperature : "+val2);
}
 
void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
 
void setup(void){
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(A0,INPUT);
  pinMode(D0,INPUT);
  digitalWrite(led, 0);


 
    if (! sht31.begin(0x45)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
  
  WiFi.begin(ssid, password);
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
 
  server.on("/gpio/0", led_off);
  server.on("/gpio/1", led_on);
  server.on("/gpio/2", readsensor);
 
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });
 
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
}
