#include "SevSeg.h"
#include <Time.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include <Wire.h>
int buzzer=A3;
const int increase = A2;
const int decrease = A0;
const int start = A1;
int i = 0;
int m = 0;
int s = 0;
int flag = 0;
SevSeg sevseg; //Instantiate a seven segment controller object

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(90);
  pinMode(buzzer,OUTPUT);
  pinMode(increase, INPUT);
  pinMode(decrease, INPUT);
  pinMode(start, INPUT);
  Serial.begin(57600);
}

void loop() {
  int time;
  time = m * 100;
  time += s;
  if (digitalRead(increase) == HIGH && flag == 0){
    m = m+1;
    sevseg.setNumber(time,2);
    sevseg.refreshDisplay(); // Must run repeatedly
    flag = 1;
  } else if (digitalRead(increase) == LOW && flag == 1){
    sevseg.setNumber(time,2);
    sevseg.refreshDisplay(); // Must run repeatedly
    flag = 0;
   } else if (digitalRead(decrease) == HIGH && flag == 0){
      m = m-1;
      flag = 2;
  } else if (digitalRead(decrease) == LOW && flag == 2){
      sevseg.setNumber(time,2);
      sevseg.refreshDisplay(); // Must run repeatedly
      flag = 0;
  }
  else if (digitalRead(start) == HIGH && flag == 0){
    int masa;
    setTime(0,59-m,s,1,1,17); // set time to Saturday 8:29:00am Jan 1 2017
    masa = minute()*100;
    masa += second();
    flag = 3;
  } else if (digitalRead(start) == LOW && flag == 3){
    countdown();
  }
  sevseg.setNumber(time,2);
  sevseg.refreshDisplay(); // Must run repeatedly
}

void countdown()
{
  int masa;
  masa = 5800-(minute()*100); //countdown for minute
  masa += 60-second();        //countdown for second
    if (masa < 001 && i>=0){
    alarm(3); //how many times alarm will be ringing
    flag = 0;
    }
  sevseg.setNumber(masa,2);
  sevseg.refreshDisplay(); // Must run repeatedly
}

void alarm(int z)
{
  while (i<z){
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
  delay(100);
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
  delay(1000);
  i=i+1;
  }
  i=0;
}

