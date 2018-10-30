#include <SPI.h>
#include <WiFi.h>

char ssid[] = "Qwertyuiop";
char pass[] = "123456789";

void setup()
{
WiFi.begin(ssid, pass);
}

void loop (){
  if (WiFi.status() != WL_CONNECTED)    {    Serial.println("Couldn't get a wifi connection");
    while(true);
    }
  else
     {
    long rssi = WiFi.RSSI();
    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.println(" dBm");
    }

delay(10000);//waits 10 seconds and update

}

