/*
   SDC Booth

   Components needed:  1 Toggle, 1 Potentiometer slider, 2 Potentiometers, 2 - 7 segment displays,  

*/
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

const int TOGGLEPIN = 1;
const int SLIDEPIN = A0;
const int POTPINWIND = A1;
const int POTPINRAIN = A2;
const int maxTemp = 100;
const int minTemp = 0;

int temp;
int wind;
int rain;
bool timeOfDay;
bool outTemp;
bool outWind;
int potentiometer;

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  pinMode(POTPIN, INPUT_PULLUP);
  matrix.begin(0x70);

}

void loop() {
  //potentiometer (wind)
  pWind = analogRead(POTPINWIND);
  wind = map(pWind, 0, 1023, -2, 200);
  matrix.print(wind, DEC);
  if (wind > 100) {
    outWind = HIGH;

  }
  else {
    outWind = LOW
  }
  matrix.writeDisplay();
  Serial.println(pWind);

   //potentiometer (rain)
  pRain = analogRead(POTPINRAIN);
  rain = map(pRain, 0, 1023, 0, 3);
  matrix.print(rain, DEC);

  
  // toggle pin (day and night)
  if (digitalRead(TOGGLEPIN) == HIGH ) {
    timeOfDay = HIGH;
  }
  else {
    timeOfDay = LOW;
  }

  // slide potentiometer for temperature 
  int slidePot = analogRead(SLIDEPIN);
  temp = map(slidePot, 0, 1023, minTemp, maxTemp);
  //Serial.write(temp);

}
