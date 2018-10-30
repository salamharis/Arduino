#include <avr/io.h>
#include <util/delay.h>

void setup() {
  
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);


}

void loop() {
  unsigned int count_value = 0;

  count_value=digitalRead(A0);
    
    
    for(count_value=0;count_value<16;count_value++)
    {
      while(digitalRead(A0)==0)
        switch(count_value)
        {
          case 0:
          digitalWrite(11,1);
          digitalWrite(10,1);
          digitalWrite(9,1);
          digitalWrite(8,1);
          digitalWrite(7,1);  //a
          digitalWrite(6,1);  //b
          digitalWrite(5,1);  //c
          digitalWrite(4,1);  //d
          digitalWrite(3,1);  //e
          digitalWrite(2,1);  //f
          digitalWrite(1,0);  //g
          digitalWrite(0,0);  //dp
          break;

          case 1:
          digitalWrite(11,1);
          digitalWrite(10,1);
          digitalWrite(9,1);
          digitalWrite(8,0);
          digitalWrite(7,0);  //a
          digitalWrite(6,1);  //b
          digitalWrite(5,1);  //c
          digitalWrite(4,0);  //d
          digitalWrite(3,0);  //e
          digitalWrite(2,0);  //f
          digitalWrite(1,0);  //g
          digitalWrite(0,0);  //dp
          break;
          
          case 2:
          digitalWrite(11,1);
          digitalWrite(10,1);
          digitalWrite(9,0);
          digitalWrite(8,1);
          digitalWrite(7,1);  //a
          digitalWrite(6,1);  //b
          digitalWrite(5,0);  //c
          digitalWrite(4,1);  //d
          digitalWrite(3,1);  //e
          digitalWrite(2,0);  //f
          digitalWrite(1,1);  //g
          digitalWrite(0,0);  //dp
          break;
          
          case 3:
          digitalWrite(11,1);
          digitalWrite(10,1);
          digitalWrite(9,0);
          digitalWrite(8,0);
          digitalWrite(7,1);  //a
          digitalWrite(6,1);  //b
          digitalWrite(5,1);  //c
          digitalWrite(4,1);  //d
          digitalWrite(3,0);  //e
          digitalWrite(2,0);  //f
          digitalWrite(1,1);  //g
          digitalWrite(0,0);  //dp
          break;
          
          case 4:
          digitalWrite(11,1);
          digitalWrite(10,0);
          digitalWrite(9,1);
          digitalWrite(8,1);
          digitalWrite(7,0);  //a
          digitalWrite(6,1);  //b
          digitalWrite(5,1);  //c
          digitalWrite(4,0);  //d
          digitalWrite(3,0);  //e
          digitalWrite(2,1);  //f
          digitalWrite(1,1);  //g
          digitalWrite(0,0);  //dp
          break;
          
          case 5:
          digitalWrite(11,1);
          digitalWrite(10,0);
          digitalWrite(9,1);
          digitalWrite(8,0);
          digitalWrite(7,1);  //a
          digitalWrite(6,0);  //b
          digitalWrite(5,1);  //c
          digitalWrite(4,1);  //d
          digitalWrite(3,0);  //e
          digitalWrite(2,1);  //f
          digitalWrite(1,1);  //g
          digitalWrite(0,0);  //dp
          break;
          
//          case 6:
//          PORTB|=0x9;
//          PORTD=0x3E;
//          break;
//          
//          case 7:
//          PORTB|=0x8;
//          PORTD=0xE0;
//          break;
//          
//          case 8:
//          PORTB|=0x7;
//          PORTD=0xFE;
//          break;
//          
//          case 9:
//          PORTB|=0x6;
//          PORTD=0xE6;
//          break;
//          
//          case 10:
//          PORTB|=0x5;
//          PORTD=0xFA;
//          break;
//          
//          case 11:
//          PORTB|=0x4;
//          PORTD=0x3E;
//          break;
//          
//          case 12:
//          PORTB|=0x3;
//          PORTD=0x1A;
//          break;
//          
//          case 13:
//          PORTB|=0x2;
//          PORTD=0x7A;
//          break;
//          
//          case 14:
//          PORTB|=0x1;
//          PORTD=0xDE;
//          break;
//          
//          case 15:
//          PORTB|=0x0;
//          PORTD=0x8E;
//          break;
        }
        
        _delay_ms(1000);
    }
    

}
