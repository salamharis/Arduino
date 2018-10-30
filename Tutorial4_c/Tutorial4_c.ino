#define F_CPU 16000000 // 16 MHz
#include <inttypes.h> //short forms for various integer types
#include <avr/io.h>#include <util/delay.h>#define XTAL 16000000L //Crystal Freq.#define TIMER_CLOCK 2 // Toggling Freq.intmain(void){uint8_t i=0;DDRD =_BV(PD6);DDRB =_BV(PB1);// set OC1A pin as outputtimer0_int_PWM();timer1_int_CTC();while(1){/* dimmLED on */for(i=0;i<255;i++){OCR0A =i;// Write to pin 1 (OCR0A)_delay_ms(10);//delay 10 ms}/* dimmLED off */for(i=255;i>0;i--){OCR0A =i;//Write to pin 1 (OCR0A)_delay_ms(10);//delay 10 ms}OCR1A =((XTAL/64)/(2*TIMER_CLOCK))-1;}return0;}
