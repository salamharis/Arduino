#include "QuickStats.h"
//#include <SoftwareSerial.h>
//#include <Wire.h>//import necessary libraries: SoftwareSerial, Wire
//#include <EEPROM.h>
//#include <ResponsiveAnalogRead.h>
#include <SPI.h>
#include <BLEPeripheral.h>
#include "BLESerial.h"
#include <Adafruit_Microbit.h>

#define SERVO_PIN1         14  // Any pin on the Arduino or Mega will work.
#define SERVO_PIN2         15
#define SERVO_PIN3         16

Adafruit_Microbit_Matrix microbit;



const int OUT_PIN1 = 6;
const int IN_PIN1 = 0;
const int IN_PIN2 = 1;
const int IN_PIN3 = 2;
const int IN_PIN4 = 3;
const int IN_PIN5 = 4;
const int IN_PIN6 = 10;

int movestate = 0;



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
  pinMode(SERVO_PIN1, OUTPUT);
  pinMode(SERVO_PIN2, OUTPUT);
  pinMode(SERVO_PIN3, OUTPUT);
  
}


int capacitance;
int capacitanceRead1=0,capacitanceRead2=0,capacitanceRead3=0,capacitanceRead4=0,capacitanceRead5=0,capacitanceRead6=0;
int savedValue1[5]={0};
int savedValue2[5]={0};
int savedValue3[5]={0};
int savedValue4[5]={0};
int savedValue5[5]={0};
int savedValue6[5]={0}; //the array is to differentiate type of gestures

#define NUMSAMPLES 30 // number of measurements to make per data point


int lenMicroSecondsOfPeriod = 20 * 1000; // 20 milliseconds (ms)
int lenMicroSecondsOfPulse0 = 0.5 * 1000; // 1.0 ms is 0 degrees
int lenMicroSecondsOfPulse180 = 1.8 * 1000; // 2.0 ms is 180 degrees

void loop() {



//       capacitanceRead1 = getMes(NUMSAMPLES,IN_PIN1); // get a measurement;
//       Serial.print(capacitanceRead1); 
//       Serial.print(",");
//       capacitanceRead2 = getMes(NUMSAMPLES,IN_PIN2); // get a measurement;
//       Serial.print(capacitanceRead2); 
//       Serial.print(",");
//       capacitanceRead3 = getMes(NUMSAMPLES,IN_PIN3); // get a measurement;
//       Serial.print(capacitanceRead3); 
//       Serial.print(",");
//       capacitanceRead4 = getMes(NUMSAMPLES,IN_PIN4); // get a measurement;
//       Serial.print(capacitanceRead4); 
//       Serial.print(",");
//       capacitanceRead5 = getMes(NUMSAMPLES,IN_PIN5); // get a measurement;
//       Serial.print(capacitanceRead5); 
//       Serial.print(",");
       capacitanceRead6 = getMes(NUMSAMPLES,IN_PIN6); // get a measurement;
       Serial.print(capacitanceRead6); 
       Serial.println("");


       receiveBleValue(capacitanceRead1, capacitanceRead2, capacitanceRead3, capacitanceRead4, capacitanceRead5, capacitanceRead6);
       gestureDetect();
     // spam();
   
       
  }


float getMes(int samples,int IN_PIN) { // routine that takes #samples, filters out NaN values, drops values outside 1.645*standard deviations of mean
      float mData[NUMSAMPLES]; // to hold measured data from thermocouple
      int cCount=0; // number actually collected
      for(int i=0;i<samples;i++){ //Collect #samples measurements

          //float measured=analogRead(sensorPin); // take a single reading
          //measured=measured*5.0/1023.0; // convert to a voltage
          float measured = capacitancevalue(IN_PIN);
             
          if(isnan(measured)==0){ // filters out NaN values (not applicable to analogRead, but handy for other measurements)
            mData[cCount]=measured; //record measurement to mData array
            cCount++;
        }
      }
      
      float avg=stats.average(mData,cCount); // get average of measured data
      float sd=stats.stdev(mData,cCount); // get standard deviation of measured data
      int oCount=0; // counter for filtered reads
      for(int i=0;i<cCount;i++){ //Remmove outliers from the data points:
          if(abs(avg-mData[i])<1.645*sd){  // filter out readings more than 1.645*sd from the mean 
              mData[oCount]=mData[i]; // overwrite original array with filtered data
              oCount++;
        }
      }
      //uncomment to see how much filtering is going on, and how the average was affected:
      //Serial.println("Avg: "+(String)avg+" SD: "+(String)sd+"cCount: "+(String)cCount+" oCount: "+(String)oCount);
      if(sd==0){
          return avg; // protects against a zero standard deviation
      } else {
          return stats.average(mData,oCount); // average filter
      }
}


int capacitancevalue(int InputPin){

       pinMode(InputPin, INPUT);
       digitalWrite(OUT_PIN1, HIGH);
       delay(15);
       
       capacitance = analogRead(InputPin);
         
       digitalWrite(OUT_PIN1, LOW);
       pinMode(InputPin, OUTPUT);
       delay(15);
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
        int gesture = 3;
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
    rangeValue2 = 15, 
    rangeValue3 = 20, 
    rangeValue4 = 15, 
    rangeValue5 = 15, 
    rangeValue6 = 10;

int gestureDetect(){
   if (rangeDecider(1))
      {
        Serial.print("Hand Gesture 1 Detected");
        if(movestate != 1){
          rotateAntiClockWise(SERVO_PIN1);
          
              if(movestate == 2){   //reset the other servo
              rotateAntiClockWise(SERVO_PIN2);  
              movestate = 0;
            }
            else if(movestate == 3){
              rotateClockWise(SERVO_PIN3); 
              movestate = 0; 
            }
            movestate = 1;
          
        }
      }
   else if (rangeDecider(2))
      {
        Serial.print("Hand Gesture 2 Detected");
        if(movestate != 2){
          rotateClockWise(SERVO_PIN2);  
              if(movestate == 1){
              rotateClockWise(SERVO_PIN1);
              movestate = 0;
              }
              else if(movestate == 3){
              rotateClockWise(SERVO_PIN3); 
              movestate = 0; 
              }
          movestate = 2;
        }  
      }
   else if (rangeDecider(3))
      {
        Serial.print("Hand Gesture 3 Detected");
        if(movestate != 3){
          rotateAntiClockWise(SERVO_PIN3); 

              if(movestate == 1){
                rotateClockWise(SERVO_PIN1);
                movestate = 0;
              }
              else if(movestate == 2){
                rotateAntiClockWise(SERVO_PIN2);  
                movestate = 0;
              }
          movestate = 3; 
        }  
      }
   else
      {
        Serial.print("No Hand Gesture Detected");
        if(movestate == 1){
          rotateClockWise(SERVO_PIN1);
          movestate = 0;
        }
        else if(movestate == 2){
          rotateAntiClockWise(SERVO_PIN2);  
          movestate = 0;
        }
        else if(movestate == 3){
          rotateClockWise(SERVO_PIN3); 
          movestate = 0; 
        }
      }
   
}


bool rangeDecider(int gesture){
  if (capacitanceRead1 >= savedValue1[gesture]-rangeValue1 && capacitanceRead1 <= savedValue1[gesture]+rangeValue1 && 
      capacitanceRead2 >= savedValue2[gesture]-rangeValue2 && capacitanceRead2 <= savedValue2[gesture]+rangeValue2 &&
      capacitanceRead3 >= savedValue3[gesture]-rangeValue3 && capacitanceRead3 <= savedValue3[gesture]+rangeValue3 &&
      capacitanceRead4 >= savedValue4[gesture]-rangeValue4 && capacitanceRead4 <= savedValue4[gesture]+rangeValue4 &&
      capacitanceRead5 >= savedValue5[gesture]-rangeValue5 && capacitanceRead5 <= savedValue5[gesture]+rangeValue5 &&
      capacitanceRead6 >= savedValue6[gesture]-rangeValue6 && capacitanceRead6 <= savedValue6[gesture]+rangeValue6)
      {
        return true;
      }
   else
      {
        return false;
      }
}



void rotateAntiClockWise(int SERVO_PIN){
    for(int i=0;i<=10;i++){
      digitalWrite(SERVO_PIN, HIGH);
      
       // Delay for the length of the pulse
       delayMicroseconds(lenMicroSecondsOfPulse0);
      
       // Turn the voltage low for the remainder of the pulse
       digitalWrite(SERVO_PIN, LOW);
      
       // Delay this loop for the remainder of the period so we don't
       // send the next signal too soon or too late
       delayMicroseconds(lenMicroSecondsOfPeriod - lenMicroSecondsOfPulse0);
       delay(50);
    }
}



void rotateClockWise(int SERVO_PIN){
     for(int i=0;i<=10;i++){
       digitalWrite(SERVO_PIN, HIGH);
      
       // Delay for the length of the pulse
       delayMicroseconds(lenMicroSecondsOfPulse180);
      
       // Turn the voltage low for the remainder of the pulse
       digitalWrite(SERVO_PIN, LOW);
      
       // Delay this loop for the remainder of the period so we don't
       // send the next signal too soon or too late
       delayMicroseconds(lenMicroSecondsOfPeriod - lenMicroSecondsOfPulse180); 
       delay(50);
     }
     
}


