#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo; 
SoftwareSerial slave(0, 1); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
int c = 0;
int val;
void setup() 
{
    // start the serial communication with the host computer
    Serial.begin(57600);
    Serial.println("Arduino with HC-06 is ready");

    // start communication with the HC-05 using 9600
    slave.begin(57600);  
    Serial.println("BTserial started at 9600");

    myservo.attach(9);
}

void loop()
{

    if (slave.available())
    {  
        val= slave.read();
        Serial.println(val);
//        val = map(val, 0, 1023, 0, 180);
        myservo.write(val); 
        delay(15);    
    }
    myservo.write(0);
}
