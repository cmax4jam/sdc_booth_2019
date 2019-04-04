#include <TM1637Display.h>
#include <Encoder.h>


volatile boolean TurnDetected;
volatile boolean up;

const int rCLK=2;                   // Used for generating interrupts using CLK signal
const int rDT=3;                    // Used for reading DT signal
const int dCLK=4; //display pin 
const int dDIO=5; //display pin
const int MIN_WIND=0;
const int MAX_WIND=200;
const int WIND_THRESHOLD = 55;
TM1637Display display(dCLK, dDIO);

void isr ()  {                    // Interrupt service routine is executed when a HIGH to LOW transition is detected on CLK
 if (digitalRead(rCLK))
   up = digitalRead(rDT);
 else
   up = !digitalRead(rDT);
 TurnDetected = true;
}


void setup ()  {
 pinMode(rCLK,INPUT);
 pinMode(rDT,INPUT);  
 attachInterrupt (0,isr,FALLING);   // interrupt 0 is always connected to pin 2 on Arduino UNO
 Serial.begin (9600);
 display.setBrightness(0x0a);
}

void loop ()  {
 static long virtualPosition=0;    // without STATIC it does not count correctly!!!
 
 if (TurnDetected)  {        // do this only if rotation was detected
   if (up)
     virtualPosition = virtualPosition + 2;
   else
     virtualPosition = virtualPosition - 2;
   TurnDetected = false;          // do NOT repeat IF loop until new rotation detected
 }

 if (virtualPosition >= MAX_WIND) {
  virtualPosition = 200;
 }
 else if (virtualPosition <= MIN_WIND) {
  virtualPosition = 0;
 }

 String wind_level;
 if (virtualPosition >= WIND_THRESHOLD) {
   wind_level = "high_wind";
 }
 else {
  wind_level = "low_wind";
 }

display.showNumberDec(virtualPosition);
 

 
}
