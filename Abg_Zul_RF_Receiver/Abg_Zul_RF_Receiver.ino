#include <VirtualWire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10); // RX, TX


const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;
int InputPin1 = 1;
int InputPin2 = 2;
int InputPin3 = 3;
int InputPin4 = 4;
int InputPin5 = 5;

void setup()
{
    delay(100);
    Serial.begin(9600);	// Debugging only
    mySerial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
    
    pinMode(InputPin1, OUTPUT);  //initialise the input pin
    pinMode(InputPin2, OUTPUT);
    pinMode(InputPin3, OUTPUT);
    pinMode(InputPin4, OUTPUT);
    pinMode(InputPin5, OUTPUT);
}

int msg[10];

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
    	int i;
      msg[0] = Read(InputPin1);   //fsr reading from receiver
      msg[1] = Read(InputPin2);
      msg[2] = Read(InputPin3);
      msg[3] = Read(InputPin4);
      msg[4] = Read(InputPin5);
      msg[5] = buf[0];  //fsr reading from transmitter
      msg[6] = buf[1];
      msg[7] = buf[2];
      msg[8] = buf[3];
      msg[9] = buf[4];


    	Serial.print("Got: ");
      
    	
        	for (i = 0; i < 10; i++)
        	{
              Serial.print(msg[i]);
              Serial.print(' ');
        	    mySerial.print(msg[i]);
        	    mySerial.print(' ');
        	}
          Serial.println();
        	mySerial.println();
         delay(500);
         
    }


}

//to make sure the others analog pin do not influenced by the value changes
int Read(int a){
  pinMode(a, INPUT);
  int b = analogRead(a);
  pinMode(a, OUTPUT);
  return b;
}
