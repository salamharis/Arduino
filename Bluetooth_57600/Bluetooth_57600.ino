#include <SoftwareSerial.h>
#include <Wire.h>//import necessary libraries: SoftwareSerial, Wire
#include <Servo.h>

SoftwareSerial I2CBT(0,1);//define PIN11 and PIN10 as RX and TX
Servo myservo;

void setup() {
  Serial.begin(57600); //set USB baudrate: 9600
  I2CBT.begin(9600);  
  //BT baudrate: 57600(Warning!! baudrate of each BT module may differ, 
  //please check the data sheet first!!
  pinMode(13, OUTPUT); //set pin 13 as output, where we put a LED
  myservo.attach(9);
}

void loop() {
  byte cmmd[20];
  int insize;
//  while(1){
    if ((insize=(I2CBT.available()))>0){ //read BT incoming message
      Serial.print("input size = ");
      Serial.println(insize);
      for (int i=0; i<insize; i++){
        Serial.print(cmmd[i]=char(I2CBT.read()));
        Serial.println(" ");
      }
    
//    switch (cmmd[0]) { //read the first character
    if(cmmd[0]=='a'){ //97 is 'a' in ASCII CODE
      digitalWrite(13,HIGH); //LED light up
      myservo.write(90);
    }//break;

   else if(cmmd[0]=='b'){ //97 is 'b' in ASCII CODE
      Serial.println("Get b");
      digitalWrite(13,LOW); //LED off
      myservo.write(0);
      }//break;
    }
//    } //Switch
//  } //while
}//loop
