//master
#include <Wire.h>

char t[10]={};//empty array where to put the numbers comming from the slave
volatile int Val; // varaible used by the master to sent data to the slave

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 3);    // request 3 bytes from slave device #8

//gathers data comming from slave
int i=0; //counter for each bite as it arrives
  while (Wire.available()) { 
    t[i] = Wire.read(); // every character that arrives it put in order in the empty array "t"
    i=i+1;
  }

Serial.println(t);   //shows the data in the array t
delay(500); //give some time to relax

// send data to slave. here I am just sending the number 2
  Val=2;
  Wire.beginTransmission (8);
  Wire.write (Val);
  Wire.endTransmission ();
}
