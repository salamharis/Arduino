/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
  
  modified 8 Sep 2016
  by Colby Newman
*/


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}
int i =0;
// the loop function runs over and over again forever
void loop() {

  //for loop cycles through 4 sensors and sends values via serial
  for(int k=10; k<80; k++)
  {
    Serial.print('#');
    Serial.print(k);
   Serial.print(',');
    Serial.print(0);
//    Serial.print(',');
//    Serial.print(k-10);
//    Serial.print(',');
//    Serial.print(1);
//    Serial.print(',');
//    Serial.print(k+24);
//    Serial.print(',');
//    Serial.print(2);
//    Serial.print(',');
//    Serial.print(k+13);
//    Serial.print(',');
//    Serial.print(3);
//    Serial.print(',');
//    Serial.print(k-9);
//    Serial.print(',');
//    Serial.print(4);
    //technically not needed but I prefer to break up data values
    //so they are easier to see when debugging
     Serial.print('~'); //used as an end of transmission character - used in app for string length
 //Serial.println();
 delay(1000);        //added a delay to eliminate missed transmissions
  i++;
  if(i>9){
    i=0;
  }
  }
 }

