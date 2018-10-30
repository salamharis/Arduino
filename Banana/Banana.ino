int sensor1 = A0;
int sensor2 = A1;
void setup() {
  // put your setup code here, to run once:
pinMode(8, OUTPUT);
pinMode(sensor1,INPUT);
pinMode(sensor2,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print(analogRead(sensor1));
Serial.print(",");
Serial.println(analogRead(sensor2));
delay(10);
if(analogRead(sensor1)>350)
{
  tone(8,349,200);
  delay(10);
}
else if(analogRead(sensor2)>350)
{
  tone(8,261,200);
  delay(10);
}
}
