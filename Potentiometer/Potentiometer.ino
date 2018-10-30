#include <SoftwareSerial.h>

#define BT_SERIAL_TX 0

#define BT_SERIAL_RX 1

SoftwareSerial BluetoothSerial(BT_SERIAL_TX, BT_SERIAL_RX);

int potpin = A1;

int val;

void setup()

{

Serial.begin(57600);

BluetoothSerial.begin(9600);

}

void loop()

{

val = analogRead(potpin);

val = map(val, 0, 1023, 0, 179);

BluetoothSerial.print(val);

delay(100);

}
