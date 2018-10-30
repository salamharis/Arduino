#include <SoftwareSerial.h>
SoftwareSerial BTserial(0,1); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
int potpin = 1;  // analog pin used to connect the potentiometer
int potpin2 = 2;

void setup() 
{
    // start the serial communication with the host computer
    Serial.begin(57600);
    Serial.println("Arduino with HC-05 is ready");

    // start communication with the HC-05 using 9600
    BTserial.begin(57600);  
    Serial.println("BTserial started at 9600");
}

void loop()
{
//    BTserial.println(potpin); 
//    delay(100); 
    Serial.print(potpin);
    delay(100);
//    BTserial.println(potpin2); 
//    delay(100); 
    Serial.print(potpin2);
}
