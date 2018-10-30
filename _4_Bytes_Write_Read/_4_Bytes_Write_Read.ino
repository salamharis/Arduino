/////////////////////////////////////////////////////////////////
// Created by Kevin Elsenberger                                //
// June 2, 2013                                                //
// elsenberger.k at gmail.com                                  //
// from http://playground.arduino.cc/Code/EEPROMReadWriteLong  //
/////////////////////////////////////////////////////////////////

//Needed to access the eeprom read write functions
#include <EEPROM.h> 

float number1;
float number2;

//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to adress + 3.
void EEPROMWritelong(long address, float value)
      {
      //Decomposition from a long to 4 bytes by using bitshift.
      //One = Most significant -> Four = Least significant byte
      byte four = (value & 0xFF);
      byte three = ((value >> 8) & 0xFF);
      byte two = ((value >> 16) & 0xFF);
      byte one = ((value >> 24) & 0xFF);

      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(address, four);
      EEPROM.write(address + 1, three);
      EEPROM.write(address + 2, two);
      EEPROM.write(address + 3, one);
      }

//This function will return a 4 byte (32bit) long from the eeprom
//at the specified address to adress + 3.
float EEPROMReadlong(long address)
      {
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address);
      long three = EEPROM.read(address + 1);
      long two = EEPROM.read(address + 2);
      long one = EEPROM.read(address + 3);

      //Return the recomposed long by using bitshift.
      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
      }

void setup()
      {
      Serial.begin(9600);
      }

void loop()
      {
      //Adding a delay in order to have the time to open the
      //Arduino serial monitor.
      delay(5000);

      if (Serial.available())
      {
        number1 = Serial.parseFloat();
        number2 = Serial.read();
      }

      //Starting at the first byte on the eeprom.
      long address=0;

      //Writing first long.
      EEPROMWritelong(address, number1);
      address+=4;
      //Writing second long.
      EEPROMWritelong(address, number2);
      address+=4;


      Serial.println("If numbers are equals, it's working !");
      Serial.print(number1);
      Serial.print(" and ");
      //Readind and sending first long.
      Serial.println(EEPROMReadlong(0));

      Serial.print(number2);
      Serial.print(" and ");
      //Readind and sending second long.
      Serial.println(EEPROMReadlong(4));
      }
