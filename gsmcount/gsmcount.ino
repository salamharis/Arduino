int inPulse = A0; 

void setup() {
  // put your setup code here, to run once:
  pinMode(inPulse,INPUT);
  Serial.begin(9600);

}

float count = 100;
void loop() {

  int readPulse = analogRead(inPulse);

  if(readPulse > 500*5/1023)
  {
    count -= 1;    //count = count - 1; //assume 1 watt
  }

  //count -= 1; //assume ever sec

  Serial.print("RM : /d",count);
  //Serial.println(count/10);

  delay(1000);
  
 

}
