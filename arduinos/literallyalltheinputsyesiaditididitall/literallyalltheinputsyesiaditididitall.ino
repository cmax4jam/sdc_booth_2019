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
int pWind;
int pRain;
int binTemp;
bool timeOfDay;
bool outTemp;
bool outWind;
int potentiometer;

//Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  pinMode(POTPINWIND, INPUT_PULLUP);
  pinMode(POTPINRAIN, INPUT_PULLUP);
  //matrix.begin(0x70);

}

void loop() {
  //potentiometer (wind)
  pWind = analogRead(POTPINWIND);
  wind = map(pWind, 0, 1023, -2, 200);
  //matrix.print(wind, DEC);
  if (wind > 100) {
    outWind = HIGH;

  }
  else {
    outWind = LOW;
  }

   //potentiometer (rain)
  pRain = analogRead(POTPINRAIN);
  rain = map(pRain, 0, 1023, 0, 2);
  //matrix.print(rain, DEC);

  
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
  binTemp = map(temp, minTemp, maxTemp, 0 , 1);
  
  if (rain == 0 &&  timeOfDay == HIGH){
    Serial.print("Sun\n");//sun 
  }
  
  else if (rain == 0 && binTemp == 1 && outWind == HIGH){
    Serial.print("Tornado\n");// tornado 
  }
  else if (rain != 0 && binTemp == 0) { 
    Serial.print("Snow\n");// snow 
  }
  else if( outWind == HIGH && rain == 2 && binTemp == 1){
    Serial.print("Hurricane\n"); // hurricane
  }
  else if(outWind == LOW && rain != 0 &&  binTemp == 1){
    Serial.print("Rain\n"); // rain 
  }
  else if( rain == 1 && timeOfDay == HIGH && binTemp == 1){
    Serial.print("Rainbow\n");// rainbow
  }

  

}
