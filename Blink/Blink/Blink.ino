#https://github.com/wemos/WEMOS_SHT3x_Arduino_Library

#include

SHT3X sht30 (0x45) ;

void setup () {

Serial . []} begin (115200) ;

}

void loop () {

sht30 . []} get () ;

serial . print (“Temperature in Celsius:”) ;

serial . println (sht30.[)(19459026] cTemp ) ;

serial . print (“Temperature in Fahrenheit:”) ;

serial . println (sht30.[)(19459026] fTemp ) ;

serial . print (“Relative Humidity:”) ;

serial . println (sht30.[)(19459026] humidity ) ;

serial . println () ;

delay (1000) ;

}
