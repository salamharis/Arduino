#include <SoftwareSerial.h>
#include <Servo.h>
#include "QuickStats.h"

QuickStats stats; //initialize an instance of this class
Servo myservo; 
SoftwareSerial slave(0, 1); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
int c = 0;
char val;
int num=5;
char reading[4];
void setup() 
{
    // start the serial communication with the host computer
    Serial.begin(57600);
    Serial.println("Arduino with HC-06 is ready");

    // start communication with the HC-05 using 9600
    slave.begin(57600);  
    Serial.println("BTserial started at 9600");

    myservo.attach(9);
}

void loop()
{

  Serial.println("connected");

    if (slave.available())
    {  
      //for(int i=0;i<num;i++){
        val= char(slave.read());
      //}
     // val = stats.mode(reading,numreading,0.00001);
        Serial.println(val);
//        val = map(val, 0, 1023, 0, 180);
//        myservo.write(val); 
          if (val == '1')
          {
            myservo.write(20);
          }
          else if (val == '2')
          {
            myservo.write(40);
          }
          else if (val == '3')
          {
            myservo.write(60);
          }
          else if (val == '4')
          {
            myservo.write(80);
          }
      //  delay(15);    
    }
   // myservo.write(0);
}
