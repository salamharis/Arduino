#include <Servo.h>

Servo myservo;  // create servo object to control a servo
float data =0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
myservo.attach(9);  // attaches the servo on pin 9 to the servo object
myservo.write(45); 
}

void loop() {
  // put your main code here, to run repeatedly:

if(Serial.available() > 0)  // Send data only when you receive data:
  {
    data = Serial.parseFloat();      //Read the incoming data and store it into variable data
    Serial.println(data);        //Print Value inside data in Serial monitor
  
    if(data == 1.23){            //Checks whether value of data is equal to 1 
     // record1 = stats.mode(capacitance,n,0.00001);  //Mode
      myservo.write(0);          
      delay(50);                       
      }
      else if(data == 2.03){       //Checks whether value of data is equal to 0
      // record2 = stats.mode(capacitance,n,0.00001);
      myservo.write(45);              
      delay(50);                      
      }
delay(100);
  }
 }
