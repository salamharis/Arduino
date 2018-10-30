#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#define FOSC 16000000 //Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
char buffer[5];//Output of the itoafunction

int main(void){
  // Initializing 
  DDRB |=_BV(DDB5);// Configure port B, pin 13 as output, set bit 1
  DDRC =0x00;// Configure port C, pin A as input, clear bit 0
  InitADC();// Initialize the ADC 
  USART_Init(MYUBRR);// Initialize Serial Communication
  uint16_t adc_value;// declare a variable for adcvalue
  
  while(1){
    adc_value=ReadADC(0);// Read Analog value from channel
    // Serial Communication start
    itoa(adc_value,buffer,10);
    USART_putstring(buffer);
    _delay_ms(500);;
    USART_Transmit('\n');
    
    if(adc_value<512){
      PORTB &=~_BV(DDB5);// LED off
      }
      else{
        PORTB |=_BV(DDB5);// LED on
      }
     }
    }
     void InitADC(){
      ADMUX=_BV(REFS0);
      // For Aref=AVcc, Can be writternas ADMUX=0x40; 
      ADCSRA =_BV(ADEN)|_BV(ADPS2)|_BV(ADPS1)|_BV(ADPS0);
      // ADEN: Set to turn on ADC , by default it is turned off 
      // ADPS2: ADPS2, ADPS1 and ADPS0 set to make division factor 128 
      }
      
      uint16_t ReadADC(uint8_t ch){
        ch=ch&0b00000111;//Select ADC Channel chmust be 0-7
        ADMUX |=ch;
        ADCSRA |=_BV(ADSC);;// Start conversion, set bit 1
        while(ADCSRA &_BV(ADSC));// wait for conversion to complete 
        return(ADCW);// return the value of ADC to main()
        }
        
        void USART_Init(uint16_t ubrr){
          // Set baud rate
          UBRR0H =(ubrr>>8);
          UBRR0L =ubrr;
          UCSR0B =(1<<RXEN0)|(1<<TXEN0);// Enable receiver and transmitter
          UCSR0C =(1<<USBS0)|(3<<UCSZ00);// Set frame format: 8 data, 2 stop bit
          }
          
          // This fuctionwrites the given "data" to the USART which then transmit it via TX line
          void USART_Transmit(int data){
            // Wait for empty transmit buffer
            while(!(UCSR0A &(1<<UDRE0)));// Put data into buffer, sends the data
            UDR0 =data;
            }
            
            void USART_putstring(char*StringPtr){
              while(*StringPtr!=0x00){
                USART_Transmit(*StringPtr);
                StringPtr++;}
             }

