// The following program is an example of data smoothing using the QuickStats.h library in Arduino.

#include "QuickStats.h"

//byte sensorPin = A1;              // declaring the analog input to be Pin A1 of Arduino board.
int val = 0;
int v = 0;                        // variable to store analog reading
int NUMSAMPLES=20;               // number of samples to take for data smoothing 
float measurements[20];          // variable for holding raw measurements
float smoothed;                   // variable for holding filtered measurement
float smoothed2;
float smoothedCV;                 // variable for holding CV of measurements

const int OUT_PIN = A1;
const int IN_PIN = A0;
const int BUTTON = 2;
const float IN_STRAY_CAP_TO_GND = 24.48;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND;
const float R_PULLUP = 34.8;  
const int MAX_ADC_VALUE = 1023;

QuickStats stats; //initialize an instance of this class

void setup()
{
  pinMode(OUT_PIN, OUTPUT);
  pinMode(IN_PIN, OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(BUTTON,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600); 
  Serial.println("Reading, %CV");
}

void loop()
{
     // int n=30;
     //float capacitance[n];
     pinMode(IN_PIN, INPUT);
     digitalWrite(OUT_PIN, HIGH);
     //int val[n];
     //val[i] = analogRead(IN_PIN);
      
      //capacitance[i] = (float)val[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val[i]);
      //for(int j=0; j<n; j++){
      //Serial.println(capacitance[j], 3);
      //}

        //Collect the data points:
  for(int i=0;i<NUMSAMPLES;i++){
    val = analogRead(IN_PIN);
   // v = (5.0*(float)val/1023.0); // convert to volts
    measurements[i]=(5.0*(float)val/1023.0); // convert to volts(float)v * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - v);
    delay(10);  // Change (or remove) this delay value to alter the sampling time span.
  } 
  
     digitalWrite(OUT_PIN, LOW);
     pinMode(IN_PIN, OUTPUT);
  
  
 
  smoothed=stats.median(measurements,NUMSAMPLES); // Median filter (choose which filter to use)
  //smoothed=stats.average(measurements,NUMSAMPLES); // Mean filter 
  //smoothed=stats.g_average(measurements,NUMSAMPLES); // Geometric mean filter 
  smoothed2=stats.mode(measurements,NUMSAMPLES,0.00001); // Mode filter, epsilon=0.00001 (tolerance for two measurements being equivalent)
  
  smoothedCV=stats.CV(measurements,NUMSAMPLES); // CV of readings 
  Serial.print("Median: ");  
  Serial.print(smoothed,3);  // Print smoothed value to serial monitor
  Serial.print(", ");
  Serial.print("Mode: ");
  Serial.println(smoothed2,3);  // Print smoothed value to serial monitor
 // Serial.print(", ");
 // Serial.println(smoothedCV);  // Print CV to serial monitor
  delay(25); // Change (or remove) this delay to alter the time between readings.
}
