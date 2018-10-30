#include <avr/io.h>
#include <util/delay.h>

int main(void)
{ 
  DDRB |=_BV(DDB5);// Configure port B, pin 13 as output, set bit 1 
  DDRB &=~_BV(DDB2);// Configure port B, pin 9 as input, clear bit 0
  unsigned int val=0; 
  
  while(1)
  { 
    val=PINB &_BV(PB2);// read input from pin 9
    if(val)
     {
      PORTB |=_BV(DDB5);// LED on
      _delay_ms(1000);// Wait for 1s
     }
      else
     {
        PORTB &=~_BV(DDB5);// Display Number 5
        _delay_ms(1000);// Wait for 1s
     }
    }
   return 0;
}

