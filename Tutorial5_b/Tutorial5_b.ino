#include <inttypes.h>  //short forms for various integer types
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define XTAL         16000000L //Crystal Freq.
#define TIMER_CLOCK     2       // Toggling Freq.

int main(void)
{
uint8_t i = 0;
DDRD &= ~_BV(PD2);  // PD2 (PCINT0 pin) is now an input 
DDRB = _BV(PB1);
interrupt_init ();

while(1) {

/* dimm LED on */
for (i=0; i<255; i++) {

timer1_int_PWM();
OCR1A = i;         // Write to pin 1 (OCR1A)
_delay_ms(10);     //delay 10 ms
}

/* dimm LED off */
for( i=255; i>0; i--) {
OCR1A = i;         //Write to pin 1 (OCR1A)
_delay_ms(10);     //delay 10 ms
}
}
}

void interrupt_init (void) {
//EICRA |=  _BV(ISC01);    // set INT0 to trigger on ANY logic change 
EIMSK |= (1 << INT0);     // Turns on INT0
sei();                    // turn on interrupts
}


void timer1_int_PWM (void) {
timer1_disable ();
// enable fast PWM, select inverted PWM
TCCR1A =  _BV(WGM10) | _BV(COM1A1) | _BV(COM1A0);
// clear timer/counter1 on Compare Match
// PWM frequency = MCU clock/8/512,     // e.g. with 4Mhz Crystal 977 Hz. 
TCCR1B = _BV(CS11) | _BV(WGM12);
}


void timer1_int_CTC (void) {
timer1_disable ();
TCCR1A = _BV(COM1A0); // enable toggle OC1A output on compare
TCCR1B = _BV(CS10) | _BV(CS11) | _BV(WGM12); // prescaler=64, clear timer/counter on compareA match
}


void timer1_disable (void) {
TCCR1B = 0;   // disable all interruptions for timer1 
TCCR1A = 0;   // disable all interruptions for  timer1
}

ISR (INT0_vect) {
timer1_int_CTC();
OCR1A = ((XTAL/64)/(2*TIMER_CLOCK)) - 1;
}

