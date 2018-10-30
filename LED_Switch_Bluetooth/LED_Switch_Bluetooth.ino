#include <SoftwareSerial.h>
#include <Servo.h>



SoftwareSerial slave(0, 1); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
Servo myservo;  // create servo object to control a servo

void setup() 
{

//    pinMode(2,OUTPUT);
//    pinMode(3,OUTPUT);
//    pinMode(4,OUTPUT);
    // start the serial communication with the host computer
    Serial.begin(57600);
    Serial.println("Arduino with HC-06 is ready");

    // start communication with the HC-05 using 9600
    slave.begin(57600);  
    Serial.println("BTserial started at 9600");

    
  myservo.attach(2);  // attaches the servo on pin 9

}
char val;
boolean state = false;
void loop()
{

    if (slave.available())
    {  
      
     val = char(slave.read());

        Serial.println(val);
 
          if (val == '1')
          {
//            digitalWrite(2,HIGH);
//            digitalWrite(3,LOW);
//            digitalWrite(4,LOW);
            myservo.write(30);
//            delay(500);
          }
          else if (val == '2')
          {
//            digitalWrite(2,LOW);
//            digitalWrite(3,HIGH);
//            digitalWrite(4,LOW);
            myservo.write(60);
//            delay(500);
          }
          else if (val == '3')
          {
//            digitalWrite(2,LOW);
//            digitalWrite(3,LOW);
//            digitalWrite(4,HIGH);
            myservo.write(90);
//            delay(500);
          }
//
//          if(state == true){
//            myservo.write(90);
//            digitalWrite(2,HIGH);
//            digitalWrite(3,LOW);
//            digitalWrite(4,LOW);
//          }
//          else{
//            myservo.write(0);
//            digitalWrite(2,LOW);
//            digitalWrite(3,LOW);
//            digitalWrite(4,LOW);
//          }
         
         
//       delay(500); 
       Serial.end();    // Ends the serial communication once all data is received
     Serial.begin(57600);  // Re-establishes serial communication , this causes deletion of anything previously stored in the buffer      
    }
   // myservo.write(0);
}
