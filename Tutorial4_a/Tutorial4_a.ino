#include <inttypes.h> //short forms for various integer types
#include <avr/io.h>
#include <util/delay.h>

int main(void){
  uint8_t i=0;
  DDRD |=_BV(PD6);// set OC0A pin as output
  timer1_init();
  
  while(1){
    /* dimmLED on */
    for(i=0;i<255;i++){
      OCR0A =i;// Write to pin 1 (OCR1A)
      _delay_ms(10);//delay 10 ms
      }
      
      /* dimmLED off */
      for(i=255;i>0;i--){
        OCR0A =i;//Write to pin 1 (OCR1A)
        _delay_ms(10);//delay 10 ms
        }
      }
       return 0;
    }
    
  
void timer1_init(void){
  // enable 8 bit fast PWM, select inverted PWM
  TCCR0A =_BV(WGM01)|_BV(WGM00)|_BV(COM0A1)|_BV(COM0A0);
  // clear timer/counter1 on Compare Match
  // PWM frequency = MCU clock/8/512, 
  // e.g. with 4Mhz Crystal 977 Hz.
  TCCR0B =_BV(CS01)|_BV(CS00);
 }


