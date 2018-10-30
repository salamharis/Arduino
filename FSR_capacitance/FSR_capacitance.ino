
const int OUT_PIN1 = 6;
const int IN_PIN1 = A0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //set USB baudrate: 9600

}

int n=100; //num of reading
int valsum = 0;
int valavg = 0;

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<n;i++){
        pinMode(IN_PIN1, INPUT);
       digitalWrite(OUT_PIN1, HIGH);
       delay(50);
       int val = analogRead(IN_PIN1);
       Serial.println(val);
       digitalWrite(OUT_PIN1, LOW);
       pinMode(IN_PIN1, OUTPUT);
       valsum += val;
  }
  valavg = valsum/n;
  valsum = 0;  //reset the value sum

}
