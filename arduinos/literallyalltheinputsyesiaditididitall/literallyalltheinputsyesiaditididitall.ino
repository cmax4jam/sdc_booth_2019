/*
   SDC Booth

   Components needed:  1 Toggle, 1 Slider,

*/
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

const int TOGGLEPIN = 1;
const int SLIDEPIN = A0;
const int POTPIN = A1;
const int maxTemp = 100;
const int minTemp = 0;

int temp;
int wind;
bool timeOfDay;
int potentiometer;

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  pinMode(POTPIN, INPUT_PULLUP);
  matrix.begin(0x70);

}

void loop() {

  //potentiometer stuff
  potentiometer = analogRead(POTPIN);
  wind = map(potentiometer, 0, 1023, -2, 200);
   matrix.print(wind, DEC);
    
  matrix.writeDisplay();
  Serial.println(potentiometer);
  //
  if (digitalRead(TOGGLEPIN) == HIGH ) {
    timeOfDay = LOW;
  }
  else {
    timeOfDay = HIGH;
  }
  int slidePot = analogRead(SLIDEPIN);
  temp = map(slidePot, 0, 1023, minTemp, maxTemp);
  //Serial.write(temp);

}
