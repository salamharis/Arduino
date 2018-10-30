//#include "QuickStats.h"
//#include <SimpleTimer.h> // here is the SimpleTimer library
//#include <Servo.h>
//#include <SoftwareSerial.h>
//#include <Wire.h>//import necessary libraries: SoftwareSerial, Wire
//#include <EEPROM.h>
//#include <ResponsiveAnalogRead.h>


const int OUT_PIN1 = 6;
const int IN_PIN1 = 0;
const int IN_PIN2 = 1;
const int IN_PIN3 = 2;
const int IN_PIN4 = 3;
const int IN_PIN5 = 4;
const int IN_PIN6 = 10;







//SoftwareSerial I2CBT(0,1);//define PIN11 and PIN10 as RX and TX
//QuickStats stats; //initialize an instance of this class
//SimpleTimer timer; // Create a Timer object called "timer"!
//Servo myservo;  // create servo object to control a servo





void setup() {
  Serial.begin(115200); //set USB baudrate: 9600
  pinMode(IN_PIN1, OUTPUT);
  pinMode(IN_PIN2, OUTPUT);
  pinMode(IN_PIN3, OUTPUT);
  pinMode(IN_PIN4, OUTPUT);
  pinMode(IN_PIN5, OUTPUT);
  pinMode(IN_PIN6, OUTPUT);
}

int i = 5;
int n = 50;
int val[6][150]={0};
int capacitance;
void loop() {


//       Serial.print(i);
//       Serial.print(",");
       capacitancevalue(IN_PIN1,i,0);
       Serial.print(",");
       capacitancevalue(IN_PIN2,i,1);
       Serial.print(",");
       capacitancevalue(IN_PIN3,i,2);
       Serial.print(",");
       capacitancevalue(IN_PIN4,i,3);
       Serial.print(",");
       capacitancevalue(IN_PIN5,i,4);
       Serial.print(",");
       capacitancevalue(IN_PIN6,i,5);
       Serial.println("");
       i++;
       if(i>=55){
        i=5;
       }
//       if(i>n){
//        i=0;
//        Serial.println("if");
//       }


       
  }



int capacitancevalue(int InputPin,int count,int Array){

       pinMode(InputPin, INPUT);
       digitalWrite(OUT_PIN1, HIGH);
       delay(25);
       
       if(count>=50){
        //val[Array][count-50] = analogRead(InputPin); 
        capacitance = analogRead(InputPin);//abs(val[Array][count-50]-val[Array][count-5]);
       }
       else if(count<50){
        //val[Array][count] = analogRead(InputPin); 
        capacitance = analogRead(InputPin);//abs(val[Array][count]-val[Array][count-5]);
       }

       float snapmultiplier = 0.05; //more smaller value more smooth
       int snap = snapcurve(capacitance*snapmultiplier);

       int smoothvalue = smoothvalue + capacitance*snap;
 
       Serial.print(smoothvalue);
       digitalWrite(OUT_PIN1, LOW);
       pinMode(InputPin, OUTPUT);
         
 
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



  






  
  


