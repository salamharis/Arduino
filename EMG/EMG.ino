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
float appdata[10];
int a =0;
int b =1;
int TIME=0;

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
  Serial.println(a);
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(A0);    //read the sensor value using ADC
   
  EMA_S_low = (EMA_a_low*sensorValue) + ((1-EMA_a_low)*EMA_S_low);  //run the EMA
  EMA_S_high = (EMA_a_high*sensorValue) + ((1-EMA_a_high)*EMA_S_high);
   
  highpass = sensorValue - EMA_S_low;     //find the high-pass as before (for comparison)
  bandpass = EMA_S_high - EMA_S_low;      //find the band-pass
 
//Serial.print(highpass);
//Serial.print(" ");
//  Serial.println(bandpass);
  appdata[a]=bandpass;
  a+=2;
  appdata[b]=TIME;
  b+=2;
  TIME += 1;

  
  
  
  values[i] = bandpass;
  if((values[i]-values[i-1])>10){       //range spontenous increase
    i=i+1;
    for(int j=1;j<20;j++){
       sensorValue = analogRead(A0);    //read the sensor value using ADC
   
        EMA_S_low = (EMA_a_low*sensorValue) + ((1-EMA_a_low)*EMA_S_low);  //run the EMA
        EMA_S_high = (EMA_a_high*sensorValue) + ((1-EMA_a_high)*EMA_S_high);
         
        highpass = sensorValue - EMA_S_low;     //find the high-pass as before (for comparison)
        bandpass = EMA_S_high - EMA_S_low;      //find the band-pass
       
       // Serial.println(bandpass);
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
       // Serial.print("MAX :");
       // Serial.println(MAX); 
        MAX = map(MAX,0,40,0,255);
        bunyi();
        
        appdata[a]=MAX;
        a+=2;
        appdata[b]=TIME;
        b+=2;
        TIME += 1;
    
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
if(a>8){
    Serial.print('#');  //start trnasmission
    Serial.print(appdata[0]);
    Serial.print('+');
    Serial.print(appdata[1]);
    Serial.print('+');
    Serial.print(appdata[2]);
    Serial.print('+');
    Serial.print(appdata[3]);
    Serial.print('+');
    Serial.print(appdata[4]);
    Serial.print('+');
    Serial.print(appdata[5]);
    Serial.print('+');
    Serial.print(appdata[6]);
    Serial.print('+');
    Serial.print(appdata[7]);
    Serial.print('+');
    Serial.print(appdata[8]);
    Serial.print('+');
    Serial.print(appdata[9]);
    //Serial.print('~');   //used as an end of transmission character - used in app for string length
    a=0;
    b=0;
    //delay(100);
  }
  delay(100);

}

void bunyi()
{
  analogWrite(buzzer,MAX);
  delay(200);
  analogWrite(buzzer,0);
}




