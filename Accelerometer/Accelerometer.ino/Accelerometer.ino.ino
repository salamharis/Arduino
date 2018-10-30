// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MPU-6000
// This code is designed to work with the MPU-6000_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=MPU-6000_I2CS#tabs-0-product_tabset-2
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <SimpleTimer.h> // here is the SimpleTimer library
#include <Ethernet.h>
#include <SPI.h>

// MPU-6000 I2C address is 0x68(104)
#define Addr 0x68
#define count 30

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "1c6816b9a52c4428a92f68fe167801c8";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Qwertyuiop";
char pass[] = "123456789";


int Power=0;
int Distance=0; 


double xaxis [count] ;
double yaxis[count] ;
double zaxis [count] ;
double xaccelero [count] ;
double yaccelero[count] ;
double zaccelero [count] ;
 int i=0;
 double totalgx =0;
 double totalgy =0;
 double totalgz =0;
 double totalx =0;
 double totaly =0;
 double totalz =0;


 
    


SimpleTimer timer; // Create a Timer object called "timer"!

void myTimerEvent()
{
  unsigned int data[6];

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x3B);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);

  // Read 6 byte of data
  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }

  // Convert the data
  int xAccl = data[0] * .256 + data[1];
  int yAccl = data[2] * .256 + data[3];
  int zAccl = data[4] * .256 + data[5];



  // Start I2C transmission
  Wire.beginTransmission(Addr);
   //Select data register
  Wire.write(0x43);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);

  // Read 6 byte of data
  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();

  }
  // Convert the data
  int xGyro = data[0] * .256 + data[1];
  int yGyro = data[2] * .256 + data[3];
  int zGyro = data[4] * .256 + data[5];



 zaxis[i] = zGyro;
 xaxis[i] =xGyro;
 yaxis[i] =yGyro;
 zaccelero[i] = zAccl;
 xaccelero[i] =xAccl;
 yaccelero[i] =yAccl;
    for (int j=0 ; j<count ;j++){
       totalgz = totalgz + zaxis[j];   
       totalgx = totalgx+ xaxis[j];
       totalgy = totalgy + yaxis[j];
       totalz = totalz + zaccelero[j];   
       totalx = totalx+ xaccelero[j];
       totaly = totaly + yaccelero[j];
    }
     double purataz = totalz/count; 
     double puratax = totalx/count; 
     double puratay = totaly/count;
     double puratagz = totalgz/count; 
     double puratagx = totalgx/count; 
     double puratagy = totalgy/count; 
     totalz = 0;
     totalx = 0;
     totaly = 0;
     totalgz = 0;
     totalgx = 0;
     totalgy = 0;
      i++;

      if (i==count){
        i=0;
      }

  Serial.print(puratagz);
  Serial.print(",");
  Serial.println(puratagx);
  Serial.print(purataz);
  Serial.print(puratax);
  Serial.print(puratay);

const int xpin = puratax; 
const int ypin = puratay;
const int zpin = purataz;

float val_x, val_y, val_z;

//int count_x, count_y, count_z;
//char flag_x, flag_y, flag_z;
//char prev_flag_x, prev_flag_y, prev_flag_z;
char axis;

double X=0;
  double Y=0;
  double Z=0;
  double R=0;
  double J=0;
  int x = xpin;
  delay(1); 
  int y = ypin;
  delay(1); 
  int z = zpin;
  //zero_G is the reading we expect from the sensor when it detects
  //no acceleration.  Subtract this value from the sensor reading to
  //get a shifted sensor reading.
  float zero_G = 512.0; 
  //scale is the number of units we expect the sensor reading to
  //change when the acceleration along an axis changes by 1G.
  //Divide the shifted sensor reading by scale to get acceleration in Gs.
  float scale = 102.3;
  static unsigned int count2=0;
  if(++count2>50){
  val_x = (((float)x - 500)/scale);
  val_y = (((float)y - 508)/scale);
  val_z = (((float)z - 635.0)/scale);
 

  
  
   X = abs(val_x*val_x);
   Y = abs(val_y*val_y);
   Z = abs(val_z*val_z);
   R= (X+Y+Z);


   
    J = sqrt (R);
    Serial.print(x);
    Serial.print("\t");
    Serial.print(y);
    Serial.print("\t");
    Serial.print(z);
    Serial.print("\t ");
    Serial.print(val_x);
    Serial.print("\t");
    Serial.print(val_y);
    Serial.print("\t");
    Serial.print(val_z);
    Serial.print("\t ");
    Serial.println(R);

//    Serial.print(count_x);
//    Serial.print("\t");
//    Serial.print(count_y);
//    Serial.print("\t");
//    Serial.print(count_z);
//    Serial.print("\t ");
    Serial.print(J);
    Serial.print("\n");
    count2=0;
    

   
if(J > 5){
    tone(9, 440, 2000);
    Serial.println("Impact");
  // do something repetitive 200 times
  J++;
}
  }




WidgetLCD lcd(V2);

if (puratagz >= 318 && puratagx >= 305 )
    {  //jatuh
     delay(1000);
           // Start I2C transmission
          Wire.beginTransmission(Addr);
           //Select data register
          Wire.write(0x43);
          // Stop I2C transmission
          Wire.endTransmission();
        
          // Request 6 bytes of data
          Wire.requestFrom(Addr, 6);
        
          // Read 6 byte of data
          if (Wire.available() == 6)
          {
            data[0] = Wire.read();
            data[1] = Wire.read();
            data[2] = Wire.read();
            data[3] = Wire.read();
            data[4] = Wire.read();
            data[5] = Wire.read();
        
          }
          // Convert the data
          int xGyro = data[0] * .256 + data[1];
          int yGyro = data[2] * .256 + data[3];
          int zGyro = data[4] * .256 + data[5];
        
        
        
         zaxis[i] = zGyro;
         xaxis[i] =xGyro;
         yaxis[i] =yGyro;
         zaccelero[i] = zAccl;
         xaccelero[i] =xAccl;
         yaccelero[i] =yAccl;
            for (int j=0 ; j<count ;j++){
               totalgz = totalgz + zaxis[j];   
               totalgx = totalgx+ xaxis[j];
               totalgy = totalgy + yaxis[j];
               totalz = totalz + zaccelero[j];   
               totalx = totalx+ xaccelero[j];
               totaly = totaly + yaccelero[j];
            }
             double purataz = totalz/count; 
             double puratax = totalx/count; 
             double puratay = totaly/count;
             double puratagz = totalgz/count; 
             double puratagx = totalgx/count; 
             double puratagy = totalgy/count; 
             totalz = 0;
             totalx = 0;
             totaly = 0;
             totalgz = 0;
             totalgx = 0;
             totalgy = 0;
              i++;
        
              if (i==count){
                i=0;
              }
        
          Serial.print(puratagz);
          Serial.print(",");
          Serial.println(puratagx);
         if (puratagz >= 313 && puratagx >= 305 )
         {
          delay(1000);
            // Start I2C transmission
                Wire.beginTransmission(Addr);
                 //Select data register
                Wire.write(0x43);
                // Stop I2C transmission
                Wire.endTransmission();
              
                // Request 6 bytes of data
                Wire.requestFrom(Addr, 6);
              
                // Read 6 byte of data
                if (Wire.available() == 6)
                {
                  data[0] = Wire.read();
                  data[1] = Wire.read();
                  data[2] = Wire.read();
                  data[3] = Wire.read();
                  data[4] = Wire.read();
                  data[5] = Wire.read();
              
                }
                // Convert the data
                int xGyro = data[0] * .256 + data[1];
                int yGyro = data[2] * .256 + data[3];
                int zGyro = data[4] * .256 + data[5];
              
              
              
               zaxis[i] = zGyro;
               xaxis[i] =xGyro;
               yaxis[i] =yGyro;
               zaccelero[i] = zAccl;
               xaccelero[i] =xAccl;
               yaccelero[i] =yAccl;
                  for (int j=0 ; j<count ;j++){
                     totalgz = totalgz + zaxis[j];   
                     totalgx = totalgx+ xaxis[j];
                     totalgy = totalgy + yaxis[j];
                     totalz = totalz + zaccelero[j];   
                     totalx = totalx+ xaccelero[j];
                     totaly = totaly + yaccelero[j];
                  }
                   double purataz = totalz/count; 
                   double puratax = totalx/count; 
                   double puratay = totaly/count;
                   double puratagz = totalgz/count; 
                   double puratagx = totalgx/count; 
                   double puratagy = totalgy/count; 
                   totalz = 0;
                   totalx = 0;
                   totaly = 0;
                   totalgz = 0;
                   totalgx = 0;
                   totalgy = 0;
                    i++;
              
                    if (i==count){
                      i=0;
                    }
              
                Serial.print(puratagz);
                Serial.print(",");
                Serial.println(puratagx);
                if (puratagz >= 313 && puratagx >= 305 )
                {
                  delay(1000);
                    // Start I2C transmission
            Wire.beginTransmission(Addr);
             //Select data register
            Wire.write(0x43);
            // Stop I2C transmission
            Wire.endTransmission();
          
            // Request 6 bytes of data
            Wire.requestFrom(Addr, 6);
          
            // Read 6 byte of data
            if (Wire.available() == 6)
            {
              data[0] = Wire.read();
              data[1] = Wire.read();
              data[2] = Wire.read();
              data[3] = Wire.read();
              data[4] = Wire.read();
              data[5] = Wire.read();
          
            }
            // Convert the data
            int xGyro = data[0] * .256 + data[1];
            int yGyro = data[2] * .256 + data[3];
            int zGyro = data[4] * .256 + data[5];
          
          
          
           zaxis[i] = zGyro;
           xaxis[i] =xGyro;
           yaxis[i] =yGyro;
           zaccelero[i] = zAccl;
           xaccelero[i] =xAccl;
           yaccelero[i] =yAccl;
              for (int j=0 ; j<count ;j++){
                 totalgz = totalgz + zaxis[j];   
                 totalgx = totalgx+ xaxis[j];
                 totalgy = totalgy + yaxis[j];
                 totalz = totalz + zaccelero[j];   
                 totalx = totalx+ xaccelero[j];
                 totaly = totaly + yaccelero[j];
              }
               double purataz = totalz/count; 
               double puratax = totalx/count; 
               double puratay = totaly/count;
               double puratagz = totalgz/count; 
               double puratagx = totalgx/count; 
               double puratagy = totalgy/count; 
               totalz = 0;
               totalx = 0;
               totaly = 0;
               totalgz = 0;
               totalgx = 0;
               totalgy = 0;
                i++;
          
                if (i==count){
                  i=0;
                }
          
            Serial.print(puratagz);
            Serial.print(",");
            Serial.println(puratagx);
        if (puratagz >= 313 && puratagx >= 305 )
         {
      
                digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
                Serial.println("Fall Detected");
                //delay(100);
                  Serial.println("scan start");
            
              // WiFi.scanNetworks will return the number of networks found
              int n = WiFi.scanNetworks();
              Serial.println("scan done");
              if (n == 0)
                Serial.println("no networks found");
              else
              {
                Serial.print(n);
                Serial.println(" networks found");
                for (int i = 0; i < 4; ++i)
                {
                 
                  // Print SSID and RSSI for each network found
                  Serial.print(i + 1);
                  Serial.print(": ");
                  if((WiFi.SSID(i)== "aifara")>(WiFi.SSID(i)== "samkickz"))
                  {
                    if((WiFi.SSID(i)== "aifara")>(WiFi.SSID(i)== "Zzzz"))
                    {
                  Serial.print(WiFi.SSID(i));
                  Serial.print(" (");
                  Serial.print(WiFi.RSSI(i));
                  Serial.print(")");
                  Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
                  Power=WiFi.RSSI(i);
                  Distance=(-(Power+70.1157)/1.8032)+29;
                  Serial.print("Distance=");
                  Serial.println(Distance);
                  Blynk.connect();
                  Blynk.virtualWrite(V0,Distance);
                  lcd.clear(); //Use it to clear the LCD Widget
                  lcd.print(2, 0, "Patient Fall"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
                  lcd.print(3, 1, "Near Toilet");
                  delay(10000);
                  lcd.clear();
                  Blynk.disconnect();
                    }
                  }
                  else if((WiFi.SSID(i)== "samkickz")>(WiFi.SSID(i)== "aifara"))
                  {
                    if((WiFi.SSID(i)== "samkickz")>(WiFi.SSID(i)== "Zzzz"))
                    {
                  Serial.print(WiFi.SSID(i));
                  Serial.print(" (");
                  Serial.print(WiFi.RSSI(i));
                  Serial.print(")");
                  Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
                  Power=WiFi.RSSI(i);
                  Distance=(-(Power+70.1157)/1.8032)+29;
                  Serial.print("Distance=");
                  Serial.println(Distance);
                  Blynk.connect();
                  Blynk.virtualWrite(V0,Distance);
                  lcd.clear(); //Use it to clear the LCD Widget
                  lcd.print(2, 0, "Patient Fall"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
                  lcd.print(3, 1, "Near Stair");
                  delay(10000);
                  lcd.clear();
                  Blynk.disconnect();
                    }
                  }
                  else if((WiFi.SSID(i)== "Zzzz")>(WiFi.SSID(i)== "aifara"))
                  {
                    if((WiFi.SSID(i)== "Zzzz")>(WiFi.SSID(i)== "samkickz"))
                    {
                  Serial.print(WiFi.SSID(i));
                  Serial.print(" (");
                  Serial.print(WiFi.RSSI(i));
                  Serial.print(")");
                  Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
                  Power=WiFi.RSSI(i);
                  Distance=(-(Power+70.1157)/1.8032)+29;
                  Serial.print("Distance=");
                  Serial.println(Distance);
                  Blynk.connect();
                  Blynk.virtualWrite(V0,Distance);
                  lcd.clear(); //Use it to clear the LCD Widget
                  lcd.print(2, 0, "Patient Fall"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
                  lcd.print(1, 1, "Near Corridor");
                  delay(10000);
                  lcd.clear();
                  Blynk.disconnect();
                   }
                  }
                  else if(WiFi.SSID(i)== "Xperia Z1_95b7")
                  {
                  Serial.print(WiFi.SSID(i));
                  Serial.print(" (");
                  Serial.print(WiFi.RSSI(i));
                  Serial.print(")");
                  Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
                  Power=WiFi.RSSI(i);
                  Distance=(-(Power+70.1157)/1.8032)+29;
                  Serial.print("Distance=");
                  Serial.println(Distance);
                  Blynk.connect();
                  Blynk.virtualWrite(V0,Distance);
                  lcd.clear(); //Use it to clear the LCD Widget
                  lcd.print(2, 0, "Patient Fall"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
                  lcd.print(5, 1, "At Stair");
                  delay(10000);
                  lcd.clear();
                  Blynk.disconnect();
                  }
                  
                  else
                  {
                    Serial.println(" ");
                  }
                  
                  delay(10);
                }
              }
              Serial.println("");
        }
        else Serial.print("Accidently drop");
      }
      else Serial.print("Accidently drop");
     }
     else Serial.print("Accidently drop");
    }
    
    else
    {
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    //delay(100);
    }
    
  
  Serial.println("");

  // Wait a bit before scanning again
 // delay(1000);
      
}

void setup()
{
 pinMode(13, OUTPUT);
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  //Blynk.begin(auth, ssid, pass);
  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select gyroscope configuration register
  Wire.write(0x1B);
  // Full scale range = 2000 dps
  Wire.write(0x18);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select accelerometer configuration register
  Wire.write(0x1C);
  // Full scale range = +/-16g
  Wire.write(0x18);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select power management register
  Wire.write(0x6B);
  // PLL with xGyro reference
  Wire.write(0x01);
  // Stop I2C transmission
  Wire.endTransmission();

//  timer.setInterval(10L, myTimerEvent); //  Here you set interval (1sec) and which function to call
}

void loop()
{  
    
   
  //Blynk.run();
 // timer.run(); // SimpleTimer is working
    unsigned int data[6];

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x3B);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);

  // Read 6 byte of data
  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }

  // Convert the data
  int xAccl = data[0] * .256 + data[1];
  int yAccl = data[2] * .256 + data[3];
  int zAccl = data[4] * .256 + data[5];



  // Start I2C transmission
  Wire.beginTransmission(Addr);
   //Select data register
  Wire.write(0x43);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);

  // Read 6 byte of data
  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();

  }
  // Convert the data
  int xGyro = data[0] * .256 + data[1];
  int yGyro = data[2] * .256 + data[3];
  int zGyro = data[4] * .256 + data[5];



 zaxis[i] = zGyro;
 xaxis[i] =xGyro;
 yaxis[i] =yGyro;
 zaccelero[i] = zAccl;
 xaccelero[i] =xAccl;
 yaccelero[i] =yAccl;
    for (int j=0 ; j<count ;j++){
       totalgz = totalgz + zaxis[j];   
       totalgx = totalgx+ xaxis[j];
       totalgy = totalgy + yaxis[j];
       totalz = totalz + zaccelero[j];   
       totalx = totalx+ xaccelero[j];
       totaly = totaly + yaccelero[j];
    }
     double purataz = totalz/count; 
     double puratax = totalx/count; 
     double puratay = totaly/count;
     double puratagz = totalgz/count; 
     double puratagx = totalgx/count; 
     double puratagy = totalgy/count; 
     totalz = 0;
     totalx = 0;
     totaly = 0;
     totalgz = 0;
     totalgx = 0;
     totalgy = 0;
      i++;

      if (i==count){
        i=0;
      }

  Serial.print(puratagz);
  Serial.print(",");
  Serial.println(puratagx);
  Serial.print(purataz);
  Serial.print(puratax);
  Serial.print(puratay);

const int xpin = puratax; 
const int ypin = puratay;
const int zpin = purataz;

float val_x, val_y, val_z;

//int count_x, count_y, count_z;
//char flag_x, flag_y, flag_z;
//char prev_flag_x, prev_flag_y, prev_flag_z;
char axis;

double X=0;
  double Y=0;
  double Z=0;
  double R=0;
  double J=0;
  int x = xpin;
  delay(1); 
  int y = ypin;
  delay(1); 
  int z = zpin;
  //zero_G is the reading we expect from the sensor when it detects
  //no acceleration.  Subtract this value from the sensor reading to
  //get a shifted sensor reading.
  float zero_G = 512.0; 
  //scale is the number of units we expect the sensor reading to
  //change when the acceleration along an axis changes by 1G.
  //Divide the shifted sensor reading by scale to get acceleration in Gs.
  float scale = 102.3;
  static unsigned int count2=0;
  if(++count2>50){
  val_x = (((float)x - 500)/scale);
  val_y = (((float)y - 508)/scale);
  val_z = (((float)z - 635.0)/scale);
 

  
  
   X = abs(val_x*val_x);
   Y = abs(val_y*val_y);
   Z = abs(val_z*val_z);
   R= (X+Y+Z);


   
    J = sqrt (R);
    Serial.print(x);
    Serial.print("\t");
    Serial.print(y);
    Serial.print("\t");
    Serial.print(z);
    Serial.print("\t ");
    Serial.print(val_x);
    Serial.print("\t");
    Serial.print(val_y);
    Serial.print("\t");
    Serial.print(val_z);
    Serial.print("\t ");
    Serial.println(R);

//    Serial.print(count_x);
//    Serial.print("\t");
//    Serial.print(count_y);
//    Serial.print("\t");
//    Serial.print(count_z);
//    Serial.print("\t ");
    Serial.print(J);
    Serial.print("\n");
    count2=0;

  }

}




