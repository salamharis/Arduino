#include <VirtualWire.h>


const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;
int InputPin1 = 1;
int InputPin2 = 2;
int InputPin3 = 3;
int InputPin4 = 4;
int InputPin5 = 5;

void setup()
{
    // Initialise the IO and ISR
    Serial.begin(9600);
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);       // Bits per sec
    pinMode(InputPin1, OUTPUT);
    pinMode(InputPin2, OUTPUT);
    pinMode(InputPin3, OUTPUT);
    pinMode(InputPin4, OUTPUT);
    pinMode(InputPin5, OUTPUT);
}


char msg[5];

void loop()
{


  msg[0] = Read(InputPin1);
  msg[1] = Read(InputPin2);
  msg[2] = Read(InputPin3);
  msg[3] = Read(InputPin4);
  msg[4] = Read(InputPin5);

  for (int i = 0; i < 5; i++)
          {
              Serial.print(msg[i]);
              Serial.print(' ');
             
          }
          Serial.println();


  vw_send((uint8_t *)msg, 5);
  vw_wait_tx(); // Wait until the whole message is gone

  delay(500);

}

//to make sure the others analog pin do not influenced by the value changes
int Read(int a){
  pinMode(a, INPUT);
  int b = analogRead(a);
  pinMode(a, OUTPUT);
  return b;
}

