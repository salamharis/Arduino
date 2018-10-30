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
int capacitanceRead1,capacitanceRead2,capacitanceRead3,capacitanceRead4,capacitanceRead5,capacitanceRead6;
int FcapacitanceRead1,FcapacitanceRead2,FcapacitanceRead3,FcapacitanceRead4,FcapacitanceRead5,FcapacitanceRead6;
int savedValue1[5]={0};
int savedValue2[5]={0};
int savedValue3[5]={0};
int savedValue4[5]={0};
int savedValue5[5]={0};
int savedValue6[5]={0}; //the array is to differentiate type of gestures

#define NUMSAMPLES 10 // number of measurements to make per data point


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
//       capacitanceRead6 = getMes(NUMSAMPLES,IN_PIN6); // get a measurement;
//       Serial.print(capacitanceRead6); 
//       Serial.println("");

       getMes(NUMSAMPLES,IN_PIN1); // get a measurement;
       Serial.print(FcapacitanceRead1);
       Serial.print(",");
       Serial.print(FcapacitanceRead2);
       Serial.print(",");
//       Serial.print(FcapacitanceRead3);
//       Serial.print(",");
       Serial.println(FcapacitanceRead4);
//       Serial.print(",");
//       Serial.print(FcapacitanceRead5);
//       Serial.print(",");
//       Serial.println(FcapacitanceRead6);
       //Serial.println("");


       receiveBleValue(FcapacitanceRead1, FcapacitanceRead2, FcapacitanceRead3, FcapacitanceRead4, FcapacitanceRead5, FcapacitanceRead6);
       gestureDetect();
   
       
  }


float getMes(int samples,int IN_PIN) { // routine that takes #samples, filters out NaN values, drops values outside 1.645*standard deviations of mean
      float mData1[NUMSAMPLES]; // to hold measured data from thermocouple
      float mData2[NUMSAMPLES]; // to hold measured data from thermocouple
      float mData3[NUMSAMPLES]; // to hold measured data from thermocouple
      float mData4[NUMSAMPLES]; // to hold measured data from thermocouple
      float mData5[NUMSAMPLES]; // to hold measured data from thermocouple
      float mData6[NUMSAMPLES]; // to hold measured data from thermocouple
      int cCount1=0,cCount2=0,cCount3=0,cCount4=0,cCount5=0,cCount6=0; // number actually collected
      for(int i=0;i<samples;i++){ //Collect #samples measurements

          //float measured=analogRead(sensorPin); // take a single reading
          //measured=measured*5.0/1023.0; // convert to a voltage
          //float measured = capacitancevalue(IN_PIN);
          capacitanceRead1 = capacitancevalue(IN_PIN1);
          capacitanceRead2 = capacitancevalue(IN_PIN2);
          //capacitanceRead3 = capacitancevalue(IN_PIN3);
          capacitanceRead4 = capacitancevalue(IN_PIN4);
          //capacitanceRead5 = capacitancevalue(IN_PIN5);
          //capacitanceRead6 = capacitancevalue(IN_PIN6);
             
            if(isnan(capacitanceRead1)==0){ // filters out NaN values (not applicable to analogRead, but handy for other measurements)
              mData1[cCount1]=capacitanceRead1; //record measurement to mData array
              cCount1++;
            }
            if(isnan(capacitanceRead2)==0){ // filters out NaN values (not applicable to analogRead, but handy for other measurements)
              mData2[cCount2]=capacitanceRead2; //record measurement to mData array
              cCount2++;
            }
//            if(isnan(capacitanceRead3)==0){ // filters out NaN values (not applicable to analogRead, but handy for other measurements)
//              mData3[cCount3]=capacitanceRead3; //record measurement to mData array
//              cCount3++;
//            }
            if(isnan(capacitanceRead4)==0){ // filters out NaN values (not applicable to analogRead, but handy for other measurements)
              mData4[cCount4]=capacitanceRead4; //record measurement to mData array
              cCount4++;
            }
//            if(isnan(capacitanceRead5)==0){ // filters out NaN values (not applicable to analogRead, but handy for other measurements)
//              mData5[cCount5]=capacitanceRead5; //record measurement to mData array
//              cCount5++;
//            }
//            if(isnan(capacitanceRead6)==0){ // filters out NaN values (not applicable to analogRead, but handy for other measurements)
//              mData6[cCount6]=capacitanceRead6; //record measurement to mData array
//              cCount6++;
//            }
      }
      
      float avg1=stats.average(mData1,cCount1); // get average of measured data
      float avg2=stats.average(mData2,cCount2); // get average of measured data
      float avg3=stats.average(mData3,cCount3); // get average of measured data
      float avg4=stats.average(mData4,cCount4); // get average of measured data
      float avg5=stats.average(mData5,cCount5); // get average of measured data
      float avg6=stats.average(mData6,cCount6); // get average of measured data
      
      float sd1=stats.stdev(mData1,cCount1); // get standard deviation of measured data
      float sd2=stats.stdev(mData2,cCount2); // get standard deviation of measured data
      float sd3=stats.stdev(mData3,cCount3); // get standard deviation of measured data
      float sd4=stats.stdev(mData4,cCount4); // get standard deviation of measured data
      float sd5=stats.stdev(mData5,cCount5); // get standard deviation of measured data
      float sd6=stats.stdev(mData6,cCount6); // get standard deviation of measured data
      
      int oCount1=0,oCount2=0,oCount3=0,oCount4=0,oCount5=0,oCount6=0; // counter for filtered reads
      
            for(int i=0;i<cCount1;i++){ //Remmove outliers from the data points:
                if(abs(avg1-mData1[i])<1.645*sd1){  // filter out readings more than 1.645*sd from the mean 
                    mData1[oCount1]=mData1[i]; // overwrite original array with filtered data
                    oCount1++;
                }
            }
            for(int i=0;i<cCount2;i++){ //Remmove outliers from the data points:
                if(abs(avg2-mData2[i])<1.645*sd2){  // filter out readings more than 1.645*sd from the mean 
                    mData2[oCount2]=mData2[i]; // overwrite original array with filtered data
                    oCount2++;
                }
            }
            for(int i=0;i<cCount3;i++){ //Remmove outliers from the data points:
                if(abs(avg3-mData3[i])<1.645*sd3){  // filter out readings more than 1.645*sd from the mean 
                    mData3[oCount3]=mData3[i]; // overwrite original array with filtered data
                    oCount3++;
                }
            }
            for(int i=0;i<cCount4;i++){ //Remmove outliers from the data points:
                if(abs(avg4-mData4[i])<1.645*sd4){  // filter out readings more than 1.645*sd from the mean 
                    mData4[oCount4]=mData4[i]; // overwrite original array with filtered data
                    oCount4++;
                }
            }
            for(int i=0;i<cCount5;i++){ //Remmove outliers from the data points:
                if(abs(avg5-mData5[i])<1.645*sd5){  // filter out readings more than 1.645*sd from the mean 
                    mData5[oCount5]=mData5[i]; // overwrite original array with filtered data
                    oCount5++;
                }
            }
            for(int i=0;i<cCount6;i++){ //Remmove outliers from the data points:
                if(abs(avg6-mData6[i])<1.645*sd6){  // filter out readings more than 1.645*sd from the mean 
                    mData6[oCount6]=mData6[i]; // overwrite original array with filtered data
                    oCount6++;
                }
            }
            
      
      //uncomment to see how much filtering is going on, and how the average was affected:
      //Serial.println("Avg: "+(String)avg+" SD: "+(String)sd+"cCount: "+(String)cCount+" oCount: "+(String)oCount);
      if(sd1==0){
          FcapacitanceRead1 = avg1; // protects against a zero standard deviation
      } 
      else if(sd2==0){
          FcapacitanceRead2 = avg2;
      }
      else if(sd3==0){
          FcapacitanceRead3 = avg3;
      }
      else if(sd4==0){
          FcapacitanceRead4 = avg4;
      }
      else if(sd5==0){
          FcapacitanceRead5 = avg5;
      }
      else if(sd6==0){
          FcapacitanceRead6 = avg6;
      }
      else {
          FcapacitanceRead1 = stats.average(mData1,oCount1); // average filter
          FcapacitanceRead2 = stats.average(mData2,oCount2); // average filter
          FcapacitanceRead3 = stats.average(mData3,oCount3); // average filter
          FcapacitanceRead4 = stats.average(mData4,oCount4); // average filter
          FcapacitanceRead5 = stats.average(mData5,oCount5); // average filter
          FcapacitanceRead6 = stats.average(mData6,oCount6); // average filter
      }
}


int capacitancevalue(int InputPin){

       pinMode(InputPin, INPUT);
       digitalWrite(OUT_PIN1, HIGH);
       delay(25);
       
       capacitance = analogRead(InputPin);
         
       digitalWrite(OUT_PIN1, LOW);
       pinMode(InputPin, OUTPUT);
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



  

//the detection range
int rangeValue1 = 30, 
    rangeValue2 = 50, 
    rangeValue3 = 50, 
    rangeValue4 = 30, 
    rangeValue5 = 20, 
    rangeValue6 = 50;

int gestureDetect(){
   if (rangeDecider(1))
      {
        Serial.print("Hand Gesture 1 Detected");
        rotateAntiClockWise(SERVO_PIN1);
      }
   else if (rangeDecider(2))
      {
        Serial.print("Hand Gesture 2 Detected");
        rotateAntiClockWise(SERVO_PIN1);     
      }
   else if (rangeDecider(3))
      {
        Serial.print("Hand Gesture 3 Detected");
        rotateAntiClockWise(SERVO_PIN1);     
      }
   else
      {
        Serial.print("No Hand Gesture Detected");
        rotateClockWise(SERVO_PIN1);
      }
   
}


bool rangeDecider(int gesture){
  if (FcapacitanceRead1 >= savedValue1[gesture]-rangeValue1 && FcapacitanceRead1 <= savedValue1[gesture]+rangeValue1 && 
      FcapacitanceRead2 >= savedValue2[gesture]-rangeValue2 && FcapacitanceRead2 <= savedValue2[gesture]+rangeValue2 &&
      FcapacitanceRead3 >= savedValue3[gesture]-rangeValue3 && FcapacitanceRead3 <= savedValue3[gesture]+rangeValue3 &&
      FcapacitanceRead4 >= savedValue4[gesture]-rangeValue4 && FcapacitanceRead4 <= savedValue4[gesture]+rangeValue4 &&
      FcapacitanceRead5 >= savedValue5[gesture]-rangeValue5 && FcapacitanceRead5 <= savedValue5[gesture]+rangeValue5 &&
      FcapacitanceRead6 >= savedValue6[gesture]-rangeValue6 && FcapacitanceRead6 <= savedValue6[gesture]+rangeValue6)
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
   }
}


