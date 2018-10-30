/*
7 LED segments demo counter program from electronicsblog.net.
If You share/use this code elsewhere on the internet please mention this code source.
*/

// segment | Arduino board PIN number 

#define G 11
#define F 12
#define A 6
#define B 7
#define E 10
#define D 9
#define C 8
#define DP 13

// Commonn cathodes control
#define GND1 2
#define GND2 3
#define GND3 4
#define GND4 5

int timer=0; 

int i=0;
// functions to display digits

void digit0 () {
// for 0 needed to turn ON F A B C D E segments, so:

digitalWrite(A, HIGH);
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, HIGH);
digitalWrite(E, HIGH);
digitalWrite(F, HIGH);

//////////////////////// G segment should be turn OFF
digitalWrite(G, LOW);

};

void digit1 () {

digitalWrite(A,LOW);
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, LOW);
digitalWrite(E, LOW);
digitalWrite(F, LOW);
digitalWrite(G, LOW);
};

void digit2 () {

digitalWrite(A,HIGH);
digitalWrite(B, HIGH);
digitalWrite(C, LOW);
digitalWrite(D, HIGH);
digitalWrite(E, HIGH);
digitalWrite(F, LOW);
digitalWrite(G, HIGH);
};

void digit3 () {

digitalWrite(A,HIGH);
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, HIGH);
digitalWrite(E, LOW);
digitalWrite(F, LOW);
digitalWrite(G, HIGH);
};

void digit4 () {

digitalWrite(A,LOW);
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, LOW);
digitalWrite(E, LOW);
digitalWrite(F, HIGH);
digitalWrite(G, HIGH);
};

void digit5 () {

digitalWrite(A,HIGH);
digitalWrite(B, LOW);
digitalWrite(C, HIGH);
digitalWrite(D, HIGH);
digitalWrite(E, LOW);
digitalWrite(F, HIGH);
digitalWrite(G, HIGH);
};

void digit6 () {

digitalWrite(A,HIGH);
digitalWrite(B, LOW);
digitalWrite(C, HIGH);
digitalWrite(D, HIGH);
digitalWrite(E, HIGH);
digitalWrite(F, HIGH);
digitalWrite(G, HIGH);
};

void digit7 () {

digitalWrite(A,HIGH);
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, LOW);
digitalWrite(E, LOW);
digitalWrite(F, LOW);
digitalWrite(G, LOW);
};

void digit8 () {

digitalWrite(A, HIGH);
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, HIGH);
digitalWrite(E, HIGH);
digitalWrite(F, HIGH);
digitalWrite(G, HIGH);

};

void digit9 () {

digitalWrite(A, HIGH);
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, HIGH);
digitalWrite(E, LOW);
digitalWrite(F, HIGH);
digitalWrite(G, HIGH);

};

//function to display digit from inputed int

void showdigit (int digit)

{

 switch (digit) {

 case 0:
 digit0 ();
 break;

 case 1:
 digit1 ();
 break;

 case 2:
 digit2 ();
 break;

 case 3:
 digit3 ();
 break;

 case 4:
 digit4 ();
 break;

 case 5:
 digit5 ();
 break;

 case 6:
 digit6 ();
 break;

 case 7:
 digit7 ();
 break;

 case 8:
 digit8 ();
 break;

 case 9:
 digit9 ();
 break;

 default:

 break;

 }; 

};

// showing 4 digits
void showdigits (int number)
{

// e.g. we have "1234"
showdigit(number/1000);  // segments are set to display "1"
digitalWrite(GND1, HIGH); // first digit on,
digitalWrite(GND2, LOW); // other off
digitalWrite(GND3, LOW);
digitalWrite(GND4, LOW);

delay (1);

number = number%1000;  // remainder of 1234/1000 is 234
digitalWrite(GND1, LOW); // first digit is off
 showdigit(number/100); //// segments are set to display "2"
digitalWrite(GND2, HIGH); // second digit is on
 delay (1); // and so on....

number =number%100;    
digitalWrite(GND2, LOW);
showdigit(number/10);
digitalWrite(GND3, HIGH);
delay (1);

number =number%10; 
digitalWrite(GND3, LOW);
showdigit(number); 
digitalWrite(GND4, HIGH);
 delay (1);

}; 

void setup()

{

pinMode(A, OUTPUT);
pinMode(B, OUTPUT);
pinMode(C, OUTPUT);
pinMode(D, OUTPUT);
pinMode(E, OUTPUT);
pinMode(F, OUTPUT);
pinMode(G, OUTPUT);
pinMode(DP, OUTPUT);

pinMode(GND1, OUTPUT);
pinMode(GND2, OUTPUT);
pinMode(GND3, OUTPUT);
pinMode(GND4, OUTPUT);

};
void loop ()

{ 
  delay(100);
  timer++;

 showdigits (i);

  if (timer==10) {

timer=0;

i++;

if (i>10000) {i=0;};

if (i%2) { digitalWrite(DP, HIGH); }

else  {digitalWrite(DP, LOW); };

  }; 

};
