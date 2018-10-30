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

int MIN = 0;
int MAX = 0;
int n = 50;
float values[50];
int i = 0;

int  sensorValue;

QuickStats stats; //initialize an instance of this class

void setup() {
  // put your setup code here, to run once:
Serial.begin(57600);
 EMA_S_low = analogRead(A0);      //set EMA S for t=1
 EMA_S_high = analogRead(A0);
}

void loop() {
  // put your main code here, to run repeatedly:
  values[i] = readsensor();
  if((values[i]-values[i-1])>10){       //range spontenous increase
        i = i+1;                        
        values[i] = readsensor();      //input data to next array 
     
      while((values[i]-values[i-1])>0){    //to record the reading until the reading decrease
        i = i+1;
        values[i] = readsensor();
        
        for(int j=0;j<50;j++){
          values[j-1]=values[j];    //shift the value to the previous array
         }
          
        DELAY();
        if(i==49){          //reset array to 0 when reach 50 element
          i=0;
        }

        
      }  
        //MIN = stats.minimum(values,n);
        //Serial.print("MIN :");
        //Serial.println(MIN);
        MAX = stats.maximum(values,50);
        Serial.print("MAX :");
        Serial.println(MAX); 
    
  }

        for(int j=0;j<50;j++){
          values[j-1]=values[j];    //shift the value to the previous array
         }
  
  i = i+1;
  if(i==49){
    i=0;
  }
DELAY();
}



int readsensor(){
  sensorValue = analogRead(A0);    //read the sensor value using ADC
   
  EMA_S_low = (EMA_a_low*sensorValue) + ((1-EMA_a_low)*EMA_S_low);  //run the EMA
  EMA_S_high = (EMA_a_high*sensorValue) + ((1-EMA_a_high)*EMA_S_high);
   
  highpass = sensorValue - EMA_S_low;     //find the high-pass as before (for comparison)
  bandpass = EMA_S_high - EMA_S_low;      //find the band-pass
 
//Serial.print(highpass);
//Serial.print(" ");
  Serial.println(bandpass);
  return(bandpass);
}


void DELAY(){
  //check delay untuk 20ms
           time1 = micros();
        //  prints time since program started
        //  time1 = millis();
        //  Serial.println(time1-time0);
          time0 = micros();
          delay(50);                              //19ms delay dlm mili
          delayMicroseconds(811);                 //19191-20000
        //int Value = analogRead(A0);
        //Serial.println(Value);
        //delay(0.2);
}

