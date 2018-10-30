#include <SoftwareSerial.h>

#define BT_SERIAL_TX 1

#define BT_SERIAL_RX 0

SoftwareSerial BluetoothSerial(BT_SERIAL_TX, BT_SERIAL_RX);

#include <Servo.h>

Servo myservo;
char val = ' ';

void setup()

{

Serial.begin(57600);

BluetoothSerial.begin(57600);

myservo.attach(10);

}

void loop()

{

if (BluetoothSerial.available()>0)

{
val = BluetoothSerial.read();

int servoAng = val - '0';
Serial.print(servoAng);

myservo.write(servoAng);

}

}
