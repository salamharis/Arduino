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


WidgetLCD lcd(V1);
BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "Non-Invasive"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(5, 1, "Blood Glucose Device");
  
  // Please use timed events when LCD printintg in void loop to avoid sending too many commands
  // It will cause a FLOOD Error, and connection will be dropped

}

void loop()
{
  Blynk.run();


}

