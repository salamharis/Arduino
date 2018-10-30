#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "b12779aafbe14369ae877eae22e30bc1";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Qwertyuiop";
char pass[] = "123456789";


int i;


void LED()
{
    if (i == HIGH)
    {
      digitalWrite(D3,HIGH);
    }
    else (i == LOW);
    {
      digitalWrite(D3,LOW);
    }
}

BlynkTimer timer;

// V1 LED Widget is blinking
void blinkLedWidget()
{
  if (led1.getValue()) {
    led1.off();
    Serial.println("LED on V1: off");
    digitalWrite(D3,HIGH);
  } else {
    led1.on();
    Serial.println("LED on V1: on");
    digitalWrite(D3,LOW);
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  timer.setInterval(1000L, blinkLedWidget);
  pinMode(13,OUTPUT);
  int i = virtualRead(3);
}

void loop()
{
  LED();
  Blynk.run();
  timer.run();
}

