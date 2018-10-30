// Makes a sequence of beeps with a Buzzer

// Connect a buzzer to pin 7
const int BUZZ_PIN = 2;

void setup()
{
  //Declares pin 7 as Output
  pinMode(BUZZ_PIN, OUTPUT);
}

void loop()
{
  buzz();  // Plays a long beep
  delay(300);  // Waits for 300 milliseconds
}


// Generates a pulse of duty cycle 50%
// and period 800 milliseconds



void buzz()
{
  digitalWrite(BUZZ_PIN, HIGH);
  delay(400);
  digitalWrite(BUZZ_PIN, LOW);
  delay(400);
  digitalWrite(BUZZ_PIN, HIGH);
  delay(700);
  digitalWrite(BUZZ_PIN, LOW);
  delay(700);
}

