#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define XTAL 16000000L //Crystal Freq.
#define TIMER_CLOCK 2 // Toggling Freq.

int main(void){DDRD &=~_BV(PD2);// PD2 (PCINT0 pin) is now an input
DDRB |=_BV(DDB5);interrupt_init();

while(1){PORTB |=_BV(DDB5);// LED on 
_delay_ms(1000);
PORTB &=~_BV(DDB5);// LED off 
_delay_ms(1000);
}
}

void interrupt_init (void) {
//EICRA |= _BV(ISC01); // set INT0 to trigger on ANY logic change 
EIMSK |= (1 << INT0);     // Turns on INT0
sei();                    // turn on interrupts
}

ISR (INT0_vect) {
PORTB &= ~_BV(DDB5); // LED off
_delay_ms(1000);
}

