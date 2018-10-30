#include "QuickStats.h"
//#include <SimpleTimer.h> // here is the SimpleTimer library
//#include <Servo.h>
//#include <SoftwareSerial.h>
#include <Wire.h>//import necessary libraries: SoftwareSerial, Wire
//#include <EEPROM.h>

const int OUT_PIN1 = 0;
const int IN_PIN1 = 1;
//const int OUT_PIN2 = A2;
const int IN_PIN2 = 2;
//const int OUT_PIN3 = A4;
const int IN_PIN3 = 3;
//const int OUT_PIN4 = A6;
const int IN_PIN4 = 4;
const int BUTTON = 2;
const float IN_STRAY_CAP_TO_GND = 24.48;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND;
const float R_PULLUP = 34.8;  
const int MAX_ADC_VALUE = 1023;
int v1 = 0;

//char data = 0;                //Variable for storing received data

int pos = 0;    // variable to store the servo position


float record[64];   //the value of 
char data;
char activity;

//SoftwareSerial I2CBT(0,1);//define PIN11 and PIN10 as RX and TX
QuickStats stats; //initialize an instance of this class
//SimpleTimer timer; // Create a Timer object called "timer"!
//Servo myservo;  // create servo object to control a servo





void setup() {
  Serial.begin(57600); //set USB baudrate: 9600
   I2CBT.begin(57600);     //BT baudrate: 57600(Warning!! baudrate of each BT module may differ, 

}

int i =0;
int n=40;     //num of reading

void loop() {
     float capacitance1[n];
     float capacitance2[n];
     float capacitance3[n];
//     float capacitance4[n];

  for(  i=0; i<n; i++){ 

     int val1[n];
     int val2[n];
     int val3[n];
//     int val4[n];
//     
//     pinMode(IN_PIN1, INPUT);   //set pin 1 as input
//     pinMode(IN_PIN2, INPUT);
//     pinMode(IN_PIN3, INPUT);
////     pinMode(IN_PIN4, INPUT);
//     digitalWrite(OUT_PIN1, HIGH);  //the output pin will send the high output
//     
//     val1[i] = analogRead(IN_PIN1);   
//     val2[i] = analogRead(IN_PIN2);
//     val3[i] = analogRead(IN_PIN3);
////     val4[i] = analogRead(IN_PIN4);
//     
//     capacitance1[i] = (float)val1[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val1[i]);    //calculate the capacitance value
//     capacitance2[i] = (float)val2[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val2[i]);
//     capacitance3[i] = (float)val3[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val3[i]);
////     capacitance4[i] = (float)val4[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val4[i]);
//     
//     digitalWrite(OUT_PIN1, LOW);     //stop send the high output
//     pinMode(IN_PIN1, OUTPUT);        //set the pin A0 to output to stop receiving the input
//     pinMode(IN_PIN2, OUTPUT);
//     pinMode(IN_PIN3, OUTPUT);




       pinMode(IN_PIN1, INPUT);
      digitalWrite(OUT_PIN1, HIGH);
      delay(50);
      val1[i] = analogRead(IN_PIN1);
      Serial.print(val1[i]);
//      capacitance1[i] = (float)val1[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val1[i]);
      digitalWrite(OUT_PIN1, LOW);
      pinMode(IN_PIN1, OUTPUT);
      
//      delay(100);
      
      pinMode(IN_PIN2, INPUT);
      digitalWrite(OUT_PIN1, HIGH);
      delay(50);
      val2[i] = analogRead(IN_PIN2);
      Serial.print(",");
      Serial.print(val2[i]);
//      capacitance2[i] = (float)val2[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val2[i]);
      
      digitalWrite(OUT_PIN1, LOW);
      pinMode(IN_PIN2, OUTPUT);

//      delay(100);

       pinMode(IN_PIN3, INPUT);
       digitalWrite(OUT_PIN1, HIGH);
       delay(50);
       val3[i] = analogRead(IN_PIN3);
       Serial.print(",");
       Serial.println(val3[i]);
//        capacitance3[i] = (float)val3[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val3[i]);
       digitalWrite(OUT_PIN1, LOW);
       pinMode(IN_PIN3, OUTPUT);

  }

//     Serial.print(stats.mode(capacitance1,n,0.00001),3);
//     Serial.print(" , ");
//     Serial.print(stats.mode(capacitance2,n,0.00001),3);
//     Serial.print(" , ");
//     Serial.println(stats.mode(capacitance3,n,0.00001),3);

  if((I2CBT.available())>0)  //read BT incoming message
  {

          data =char(I2CBT.read());
//          Serial.print(data);

   if(data == 'a'){            //when user click set new value button for position 1 for home activity
    record[1] =stats.mode(capacitance1,n,0.00001);  //Mode
    record[2] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[3] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[4] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(5,record[1]);   //save the value of capacitance in EEPROM
    EEPROM.put(10,record[2]);  //each has length 4 bytes, so need to has the distance at least 4 bytes between the saved value
    EEPROM.put(15,record[3]);
//    EEPROM.put(20,record[4]);
    EEPROM.get(5,record[1]);
    Serial.print(record[1]);
//      myservo.write(20);          
      delay(50);                      
      }
      
      
      else if(data == 'b'){      //when user click set new value button for position 2 for home activity
    record[4] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[5] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[6] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[8] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(20,record[4]);
    EEPROM.put(25,record[5]);
    EEPROM.put(30,record[6]);
//    EEPROM.put(40,record[8]);
    EEPROM.get(20,record[4]);
    Serial.print(record[4]);
//      myservo.write(40);              
      delay(50);                      
      }

  }
  else{

     float error1 = 0.3;         //the error of capacitance 1
     float error2 = 0.3;          //the error of capacitance 2
     float error3 = 0.3;        //the error of capacitance 3

   for(int c=1; c<=6; c++)          //to read the recorded value
      {
        EEPROM.get(c*5,record[c]);
        //Serial.print(record[c]);
      }
       if((record[1] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[1] <= stats.mode(capacitance1,n,0.00001)+error1) &&
          (record[2] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[2] <= stats.mode(capacitance2,n,0.00001)+error2) &&
          (record[3] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[3] <= stats.mode(capacitance3,n,0.00001)+error3) 
//          (record[52] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[52] <= stats.mode(capacitance4,n,0.00001)+error4)
          ){        
//          myservo.write(20);
          Serial.print('1');
          delay(100);
      }
      

      else if((record[4] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[4] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[5] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[5] <= stats.mode(capacitance2,n,0.00001)+error2) &&
              (record[6] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[6] <= stats.mode(capacitance3,n,0.00001)+error3) 
//              (record[56] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[56] <= stats.mode(capacitance4,n,0.00001)+error4)
              ){        
//          myservo.write(40);
          Serial.print('2');
          delay(100);
      }
  }


//          Serial.print('1');
//          delay(2000);
//          Serial.print('2');
          delay(500);
  

  
  

}
