#include <avr/io.h>
#include <inttypes.h>

int main()
{
  int data;
  USARTInit(68);//UBRR = 51
  
  while(1)
  {
    //Read data
    data=USARTReadChar();
    /* Now send the same data but butsurround it in
    square bracket. For example if user sent 'a' our
    system will echo back '[a]'.*/
    
        USARTWriteChar('[');
        USARTWriteChar(data);
        USARTWriteChar(']');
  }
}
    
    void USARTInit(uint16_t ubrr_value)
    {
      //Set Baud rate
      UBRR0L =ubrr_value;
      UBRR0H =(ubrr_value>>8);
      UCSR0C=(1<<USBS0)|(3<<UCSZ00);
      UCSR0B=(1<<RXEN0)|(1<<TXEN0);         //Enable The receiver and transmitter
    }
      //This function is used to read the available data
      //from USART. This function will wait untilldata is
      //available.
     
      char USARTReadChar()
    {
      while(!(UCSR0A &(1<<RXC0)));        //Wait untilla data is available
        
        //Now USART has got data from host
        //and is available is buffer
        
      return UDR0;
    }
        
       //This fuctionwrites the given "data" to
       //the USART which then transmit it via TX line
       
       void USARTWriteChar(int data)
     {
       //Wait untill the transmitter is ready 
       
       while(!(UCSR0A &(1<<UDRE0)));
       
       //Now write the data to USART buffer
       UDR0=data;
     }

