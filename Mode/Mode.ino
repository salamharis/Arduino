// Example program for use with QuickStats.h 

#include "QuickStats.h"

const int OUT_PIN = A1;
const int IN_PIN = A0;
const int BUTTON = 2;
const float IN_STRAY_CAP_TO_GND = 24.48;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND;
const float R_PULLUP = 34.8;  
const int MAX_ADC_VALUE = 1023;


//
//  int i=0, j, n=30, mode, MAX=0, sum=0, t, k=0, c=1; 
//
//        float readings[20]={0}, b[n]={0};
//        for(i=0;i<n;i++)
//        {
//        readings[i] = (float)analogRead(IN_PIN) * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - analogRead(IN_PIN));
//        } 

int numreadings = 9;
float readings[]={1.0,2.2,4.8,3.3,6.1,2.2,3.8,7.0,2.2};
 
QuickStats stats; //initialize an instance of this class

void setup()
{
 pinMode(IN_PIN, INPUT);
 digitalWrite(OUT_PIN, HIGH);
 unsigned int val[20];
 digitalWrite(OUT_PIN, LOW);
 pinMode(IN_PIN, OUTPUT);
  
  Serial.begin(9600); 
  Serial.println("Descriptive Statistics");
  Serial.print("Average: ");
  Serial.println(stats.average(readings,numreadings));
  Serial.print("Geometric mean: ");
  Serial.println(stats.g_average(readings,numreadings));
  Serial.print("Minimum: ");
  Serial.println(stats.minimum(readings,numreadings));
  Serial.print("Maximum: ");
  Serial.println(stats.maximum(readings,numreadings));
  Serial.print("Standard Deviation: ");
  Serial.println(stats.stdev(readings,numreadings));
  Serial.print("Standard Error: ");
  Serial.println(stats.stderror(readings,numreadings));
  Serial.print("Coefficient of Variation (%): ");
  Serial.println(stats.CV(readings,numreadings));
  Serial.print("Median: ");
  Serial.println(stats.median(readings,numreadings));
  Serial.print("Mode: ");
  Serial.println(stats.mode(readings,numreadings,0.00001));
}
 
void loop()
{
}
