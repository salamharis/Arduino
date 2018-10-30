#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
  DDRD =0xFF;// Configure port D as output

while(1)
    {
          PORTD =0b10011111;// Display Number 1
          _delay_ms(1000);// Wait for 1s
          PORTD =0b00100100;// Display Number 2
          _delay_ms(1000);// Wait for 1s
          PORTD =0b00000011;// Display Number 0
          _delay_ms(1000);// Wait for 1s
          PORTD =0b00001001;// Display Number 9
          _delay_ms(1000);// Wait for 1s
          PORTD =0b10011111;// Display Number 1
          _delay_ms(1000);// Wait for 1s
          PORTD =0b01001001;// Display Number 5
          _delay_ms(1000);// Wait for 1s
    }
  return 0;
}
