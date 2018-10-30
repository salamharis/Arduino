/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/
int IN_PIN1 = A0;
int OUT_PIN1 = 13;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
float voltage[100];
float voltagesum = 0;
float voltageavg = 0;
void loop() {
   //read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  //for(int i=0;i<100;i++){
  Serial.println(sensorValue);
  //voltage[i] = sensorValue;//* (5.0 / 1023.0);
  // print out the value you read:
  //voltagesum += voltage[i];
  
 // }
  //voltageavg = voltagesum/100;
  //Serial.println(voltageavg);
  //voltagesum = 0;

//      pinMode(IN_PIN1, INPUT);
//      digitalWrite(OUT_PIN1, HIGH);
//      delay(50);
//      float val1 = analogRead(IN_PIN1);
//      Serial.println(val1);
//      digitalWrite(OUT_PIN1, LOW);
//      pinMode(IN_PIN1, OUTPUT);
//      delay(100);
}
