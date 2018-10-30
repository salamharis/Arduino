#include "QuickStats.h"
#include <SimpleTimer.h> // here is the SimpleTimer library
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>//import necessary libraries: SoftwareSerial, Wire
#include <EEPROM.h>

const int OUT_PIN1 = A1;
const int IN_PIN1 = A0;
const int OUT_PIN2 = A2;
const int IN_PIN2 = A3;
const int OUT_PIN3 = A4;
const int IN_PIN3 = A5;
const int OUT_PIN4 = A6;
const int IN_PIN4 = A7;
const int BUTTON = 2;
const float IN_STRAY_CAP_TO_GND = 24.48;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND;
const float R_PULLUP = 34.8;  
const int MAX_ADC_VALUE = 1023;
int v1 = 0;


SoftwareSerial I2CBT(0,1);//define PIN11 and PIN10 as RX and TX

void setup(){
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  
  
  Serial.begin(57600); //set USB baudrate: 9600
  I2CBT.begin(57600);     //BT baudrate: 57600(Warning!! baudrate of each BT module may differ, 
                          //please check the data sheet first!!

}


void loop(){
  //Serial.print("connected");

  int input1 = digitalRead(A0);
  int input2 = digitalRead(A1);
  int input3 = digitalRead(A2);

  if(input1 == HIGH){
  Serial.print('1');  //send value 1 to other bluetooth receiver
  delay(100);
  }
 else if(input2 == HIGH){
    Serial.print('2');
    delay(100);
  }
 else if(input3 == HIGH){
    Serial.print('3');
    delay(100);
  }
 
//  delay(100);
 }
  

  


