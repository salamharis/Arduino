//#include "QuickStats.h"
//#include <SimpleTimer.h> // here is the SimpleTimer library
//#include <Servo.h>
//#include <SoftwareSerial.h>
//#include <Wire.h>//import necessary libraries: SoftwareSerial, Wire
//#include <EEPROM.h>
//#include <ResponsiveAnalogRead.h>
#include <SPI.h>
#include <BLEPeripheral.h>
#include "BLESerial.h"
#include <Adafruit_Microbit.h>

Adafruit_Microbit_Matrix microbit;



const int OUT_PIN1 = 6;
const int IN_PIN1 = 0;
const int IN_PIN2 = 1;
const int IN_PIN3 = 2;
const int IN_PIN4 = 3;
const int IN_PIN5 = 4;
const int IN_PIN6 = 10;





//custom boards may override default pin definitions with BLESerial(PIN_REQ, PIN_RDY, PIN_RST)
BLESerial bleSerial;

//SoftwareSerial I2CBT(0,1);//define PIN11 and PIN10 as RX and TX
//QuickStats stats; //initialize an instance of this class
//SimpleTimer timer; // Create a Timer object called "timer"!
//Servo myservo;  // create servo object to control a servo





void setup() {
  // custom services and characteristics can be added as well
  bleSerial.setLocalName("Capacitive Sensor");
  
  Serial.begin(115200); //set USB baudrate: 9600
  bleSerial.begin();
  pinMode(IN_PIN1, OUTPUT);
  pinMode(IN_PIN2, OUTPUT);
  pinMode(IN_PIN3, OUTPUT);
  pinMode(IN_PIN4, OUTPUT);
  pinMode(IN_PIN5, OUTPUT);
  pinMode(IN_PIN6, OUTPUT);

  microbit.begin();
}

int i = 5;
int n = 50;
int val[6][150]={0};

int capacitance;
int capacitanceRead1,capacitanceRead2,capacitanceRead3,capacitanceRead4,capacitanceRead5,capacitanceRead6;
int savedValue1[5]={0};
int savedValue2[5]={0};
int savedValue3[5]={0};
int savedValue4[5]={0};
int savedValue5[5]={0};
int savedValue6[5]={0}; //the array is to differentiate type of gestures

void loop() {



       capacitanceRead1 = capacitancevalue(IN_PIN1,i,0);
//       Serial.print(",");
//       capacitanceRead2 = capacitancevalue(IN_PIN2,i,1);
//       Serial.print(",");
//       capacitanceRead3 = capacitancevalue(IN_PIN3,i,2);
//       Serial.print(",");
//       capacitanceRead4 = capacitancevalue(IN_PIN4,i,3);
//       Serial.print(",");
//       capacitanceRead5 = capacitancevalue(IN_PIN5,i,4);
//       Serial.print(",");
//       capacitanceRead6 = capacitancevalue(IN_PIN6,i,5);
       Serial.println("");


       bleSerial.poll();

       receiveBleValue(capacitanceRead1, capacitanceRead2, capacitanceRead3, capacitanceRead4, capacitanceRead5, capacitanceRead6);
       //gestureDetect();
     // spam();

       
  }



int capacitancevalue(int InputPin,int count,int Array){

       pinMode(InputPin, INPUT);
       digitalWrite(OUT_PIN1, HIGH);
       
       delay(25);
       
       capacitance = analogRead(InputPin);
 
       Serial.print(capacitance);
       digitalWrite(OUT_PIN1, LOW);
       pinMode(InputPin, OUTPUT);
       
       delay(25);
    
         
 
  }


  


  //for more info go to http://damienclarke.me/code/posts/writing-a-better-noise-reducing-analogread
  int snapcurve(float x){
    
    float y = 1/(x + 1);  //hyperbolic funtion
    y = (1 - y)*2; //to inverse the y value and to set the treshold
    if(y > 1){
      return 1;
    }
    else{
      return y;
    }
    
  }



  // forward received from Serial to BLESerial and vice versa
  void receiveBleValue(int a,int b,int c,int d,int e,int f) {
    if (bleSerial && Serial) {
      char dataBLE;
      //while ((dataBLE = bleSerial.read()) > 0) Serial.write((char)dataBLE);
     // while ((dataBLE = Serial.read()) > 0) bleSerial.write((char)dataBLE);
      dataBLE = bleSerial.read();
      //Serial.write(dataBLE);
      if(dataBLE == 'a'){
        int gesture = 1;
        savedValue1[gesture] = a; 
        savedValue2[gesture] = b;
        savedValue3[gesture] = c;
        savedValue4[gesture] = d;
        savedValue5[gesture] = e;
        savedValue6[gesture] = f;
        Serial.println("ble data gesture 1 receive");

        microbit.print(1);
        delay(1000);
        microbit.show(microbit.YES);
        delay(1000);
      }
      else if(dataBLE == 'b'){
        int gesture = 2;
        savedValue1[gesture] = a; 
        savedValue2[gesture] = b;
        savedValue3[gesture] = c;
        savedValue4[gesture] = d;
        savedValue5[gesture] = e;
        savedValue6[gesture] = f;
        Serial.println("ble data gesture 2 receive");

        microbit.print(2);
        delay(1000);
        microbit.show(microbit.YES);
        delay(1000);
      }
      else if(dataBLE == 'c'){
        int gesture = 2;
        savedValue1[gesture] = a; 
        savedValue2[gesture] = b;
        savedValue3[gesture] = c;
        savedValue4[gesture] = d;
        savedValue5[gesture] = e;
        savedValue6[gesture] = f;
        Serial.println("ble data gesture 3 receive");

        microbit.print(3);
        delay(1000);
        microbit.show(microbit.YES);
        delay(1000);
      }
    }
  }




  // periodically sent time stamps
  void spam() {
  if (bleSerial) {
    bleSerial.print(millis());
    bleSerial.println(" tick-tacks!");
    delay(1000);
    }
  }
  

//the detection range
int rangeValue1 = 50, 
    rangeValue2 = 50, 
    rangeValue3 = 50, 
    rangeValue4 = 50, 
    rangeValue5 = 50, 
    rangeValue6 = 50;

int gestureDetect(){
  if (rangeDecider(1))
      {
        Serial.print("Hand Gesture 1 Detected");
        
      }
   else if (rangeDecider(2))
      {
        Serial.print("Hand Gesture 2 Detected");
             
      }
   else if (rangeDecider(3))
      {
        Serial.print("Hand Gesture 3 Detected");
             
      }
   else
     {
      Serial.print("No Hand Gesture Detected");
     }
   
}


bool rangeDecider(int gesture){
  if (savedValue1[gesture] >= savedValue1[gesture]-rangeValue1 && savedValue1[gesture] <= savedValue1[gesture]+rangeValue1/* && 
      savedValue2[gesture] >= savedValue2[gesture]-rangeValue2 && savedValue2[gesture] <= savedValue2[gesture]+rangeValue2 &&
      savedValue3[gesture] >= savedValue3[gesture]-rangeValue3 && savedValue3[gesture] <= savedValue3[gesture]+rangeValue3 &&
      savedValue4[gesture] >= savedValue4[gesture]-rangeValue4 && savedValue4[gesture] <= savedValue4[gesture]+rangeValue4 &&
      savedValue5[gesture] >= savedValue5[gesture]-rangeValue5 && savedValue5[gesture] <= savedValue5[gesture]+rangeValue5 &&
      savedValue6[gesture] >= savedValue6[gesture]-rangeValue6 && savedValue6[gesture] <= savedValue6[gesture]+rangeValue6*/)
      {
        return true;
      }
   else
      {
        return false;
      }
}


