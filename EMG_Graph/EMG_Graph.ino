#include <Filters.h>
#include "QuickStats.h"
#define Analog A0;
unsigned long time0;
unsigned long time1;

float EMA_a_low = 0.3;    //initialization of EMA alpha
float EMA_a_high = 0.5;
 
int EMA_S_low = 0;        //initialization of EMA S
int EMA_S_high = 0;
 
int highpass = 0.05;
int bandpass = 130;
int buzzer = 9;

int MIN = 0;
int MAX = 0;
int n = 20;
float values[20];
int i = 0;

int  sensorValue;

QuickStats stats; //initialize an instance of this class

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 EMA_S_low = analogRead(A0);      //set EMA S for t=1
 EMA_S_high = analogRead(A0);
 pinMode(buzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(A0);    //read the sensor value using ADC
   
  EMA_S_low = (EMA_a_low*sensorValue) + ((1-EMA_a_low)*EMA_S_low);  //run the EMA
  EMA_S_high = (EMA_a_high*sensorValue) + ((1-EMA_a_high)*EMA_S_high);
   
  highpass = sensorValue - EMA_S_low;     //find the high-pass as before (for comparison)
  bandpass = EMA_S_high - EMA_S_low;      //find the band-pass
 
//Serial.print(highpass);
//Serial.print(" ");
  //Serial.println(bandpass);
  
  values[i] = bandpass;
  if((values[i]-values[i-1])>10){       //range spontenous increase
    i=i+1;
    for(int j=1;j<20;j++){
       sensorValue = analogRead(A0);    //read the sensor value using ADC
   
        EMA_S_low = (EMA_a_low*sensorValue) + ((1-EMA_a_low)*EMA_S_low);  //run the EMA
        EMA_S_high = (EMA_a_high*sensorValue) + ((1-EMA_a_high)*EMA_S_high);
         
        highpass = sensorValue - EMA_S_low;     //find the high-pass as before (for comparison)
        bandpass = EMA_S_high - EMA_S_low;      //find the band-pass
       
        //Serial.println(bandpass);
        values[j] = bandpass;

            //check delay untuk 20ms
               time1 = micros();
            //  prints time since program started
            //  time1 = millis();
            //  Serial.println(time1-time0);
              time0 = micros();
              delay(19);                              //19ms delay dlm mili
              delayMicroseconds(811);                 //19191-20000
            //int Value = analogRead(A0);
            //Serial.println(Value);
            //delay(0.2);
    }
     
  
        //MIN = stats.minimum(values,n);
        //Serial.print("MIN :");
        //Serial.println(MIN);
        MAX = stats.maximum(values,20);
        //Serial.print("MAX :");
        //Serial.println(MAX);
        
        Serial.print('#');  //Start send to app
        Serial.print(MAX);  //Data that want to display on graph
        Serial.print(',');
        Serial.print(0);
        Serial.print('~'); //used as an end of transmission character - used in app for string length
        MAX = map(MAX,0,40,0,255);
        bunyi();
    
  }

    //check delay untuk 20ms
   time1 = micros();
//  prints time since program started
//  time1 = millis();
//  Serial.println(time1-time0);
  time0 = micros();
  delay(19);                              //19ms delay dlm mili
  delayMicroseconds(811);                 //19191-20000
//int Value = analogRead(A0);
//Serial.println(Value);
//delay(0.2);
if(i>0){
  i=0;
} 
}

void bunyi()
{
  analogWrite(buzzer,MAX);
  delay(200);
  analogWrite(buzzer,0);
}





