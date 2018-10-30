/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(0,1);   // set pin 0 as RX and pin 1 as TX
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position
boolean state = false;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(57600);
  BTSerial.begin(57600);
   myservo.write(pos); 
}

void loop() {

  if(Serial.available()>0){
    
    char val = char(BTSerial.read()); 

    
    if(val == '1'){
      state = !state;
    }
    if(state == true){
          
          if (pos >= 0) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          int fsr = analogRead(A0);   //read the fsr value
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          Serial.println(fsr);
          while(fsr > 1){
            fsr = analogRead(A0);   //read the fsr value
            myservo.write(pos);
            Serial.print(fsr);
          }
        delay(100);                       // waits 15ms for the servo to reach the position
        pos--;
     }
    }
    else {
          if (pos <= 90) { // goes from 180 degrees to 0 degrees
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(100);                       // waits 15ms for the servo to reach the position
          pos++;
    }
  }
 }
}

