#include "QuickStats.h"
#include <SimpleTimer.h> // here is the SimpleTimer library
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>//import necessary libraries: SoftwareSerial, Wire
#include <EEPROM.h>

const int OUT_PIN1 = A1;
const int IN_PIN1 = A0;
const int OUT_PIN2 = A2;
const int IN_PIN2 = A3;
const int OUT_PIN3 = A4;
const int IN_PIN3 = A5;
const int OUT_PIN4 = A6;
const int IN_PIN4 = A7;
const int BUTTON = 2;
const float IN_STRAY_CAP_TO_GND = 24.48;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND;
const float R_PULLUP = 34.8;  
const int MAX_ADC_VALUE = 1023;
int v1 = 0;

//char data = 0;                //Variable for storing received data

int pos = 0;    // variable to store the servo position

//static double record1,record2,record3,record4,record5,record6,record7,record8,record9,record10,record11,record12;
//static float record13,record14,record15,record16,record17,record18,record19,record20,record21,record22,record23,record24;
//static float record25,record26,record27,record28,record29,record30,record31,record32,record33,record34,record35,record36;
//static float record37,record38,record39,record40,record41,record42,record43,record44,record45,record46,record47,record48;
float record[50];
char data;
char activity;

SoftwareSerial I2CBT(0,1);//define PIN11 and PIN10 as RX and TX
QuickStats stats; //initialize an instance of this class
SimpleTimer timer; // Create a Timer object called "timer"!
Servo myservo;  // create servo object to control a servo

int i =0;
int n=50;
void myTimerEvent()
{


     float capacitance1[n];
     float capacitance2[n];
//     float capacitance3[n];
//     float capacitance4[n];

  for(  i=0; i<n; i++){ 
     
     pinMode(IN_PIN1, INPUT);
     pinMode(IN_PIN2, INPUT);
//     pinMode(IN_PIN3, INPUT);
//     pinMode(IN_PIN4, INPUT);
     
     digitalWrite(OUT_PIN1, HIGH);
     digitalWrite(OUT_PIN2, HIGH);
//     digitalWrite(OUT_PIN3, HIGH);
//     digitalWrite(OUT_PIN4, HIGH);
     
     int val1[n];
     int val2[n];
//     int val3[n];
//     int val4[n];
     

     val1[i] = analogRead(IN_PIN1);
     val2[i] = analogRead(IN_PIN2);
//     val3[i] = analogRead(IN_PIN3);
//     val4[i] = analogRead(IN_PIN4);
     
      
      capacitance1[i] = (float)val1[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val1[i]);
      capacitance2[i] = (float)val2[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val2[i]);
//      capacitance3[i] = (float)val3[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val3[i]);
//      capacitance4[i] = (float)val4[i] * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val4[i]);
      
//      for(int j=0; j<n; j++){
//      Serial.println(capacitance1[i], 3);
//      Serial.print(" , ");
//      Serial.print(capacitance2[j], 3);
//      Serial.print(" , ");
//      Serial.print(capacitance3[j], 3);
//      Serial.println(" , ");
//      Serial.println(capacitance4[j], 3);
//      }
  
     digitalWrite(OUT_PIN1, LOW);
     digitalWrite(OUT_PIN2, LOW);
//     digitalWrite(OUT_PIN3, LOW);
//     digitalWrite(OUT_PIN4, LOW);
     
     pinMode(IN_PIN1, OUTPUT);
     pinMode(IN_PIN2, OUTPUT);
//     pinMode(IN_PIN3, OUTPUT);
//     pinMode(IN_PIN4, OUTPUT);


    }


       

      
      
//     Serial.print("Median: ");
//     Serial.print(stats.median(capacitance,n),3);
//     Serial.print(",");
//     Serial.print("Mode: ");
     Serial.print(stats.mode(capacitance1,n,0.00001),3);
     Serial.print(" , ");
     Serial.println(stats.mode(capacitance2,n,0.00001),3);
//     Serial.print(" , ");
//     Serial.println(stats.mode(capacitance3,n,0.00001),3);
//     Serial.print(" , ");
//     Serial.println(stats.mode(capacitance4,n,0.00001),3);


     


     



  if((I2CBT.available())>0)  //read BT incoming message
  {

          data =char(I2CBT.read());

   if(data == 'a'){            //when user click set new value button for position 1 for home activity
    record[1] =stats.mode(capacitance1,n,0.00001);  //Mode
    record[2] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[3] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(5,record[1]);
    EEPROM.put(10,record[2]);
//    EEPROM.put(15,record[3]);
    EEPROM.get(5,record[1]);
    Serial.print(record[1]);
      myservo.write(20);          
      delay(50);                      
      }
      
      
      else if(data == 'b'){      //when user click set new value button for position 2 for home activity
    record[4] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[5] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[6] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(20,record[4]);
    EEPROM.put(25,record[5]);
//    EEPROM.put(30,record[6]);
    EEPROM.get(20,record[4]);
    Serial.print(record[4]);
      myservo.write(40);              
      delay(50);                      
      }
      

     else if (data == 'c')      //when user click set new value button for position 3 for home activity
      {
    record[7] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[8] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[9] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(35,record[7]);
    EEPROM.put(40,record[8]);
//    EEPROM.put(45,record[9]);
    EEPROM.get(35,record[7]);
    Serial.print(record[7]);
      myservo.write(60);              
      delay(50);                      
      }
      

      else if(data == 'd')      //when user click set new value button for position 4 for home activity
      {
    record[10] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[11] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[12] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(40,record[10]);
    EEPROM.put(45,record[11]);
//    EEPROM.put(50,record[12]);
    EEPROM.get(40,record[10]);
    Serial.print(record[10]);
      myservo.write(80);              
      delay(50);                      
      }


      else if(data == 'e'){            //when user click set new value button for position 1 for study activity
    record[13] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[14] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[15] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(55,record[13]);
    EEPROM.put(60,record[14]);
//    EEPROM.put(65,record[15]);
    EEPROM.get(55,record[13]);
      Serial.print(record[13]);
      myservo.write(20);          
      delay(50);                       
      }
      
      
      else if(data == 'f'){      //when user click set new value button for position 2 for study activity
    record[16] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[17] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[18] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(70,record[16]);
    EEPROM.put(75,record[17]);
//    EEPROM.put(80,record[18]);
    EEPROM.get(70,record[16]);
    Serial.print(record[16]);
      myservo.write(40);              
      delay(50);                      
      }
      

     else if (data == 'g')      //when user click set new value button for position 3 for study activity
      {
    record[19] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[20] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[21] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(75,record[19]);
    EEPROM.put(80,record[20]);
//    EEPROM.put(85,record[21]);
    EEPROM.get(75,record[19]);
    Serial.print(record[19]);
      myservo.write(60);              
      delay(50);                      
      }
      

      else if(data == 'h')      //when user click set new value button for position 4 for study activity
      {
    record[22] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[23] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[24] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(90,record[22]);
    EEPROM.put(95,record[23]);
//    EEPROM.put(100,record[24]);
    EEPROM.get(90,record[22]);
    Serial.print(record[22]);
      myservo.write(80);              
      delay(50);                      
      }


      else if(data == 'i'){            //when user click set new value button for position 1 for eat activity
    record[25] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[26] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[27] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(110,record[25]);
    EEPROM.put(115,record[26]);
//    EEPROM.put(120,record[27]);
    EEPROM.get(110,record[25]);
      Serial.print(record[25]);
      myservo.write(20);          
      delay(50);                       
      }
      
      
      else if(data == 'j'){      //when user click set new value button for position 2 for eat activity
    record[28] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[29] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[30] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(125,record[28]);
    EEPROM.put(130,record[29]);
//    EEPROM.put(135,record[30]);
    EEPROM.get(125,record[28]);
    Serial.print(record[28]);
      myservo.write(40);              
      delay(50);                      
      }
      

     else if (data == 'k')      //when user click set new value button for position 3 for eat activity
      {
    record[31] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[32] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[33] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(140,record[31]);
    EEPROM.put(145,record[32]);
//    EEPROM.put(150,record[33]);
    EEPROM.get(140,record[31]);
    Serial.print(record[31]);
      myservo.write(60);              
      delay(50);                      
      }
      

      else if(data == 'l')      //when user click set new value button for position 4 for eat activity
      {
    record[34] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[35] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[36] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(155,record[34]);
    EEPROM.put(160,record[35]);
//    EEPROM.put(165,record[36]);
    EEPROM.get(155,record[34]);
    Serial.print(record[34]);
      myservo.write(80);              
      delay(50);                      
      }


      else if(data == 'm'){     //when user click set new value button for position 1 for play activity
    record[37] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[38] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[39] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(170,record[37]);
    EEPROM.put(175,record[38]);
//    EEPROM.put(180,record[39]);
    EEPROM.get(170,record[37]);
    Serial.print(record[37]);
      myservo.write(20);          
      delay(50);                       
      }
      
      
      else if(data == 'n'){      //when user click set new value button for position 2 for play activity
    record[40] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[41] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[42] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(185,record[40]);
    EEPROM.put(190,record[41]);
//    EEPROM.put(195,record[42]);
    EEPROM.get(185,record[40]);
    Serial.print(record[40]);
      myservo.write(40);              
      delay(50);                      
      }
      

     else if (data == 'o')      //when user click set new value button for position 3 for play activity
      {
    record[43] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[44] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[45] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(200,record[43]);
    EEPROM.put(205,record[44]);
//    EEPROM.put(210,record[45]);
    EEPROM.get(200,record[43]);
    Serial.print(record[43]);
      myservo.write(60);              
      delay(50);                      
      }
      

      else if(data == 'p')      //when user click set new value button for position 4 for play activity
      {
    record[46] = stats.mode(capacitance1,n,0.00001);  //Mode
    record[47] = stats.mode(capacitance2,n,0.00001);  //Mode
//    record[48] = stats.mode(capacitance3,n,0.00001);  //Mode
    EEPROM.put(215,record[46]);
    EEPROM.put(220,record[47]);
//    EEPROM.put(225,record[48]);
    EEPROM.get(215,record[46]);
    Serial.print(record[46]);
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
  



     float error1 = 0.3;         //the error of capacitance 1
     float error2 = 0.3;          //the error of capacitance 2
//     float error3 = 100000;        //the error of capacitance 3

if(activity=='1')      //when user click home activity button
   {

      for(int c=1; c<=12; c++)          //to read the recorded value
      {
        EEPROM.get(c*5,record[c]);
        //Serial.print(record[c]);
      }
     if((record[1] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[1] <= stats.mode(capacitance1,n,0.00001)+error1) &&
        (record[2] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[2] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(20);
          Serial.println("1");
          delay(100);
//        }
      }
      
      
      else if((record[4] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[4] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[5] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[5] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(40);
          Serial.println("2");
          delay(100);
      }



      else if((record[7] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[7] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[8] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[8] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(60);
          Serial.println("3");
          delay(100);
      }



      else if((record[10] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[10] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[11] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[11] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(80);
          Serial.println("4");
          delay(100);
      }

      
   }

 
else if(activity=='2')        //when user click study activity button
   {
        for(int c=13; c<=24; c++)          //to read the recorded value
      {
        EEPROM.get(c*5,record[c]);
        //Serial.print(record[c]);
      }
       if((record[13] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[13] <= stats.mode(capacitance1,n,0.00001)+error1) &&
          (record[14] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[14] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(20);
          Serial.println("1");
          delay(100);
      }
      

      else if((record[16] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[16] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[17] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[17] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(40);
          Serial.println("2");
          delay(100);
      }



      else if((record[19] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[19] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[20] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[20] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(60);
          Serial.println("3");
          delay(100);
      }



       else if((record[22] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[22] <= stats.mode(capacitance1,n,0.00001)+error1) &&
               (record[23] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[23] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(80);
          Serial.println("4");
          delay(100);
        
      }    
   }


else if(activity=='3')        //when user click eat activity button
   {
       for(int c=25; c<=36; c++)          //to read the recorded value
      {
        EEPROM.get(c*5,record[c]);
        //Serial.print(record[c]);
      }
      
       if((record[25] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[25] <= stats.mode(capacitance1,n,0.00001)+error1) &&
          (record[26] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[26] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(20);
          Serial.println("1");
          delay(100);
      }
      

      else if((record[28] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[28] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[29] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[29] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(40);
          Serial.println("2");
          delay(100);
      }



      else if((record[31] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[31] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[32] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[32] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(60);
          Serial.println("3");
          delay(100);
      }



       else if((record[34] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[34] <= stats.mode(capacitance1,n,0.00001)+error1) &&
               (record[35] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[35] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(80);
          Serial.println("4");
          delay(100);
      }    
   }



 else if(activity=='4')        //when user click play activity button
   {
        for(int c=37; c<=48; c++)          //to read the recorded value
      {
        EEPROM.get(c*5,record[c]);
        //Serial.print(record[c]);
      }
      
       if((record[37] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[37] <= stats.mode(capacitance1,n,0.00001)+error1) &&
          (record[38] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[38] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(20);
          Serial.println("1");
          delay(100);
      }
      

      else if((record[40] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[40] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[41] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[41] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(40);
          Serial.println("2");
          delay(100);
      }



      else if((record[43] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[43] <= stats.mode(capacitance1,n,0.00001)+error1) &&
              (record[44] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[44] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(60);
          Serial.println("3");
          delay(100);
      }



       else if((record[46] >= stats.mode(capacitance1,n,0.00001)-error1) && (record[46] <= stats.mode(capacitance1,n,0.00001)+error1) &&
               (record[47] >= stats.mode(capacitance2,n,0.00001)-error2) && (record[47] <= stats.mode(capacitance2,n,0.00001)+error2)){        
          myservo.write(80);
          Serial.println("4");
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
  pinMode(OUT_PIN2, OUTPUT);
  pinMode(IN_PIN2, OUTPUT);
  pinMode(OUT_PIN3, OUTPUT);
  pinMode(IN_PIN3, OUTPUT);
  pinMode(OUT_PIN4, OUTPUT);
  pinMode(IN_PIN4, OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(BUTTON,INPUT);
  pinMode(13,OUTPUT);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo objec
 // myservo.write(0);

  

  timer.setInterval(10L, myTimerEvent); //  Here you set interval (1sec) and which function to call
}

void loop()
{
  timer.run(); // SimpleTimer is working 
}

