#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h> // here is the SimpleTimer library




// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "1d6e9491c57348a2a0cb094062ca6b7d";


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Qwertyuiop";
char pass[] = "123456789";


WidgetLCD lcd(V1);
BlynkTimer timer;
int BG_read = A0;
int BG,BG_on, BG_pin = D2;
int recommendation_pin = D7;
int LCD;
void setup() {

  // Initializes serial communication
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  pinMode(BG_read,INPUT);
  pinMode(recommendation_pin,INPUT);
  pinMode(BG_pin,INPUT);
  

  lcd.clear();
  lcd.print(0,0,"MAGS GLUCOMETER"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(5,1,"Hola!!");
  delay(5000);

  timer.setInterval(10L,BG_reading);
  
}


void loop() {
  Blynk.run();
  timer.run(); // SimpleTimer is working
  lcd.clear();
  lcd.print(0,0,"MAGS GLUCOMETER"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(5,1,"Hola!!");
    delay(5000);
//  BG_reading();
}


int age_use, weight_use, diabetes_use,user_use, insulin_use;
float finalresult, BG_use;

void BG_reading()
{ 
  lcd.clear();
  lcd.print(0,0,"MAGS GLUCOMETER"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(5,1,"Hola!!");
  
    LCD = digitalRead(D7);
    
    
     BG_on = analogRead(BG_pin);

  
   int n=20, i=0; // n is the number of reading taken
   float average,sum; 
   int IRread[n];
        for (i=0 ;i<n ;i++)
        {
          IRread[i]=analogRead(BG_read);
          sum += IRread[i];
          Serial.print(i+1);
          Serial.print(") sum=");
          Serial.println(sum);
        }
        average = sum/n;
        BG = average/79;
        Serial.print("BG=");
        Serial.println(BG);
        Serial.println("");
        Blynk.connect();
        Blynk.virtualWrite(V0,BG);
  

  // Blynk.connect();
   lcd.clear();
   lcd.print(0,0,"REFER HEALTHCARE");
   lcd.print(0,1,"PERSONNEL :D");
   delay(2000);
//   
//   lcd.clear(); 
//   lcd.print(0,0,"!!DIABETES RISK!!");
//   lcd.print(0,0,"Kidney damage");
//   delay(100);
//
//   lcd.clear();
//   lcd.print(0,0,"Nerve damage");
//   lcd.print(0,1,"Eye&foot damage");
//   delay(100);
//   
//   lcd.clear();
//   lcd.print(0,0,"Fungal infection");
//   lcd.print(0,1,"Hearing problem");
//   delay(100);
//
//      lcd.clear();
//   lcd.print(0,0,"Alzheimer");
//   lcd.print(0,1,"Cardio disease");
//   delay(100);

    lcd.clear();
   lcd.print(0,0,"SO DONT FORGET");
   lcd.print(0,1,"Balanced diet");
   delay(2000);

    lcd.clear();
   lcd.print(0,0,"Regularexercise");
   lcd.print(0,1,"Regular checkup");
   delay(2000);

   lcd.clear();
   lcd.print(0,0,"Quit smoking");
   lcd.print(0,1,"Self care");
   delay(2000);

   lcd.clear();
   lcd.print(0,0,"Good problem");
   lcd.print(0,1,"solving skills");  
 
}

