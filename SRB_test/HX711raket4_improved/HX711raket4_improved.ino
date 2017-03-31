// Code made by Jens Dalsgaard Nielsen ( https://github.com/jdn-aau ), improved a bit (filtering) by Raphaël Casimir ( https://github.com/raphaelcasimir )
// To use with a weight scale and HX711 ADC. Ask Jens at AAU for the scale. Useful to measure rocket motor thrust.

#include "HX711.h"
#include "looptime.h"
#define PINMIN 5
#define PINMAX 10

#define GND 11
#define SW 12
#define LED 13

#define BUFF_SIZE 4

short int portNr = 0;
short int buffPos=0;
long buff[BUFF_SIZE];
char res=0;
 
HX711 scale;


void initNumberPorts()
{
  for (int i = PINMIN; i <= PINMAX; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  pinMode(GND, OUTPUT); // GND for switch
  digitalWrite(GND, LOW);

  pinMode(SW, INPUT_PULLUP); // for step switch
  
  pinMode(LED, OUTPUT); //LED
  digitalWrite(LED,LOW); // OFF
}

int rdPortNumber(void)
{
  int n = 0;
  for (int i = PINMIN; i <= PINMAX; i++) {
    n *= 2 ;
    n += digitalRead(i);
  }
  return n;
}

void testSwitch()
{
  static unsigned long t = 0, t1;
  t1 = millis() - t;

  if (1000 < t1) {
    
    digitalWrite(LED,LOW);
    
    if (digitalRead(SW) == HIGH) {
      digitalWrite(LED, HIGH);
      t = millis();
      portNr++;
    }
  }
}


long buffRead() {
  long temp=0;
  temp=(long)scale.read();

  if( abs(temp/buff[buffPos]) < 10^3 ) { // Filter spikes due to errors
    buff[buffPos]=temp;
  }
  buffPos= (buffPos+1) % BUFF_SIZE;
  
  temp=0;
  for(int i=0; i<BUFF_SIZE; i++) {
    temp+=buff[i];
  }
  temp=temp/BUFF_SIZE;
  return temp;
}

void setup() {
  Serial.begin(57600);
  pinMode(2,INPUT); //TEST
  initNumberPorts();  // get initial diwpswitch setup of port nr
  delay(50);
  portNr = rdPortNumber();

  scale.begin(A1, A0);

  for (int i=0; i<BUFF_SIZE; i++)
  {
    delay(15);
    buff[i]=scale.read();
  }
}

void loop() {
 
  while (1) {
    looptime(15);
      testSwitch(); // test if key is pressed and increment portNr
      Serial.print(portNr); Serial.print(" ");
      Serial.print(millis());
      Serial.print(" ");
      
      Serial.println(buffRead());
  }
}

