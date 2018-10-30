#include "QuickStats.h"
#include <SimpleTimer.h> // here is the SimpleTimer library
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>//import necessary libraries: SoftwareSerial, Wire
#include <EEPROM.h>

const int OUT_PIN1 = 13;
const int IN_PIN1 = A0;
//const int OUT_PIN2 = A2;
const int IN_PIN2 = A1;
//const int OUT_PIN3 = A4;
const int IN_PIN3 = A2;
//const int OUT_PIN4 = A6;
const int IN_PIN4 = A3;
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

SoftwareSerial I2CBT(0,1);//define PIN11 and PIN10 as RX and TX
QuickStats stats; //initialize an instance of this class
SimpleTimer timer; // Create a Timer object called "timer"!
Servo myservo;  // create servo object to control a servo

int i =0;
int n=40;     //num of reading
void myTimerEvent()
{


     float capacitance1[n];
     float capacitance2[n];
     float capacitance3[n];
//     float capacitance4[n];

  for(  i=0; i<n; i++){ 

     int val1[n];
     int val2[n];
     int val3[n];
//     int val4[n];
     
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
////     pinMode(IN_PIN4, OUTPUT);
     


      
      pinMode(IN_PIN1, INPUT);
      digitalWrite(OUT_PIN1, HIGH);
      val2[i] = analogRead(IN_PIN1);
      capacitance1[i] = (float)val1[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val1[i]);
      digitalWrite(OUT_PIN1, LOW);
      pinMode(IN_PIN1, OUTPUT);
      
      
      
      pinMode(IN_PIN2, INPUT);
      digitalWrite(OUT_PIN1, HIGH);
      val2[i] = analogRead(IN_PIN2);
      capacitance2[i] = (float)val2[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val2[i]);
      digitalWrite(OUT_PIN1, LOW);
      pinMode(IN_PIN2, OUTPUT);



       pinMode(IN_PIN3, INPUT);
       digitalWrite(OUT_PIN1, HIGH);
       val2[i] = analogRead(IN_PIN33);
        capacitance3[i] = (float)val3[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val3[i]);
       digitalWrite(OUT_PIN1, LOW);
       pinMode(IN_PIN3, OUTPUT);
//
//
//
//       pinMode(IN_PIN4, INPUT);
//       digitalWrite(OUT_PIN4, HIGH);
//       val2[i] = analogRead(IN_PIN4);
//        capacitance4[i] = (float)val4[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val4[i]);
//       digitalWrite(OUT_PIN4, LOW);
//       pinMode(IN_PIN4, OUTPUT);

    }


       

      
      
//     Serial.print("Median: ");
//     Serial.print(stats.median(capacitance,n),3);
//     Serial.print(",");
//     Serial.print("Mode: ");
     Serial.print(stats.mode(capacitance1,n,0.00001),3);
     Serial.print(" , ");
     Serial.print(stats.mode(capacitance2,n,0.00001),3);
     Serial.print(" , ");
     Serial.println(stats.mode(capacitance3,n,0.00001),3);
//     Serial.print(" , ");
//     Serial.println(stats.mode(capacitance4,n,0.00001),3);


     


     



  if((I2CBT.available())>0)  //read BT incoming message
  {

          data =char(I2CBT.read());
          Serial.print(data);

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
      myservo.write(20);          
      delay(50);                      
      }
      
      
      else if(data == 'b'){      //when user click set new value button for position 2 for home activity
    record[5] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[6] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[7] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[8] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(25,record[5]);
    EEPROM.put(30,record[6]);
    EEPROM.put(35,record[7]);
//    EEPROM.put(40,record[8]);
    EEPROM.get(25,record[5]);
    Serial.print(record[5]);
      myservo.write(40);              
      delay(50);                      
      }
      

     else if (data == 'c')      //when user click set new value button for position 3 for home activity
      {
    record[9] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[10] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[11] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[12] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(45,record[9]);
    EEPROM.put(50,record[10]);
    EEPROM.put(55,record[11]);
//    EEPROM.put(60,record[12]);
    EEPROM.get(45,record[9]);
    Serial.print(record[9]);
      myservo.write(60);              
      delay(50);                      
      }
      

      else if(data == 'd')      //when user click set new value button for position 4 for home activity
      {
    record[13] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[14] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[15] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[16] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(65,record[13]);
    EEPROM.put(70,record[14]);
    EEPROM.put(75,record[15]);
//    EEPROM.put(80,record[16]);
    EEPROM.get(65,record[13]);
    Serial.print(record[13]);
      myservo.write(80);              
      delay(50);                      
      }


      else if(data == 'e'){            //when user click set new value button for position 1 for study activity
    record[17] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[18] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[19] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[20] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(85,record[17]);
    EEPROM.put(90,record[18]);
    EEPROM.put(95,record[19]);
//    EEPROM.put(100,record[20]);
    EEPROM.get(85,record[17]);
      Serial.print(record[17]);
      myservo.write(20);          
      delay(50);                       
      }
      
      
      else if(data == 'f'){      //when user click set new value button for position 2 for study activity
    record[21] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[22] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[23] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[24] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(105,record[21]);
    EEPROM.put(110,record[22]);
    EEPROM.put(115,record[23]);
//    EEPROM.put(120,record[24]);
    EEPROM.get(105,record[21]);
    Serial.print(record[21]);
      myservo.write(40);              
      delay(50);                      
      }
      

     else if (data == 'g')      //when user click set new value button for position 3 for study activity
      {
    record[25] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[26] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[27] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[28] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(125,record[25]);
    EEPROM.put(130,record[26]);
    EEPROM.put(135,record[27]);
//    EEPROM.put(140,record[28]);
    EEPROM.get(125,record[25]);
    Serial.print(record[25]);
      myservo.write(60);              
      delay(50);                      
      }
      

      else if(data == 'h')      //when user click set new value button for position 4 for study activity
      {
    record[29] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[30] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[31] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[32] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(145,record[29]);
    EEPROM.put(150,record[30]);
    EEPROM.put(155,record[31]);
//    EEPROM.put(160,record[32]);
    EEPROM.get(145,record[29]);
    Serial.print(record[29]);
      myservo.write(80);              
      delay(50);                      
      }


      else if(data == 'i'){            //when user click set new value button for position 1 for eat activity
    record[33] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[34] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[35] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[36] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(165,record[33]);
    EEPROM.put(170,record[34]);
    EEPROM.put(175,record[35]);
//    EEPROM.put(180,record[36]);
    EEPROM.get(165,record[33]);
      Serial.print(record[33]);
      myservo.write(20);          
      delay(50);                       
      }
      
      
      else if(data == 'j'){      //when user click set new value button for position 2 for eat activity
    record[37] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[38] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[39] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[40] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(185,record[37]);
    EEPROM.put(190,record[38]);
    EEPROM.put(195,record[39]);
//    EEPROM.put(200,record[40]);
    EEPROM.get(185,record[37]);
    Serial.print(record[37]);
      myservo.write(40);              
      delay(50);                      
      }
      

     else if (data == 'k')      //when user click set new value button for position 3 for eat activity
      {
    record[41] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[42] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[43] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[44] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(205,record[41]);
    EEPROM.put(210,record[42]);
    EEPROM.put(215,record[43]);
//    EEPROM.put(220,record[44]);
    EEPROM.get(205,record[41]);
    Serial.print(record[41]);
      myservo.write(60);              
      delay(50);                      
      }
      

      else if(data == 'l')      //when user click set new value button for position 4 for eat activity
      {
    record[45] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[46] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[47] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[48] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(225,record[45]);
    EEPROM.put(230,record[46]);
    EEPROM.put(235,record[47]);
//    EEPROM.put(240,record[48]);
    EEPROM.get(225,record[45]);
    Serial.print(record[45]);
      myservo.write(80);              
      delay(50);                      
      }


      else if(data == 'm'){     //when user click set new value button for position 1 for play activity
    record[49] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[50] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[51] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[52] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(245,record[37]);
    EEPROM.put(250,record[38]);
    EEPROM.put(255,record[39]);
//    EEPROM.put(260,record[39]);
    EEPROM.get(245,record[37]);
    Serial.print(record[37]);
      myservo.write(20);          
      delay(50);                       
      }
      
      
      else if(data == 'n'){      //when user click set new value button for position 2 for play activity
    record[40] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[41] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[42] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[43] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(265,record[40]);
    EEPROM.put(270,record[41]);
    EEPROM.put(275,record[42]);
//    EEPROM.put(280,record[43]);
    EEPROM.get(265,record[40]);
    Serial.print(record[40]);
      myservo.write(40);              
      delay(50);                      
      }
      

     else if (data == 'o')      //when user click set new value button for position 3 for play activity
      {
    record[44] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[45] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[46] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[47] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(285,record[44]);
    EEPROM.put(290,record[45]);
    EEPROM.put(295,record[46]);
//    EEPROM.put(300,record[47]);
    EEPROM.get(285,record[44]);
    Serial.print(record[44]);
      myservo.write(60);              
      delay(50);                      
      }
      

      else if(data == 'p')      //when user click set new value button for position 4 for play activity
      {
    record[48] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[49] = stats.mode(capacitance2,n,0.00001);  //Mode
    record[50] = stats.mode(capacitance3,n,0.00001);  //Mode
//    record[51] = stats.mode(capacitance4,n,0.00001);  //Mode
    EEPROM.put(305,record[48]);
    EEPROM.put(310,record[49]);
    EEPROM.put(315,record[50]);
//    EEPROM.put(320,record[51]);
    EEPROM.get(305,record[48]);
    Serial.print(record[48]);
      myservo.write(80);              
      delay(50);                      
      }

      else if (data>'0' && data<'5')   // To set the activity 
      {
      EEPROM.write(220,data);
      }
    
  }

  
  activity = (char)EEPROM.read(220);
//  Serial.println(activity);
  



     float error1 = 0.05;         //the error of capacitance 1
     float error2 = 0.18;          //the error of capacitance 2
     float error3 = 0.09;        //the error of capacitance 3
//     float error4 = 0.3;        //the error of capacitance 4

if(activity=='1')      //when user click home activity button
   {

      for(int c=1; c<=16; c++)          //to read the recorded value
      {
        EEPROM.get(c*5,record[c]);
        //Serial.print(record[c]);
      }
     if((record[1] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[1] <= stats.mode(capacitance1,n,0.00001)+error1) &&
        (record[2] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[2] <= stats.mode(capacitance2,n,0.00001)+error2) &&
        (record[3] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[3] <= stats.mode(capacitance3,n,0.00001)+error3) 
//        (record[4] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[4] <= stats.mode(capacitance4,n,0.00001)+error4)
){        
//          myservo.write(20);
          Serial.println("1");
          delay(100);
//        }
      }
      
      
      else if((record[5] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[5] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[6] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[6] <= stats.mode(capacitance2,n,0.00001)+error2) &&
              (record[7] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[7] <= stats.mode(capacitance3,n,0.00001)+error3) 
//              (record[8] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[8] <= stats.mode(capacitance4,n,0.00001)+error4)
              ){        
//          myservo.write(40);
          Serial.println("2");
          delay(100);
      }



      else if((record[9] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[9] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[10] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[10] <= stats.mode(capacitance2,n,0.00001)+error2) &&
              (record[11] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[11] <= stats.mode(capacitance3,n,0.00001)+error3) 
//              (record[12] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[12] <= stats.mode(capacitance4,n,0.00001)+error4)
              ){        
//          myservo.write(60);
          Serial.println("3");
          delay(100);
      }



      else if((record[13] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[13] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[14] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[14] <= stats.mode(capacitance2,n,0.00001)+error2) &&
              (record[15] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[15] <= stats.mode(capacitance3,n,0.00001)+error3) 
//              (record[16] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[16] <= stats.mode(capacitance4,n,0.00001)+error4)
              ){        
//          myservo.write(80);
          Serial.println("4");
          delay(100);
      }

      
   }

 
else if(activity=='2')        //when user click study activity button
   {
        for(int c=17; c<=32; c++)          //to read the recorded value
      {
        EEPROM.get(c*5,record[c]);
        //Serial.print(record[c]);
      }
       if((record[17] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[17] <= stats.mode(capacitance1,n,0.00001)+error1) &&
          (record[18] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[18] <= stats.mode(capacitance2,n,0.00001)+error2) &&
          (record[19] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[19] <= stats.mode(capacitance3,n,0.00001)+error3) 
//          (record[20] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[20] <= stats.mode(capacitance4,n,0.00001)+error4)
          ){        
//          myservo.write(20);
          Serial.println('1');
          delay(100);
      }
      

      else if((record[21] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[21] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[22] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[22] <= stats.mode(capacitance2,n,0.00001)+error2) &&
              (record[23] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[23] <= stats.mode(capacitance3,n,0.00001)+error3) 
//              (record[24] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[24] <= stats.mode(capacitance4,n,0.00001)+error4)
              ){        
//          myservo.write(40);
          Serial.println('2');
          delay(100);
      }



      else if((record[25] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[25] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[26] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[26] <= stats.mode(capacitance2,n,0.00001)+error2) &&
              (record[27] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[27] <= stats.mode(capacitance3,n,0.00001)+error3) 
//              (record[28] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[28] <= stats.mode(capacitance4,n,0.00001)+error4)
              ){        
//          myservo.write(60);
          Serial.println('3');
          delay(100);
      }



       else if((record[29] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[29] <= stats.mode(capacitance1,n,0.00001)+error1) &&
               (record[30] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[30] <= stats.mode(capacitance2,n,0.00001)+error2) &&
               (record[31] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[31] <= stats.mode(capacitance3,n,0.00001)+error3) 
//               (record[32] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[32] <= stats.mode(capacitance4,n,0.00001)+error4)
               ){        
//          myservo.write(80);
          Serial.println('4');
          delay(100);
        
      }    
   }


else if(activity=='3')        //when user click eat activity button
   {
       for(int c=33; c<=48; c++)          //to read the recorded value
      {
        EEPROM.get(c*5,record[c]);
        //Serial.print(record[c]);
      }
      
       if((record[33] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[33] <= stats.mode(capacitance1,n,0.00001)+error1) &&
          (record[34] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[34] <= stats.mode(capacitance2,n,0.00001)+error2) &&
          (record[35] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[35] <= stats.mode(capacitance3,n,0.00001)+error3) 
//          (record[36] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[36] <= stats.mode(capacitance4,n,0.00001)+error4)
          ){        
//          myservo.write(20);
          Serial.println('1');
          delay(100);
      }
      

      else if((record[37] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[37] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[38] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[38] <= stats.mode(capacitance2,n,0.00001)+error2) &&
              (record[39] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[39] <= stats.mode(capacitance3,n,0.00001)+error3) 
//              (record[40] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[40] <= stats.mode(capacitance4,n,0.00001)+error4)
              ){        
//          myservo.write(40);
          Serial.println('2');
          delay(100);
      }



      else if((record[41] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[41] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[42] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[42] <= stats.mode(capacitance2,n,0.00001)+error2) &&
              (record[43] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[43] <= stats.mode(capacitance3,n,0.00001)+error3) 
//              (record[44] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[44] <= stats.mode(capacitance4,n,0.00001)+error4)
              ){        
//          myservo.write(60);
          Serial.println('3');
          delay(100);
      }



       else if((record[45] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[45] <= stats.mode(capacitance1,n,0.00001)+error1) &&
               (record[46] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[46] <= stats.mode(capacitance2,n,0.00001)+error2) &&
               (record[47] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[47] <= stats.mode(capacitance3,n,0.00001)+error3) 
//               (record[48] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[48] <= stats.mode(capacitance4,n,0.00001)+error4)
               ){        
//          myservo.write(80);
          Serial.println('4');
          delay(100);
      }    
   }



 else if(activity=='4')        //when user click play activity button
   {
        for(int c=49; c<=64; c++)          //to read the recorded value
      {
        EEPROM.get(c*5,record[c]);
        //Serial.print(record[c]);
      }
      
       if((record[49] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[49] <= stats.mode(capacitance1,n,0.00001)+error1) &&
          (record[50] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[50] <= stats.mode(capacitance2,n,0.00001)+error2) &&
          (record[51] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[51] <= stats.mode(capacitance3,n,0.00001)+error3) 
//          (record[52] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[52] <= stats.mode(capacitance4,n,0.00001)+error4)
          ){        
//          myservo.write(20);
          Serial.println('1');
          delay(100);
      }
      

      else if((record[53] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[53] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[54] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[54] <= stats.mode(capacitance2,n,0.00001)+error2) &&
              (record[55] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[55] <= stats.mode(capacitance3,n,0.00001)+error3) 
//              (record[56] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[56] <= stats.mode(capacitance4,n,0.00001)+error4)
              ){        
//          myservo.write(40);
          Serial.println('2');
          delay(100);
      }



      else if((record[57] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[57] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[58] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[58] <= stats.mode(capacitance2,n,0.00001)+error2) &&
              (record[59] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[59] <= stats.mode(capacitance3,n,0.00001)+error3) 
//              (record[60] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[60] <= stats.mode(capacitance4,n,0.00001)+error4)
              ){        
//          myservo.write(60);
          Serial.println('3');
          delay(100);
      }



       else if((record[61] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[61] <= stats.mode(capacitance1,n,0.00001)+error1) &&
               (record[62] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[62] <= stats.mode(capacitance2,n,0.00001)+error2) &&
               (record[63] >= stats.mode(capacitance3,n,0.00001)-error3) && (record[63] <= stats.mode(capacitance3,n,0.00001)+error3) 
//               (record[64] >= stats.mode(capacitance4,n,0.00001)-error4) && (record[64] <= stats.mode(capacitance4,n,0.00001)+error4)
               ){        
//          myservo.write(80);
          Serial.println('4');
          delay(100);
      }    
   }
 



   


}





void setup()
{
   pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
   Serial.begin(57600); //set USB baudrate: 9600
   I2CBT.begin(57600);     //BT baudrate: 57600(Warning!! baudrate of each BT module may differ, 
                          //please check the data sheet first!!
//   Serial.begin(38400);
//  BTSerial.begin(9600);  // HC-05 default speed in AT command more
//   Serial.print("Device Start Reading");
  
  pinMode(OUT_PIN1, OUTPUT);
  pinMode(IN_PIN1, OUTPUT);
//  pinMode(OUT_PIN2, OUTPUT);
  pinMode(IN_PIN2, OUTPUT);
//  pinMode(OUT_PIN3, OUTPUT);
  pinMode(IN_PIN3, OUTPUT);
//  pinMode(OUT_PIN4, OUTPUT);
  pinMode(IN_PIN4, OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(BUTTON,INPUT);
  pinMode(13,OUTPUT);

//  myservo.attach(2);  // attaches the servo on pin 9 to the servo objec
 // myservo.write(0);

  

  timer.setInterval(100L, myTimerEvent); //  Here you set interval (1sec) and which function to call
}

void loop()
{
  timer.run(); // SimpleTimer is working 
}

