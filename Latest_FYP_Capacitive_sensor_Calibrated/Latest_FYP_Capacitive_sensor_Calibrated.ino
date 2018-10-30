#include "QuickStats.h"
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
QuickStats stats; //initialize an instance of this class
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
  //initializeRatio();
}

int i = 0;
int n = 50;
int val[6][20]={0};

int capacitance;
float capacitanceRead1[20]={0},capacitanceRead2[20]={0},capacitanceRead3[20]={0},capacitanceRead4[20]={0},capacitanceRead5[20]={0},capacitanceRead6[20]={0};
int savedValue1[5]={0};
int savedValue2[5]={0};
int savedValue3[5]={0};
int savedValue4[5]={0};
int savedValue5[5]={0};
int savedValue6[5]={0}; //the array is to differentiate type of gestures
int initialcapacitance[6] = {0};
bool doneInit = false;
int smoothed[6];

void loop() {



       capacitanceRead1[i] = capacitancevalue(IN_PIN1,i,0);
       //smoothed[0] = stats.median(capacitanceRead1,20);// Median filter (choose which filter to use)
       smoothed[0] = stats.mode(capacitanceRead1,20,0.000001);// Mode filter (choose which filter to use)
       //smoothed[0] = stats.g_average(capacitanceRead1,20);// Gussian Mean filter (choose which filter to use)
       //smoothed[0] = stats.average(capacitanceRead1,20);// Mean filter (choose which filter to use)
       Serial.print(smoothed[0]); 
//       Serial.print(",");
//       capacitanceRead2[i] = capacitancevalue(IN_PIN2,i,1);
//       smoothed[1] = stats.average(capacitanceRead2,20);
//       Serial.print(smoothed[1]);
//       Serial.print(",");
//       capacitanceRead3[i] = capacitancevalue(IN_PIN3,i,2);
//       smoothed[2] = stats.average(capacitanceRead3,20);
//       Serial.print(smoothed[2]);
//       Serial.print(",");
//       capacitanceRead4[i] = capacitancevalue(IN_PIN4,i,3);
//       smoothed[3] = stats.average(capacitanceRead4,20);
//       Serial.print(smoothed[3]);
//       Serial.print(",");
//       capacitanceRead5[i] = capacitancevalue(IN_PIN5,i,4);
//       smoothed[4] = stats.average(capacitanceRead5,20);
//       Serial.print(smoothed[4]);
//       Serial.print(",");
//       capacitanceRead6[i] = capacitancevalue(IN_PIN6,i,5);
//       smoothed[5] = stats.average(capacitanceRead6,20);
//       Serial.print(smoothed[5]);
       Serial.println("");


       receiveBleValue(smoothed[0], smoothed[1], smoothed[2], smoothed[3], smoothed[4], smoothed[5]);
       gestureDetect();
     // spam();
     i++;
     if(i==19){
      i=0;
     }

       
  }



int capacitancevalue(int InputPin,int count,int Array){

       pinMode(InputPin, INPUT);
       digitalWrite(OUT_PIN1, HIGH);
       delay(25);
       
       capacitance = analogRead(InputPin);
       
//       float snapmultiplier = 0.5; //more smaller value more smooth
//       int snap = snapcurve(capacitance*snapmultiplier);
//
//       int smoothvalue = smoothvalue + capacitance*snap;
       
       
       digitalWrite(OUT_PIN1, LOW);
       pinMode(InputPin, OUTPUT);
//       smoothvalue = map(smoothvalue,0,1023,0,2047);
       //Serial.print(smoothvalue);
//       return smoothvalue;
       return capacitance;
         
 
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
    bleSerial.poll();
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
  if (smoothed[0] >= savedValue1[gesture]-rangeValue1 && smoothed[0] <= savedValue1[gesture]+rangeValue1 && 
      smoothed[1] >= savedValue2[gesture]-rangeValue2 && smoothed[1] <= savedValue2[gesture]+rangeValue2 &&
      smoothed[2] >= savedValue3[gesture]-rangeValue3 && smoothed[2] <= savedValue3[gesture]+rangeValue3 &&
      smoothed[3] >= savedValue4[gesture]-rangeValue4 && smoothed[3] <= savedValue4[gesture]+rangeValue4 &&
      smoothed[4] >= savedValue5[gesture]-rangeValue5 && smoothed[4] <= savedValue5[gesture]+rangeValue5 &&
      smoothed[5] >= savedValue6[gesture]-rangeValue6 && smoothed[5] <= savedValue6[gesture]+rangeValue6)
      {
        return true;
      }
   else
      {
        return false;
      }
}



int initializeRatio(){
  
       initialcapacitance[0] = capacitancevalue(IN_PIN1,i,0);
       Serial.print(",");
       initialcapacitance[1] = capacitancevalue(IN_PIN2,i,1);
       Serial.print(",");
       initialcapacitance[2] = capacitancevalue(IN_PIN3,i,2);
       Serial.print(",");
       initialcapacitance[3] = capacitancevalue(IN_PIN4,i,3);
       Serial.print(",");
       initialcapacitance[4] = capacitancevalue(IN_PIN5,i,4);
       Serial.print(",");
       initialcapacitance[5] = capacitancevalue(IN_PIN6,i,5);
       Serial.println("");
       doneInit = true;
}


