#include <avr/io.h>

int main(void)
{
  // Initializing
  DDRB |=_BV(DDB5);// Configure port B, pin 13 as output, set bit 1
  DDRC =0x00;// Configure port C, pin A as input, clear bit 0
  InitADC();// Initialize the ADC
  Serial.begin(9600);// Initialize Serial Communication
  uint16_t adc_value;// declare a variable for adcvalue
  
  while(1)
  {
    adc_value=ReadADC(5);// Read Analog value from channel
    Serial.println(adc_value);// Serial Communication start 
      if(adc_value<512)
          {
            PORTB &=~_BV(DDB5);// LED off
          }
      else
          {
            PORTB |=_BV(DDB5);// LED on
          }
      }
  }


  
  void InitADC()
  {
    ADMUX=_BV(REFS0);// For Aref=AVcc, Can be writternas ADMUX=0x40; 
    ADCSRA =_BV(ADEN)|_BV(ADPS2)|_BV(ADPS1)|_BV(ADPS0);// ADEN: Set to turn on ADC , by default it is turned off // ADPS2: ADPS2, ADPS1 and ADPS0 set to make division factor 128 
  }
  
  uint16_t ReadADC(uint8_t ch)
  {
    ch=ch&0b00000111;//Select ADC Channel chmust be 0-7
    ADMUX |=ch;
    ADCSRA |=_BV(ADSC);;// Start conversion, set bit 1
    while(ADCSRA &_BV(ADSC));// wait for conversion to complete  
  
    return(ADCW);// return the value of ADC to main()
  }

