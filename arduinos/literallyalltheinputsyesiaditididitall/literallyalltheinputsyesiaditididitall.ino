/*
   SDC Booth

   Components needed:  1 Toggle, 1 Potentiometer slider, 2 Potentiometers, 2 - 7 segment displays,  

*/
#include <Wire.h>

const int TOGGLEPIN = 2;
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
bool timeOfDay;
int slidePot;
int potentiometer;
int counter = 0;

//Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  pinMode(POTPINWIND, INPUT_PULLUP);
  pinMode(POTPINRAIN, INPUT_PULLUP);
  //matrix.begin(0x70);

}

void loop() {
  counter++;
  //potentiometer (wind)
  wind = analogRead(POTPINWIND);
  //matrix.print(wind, DEC);
//  if (wind > 100) {
//    outWind = HIGH;
//
//  }
//  else {
//    outWind = LOW;
//  }

   //potentiometer (rain)
  rain = analogRead(POTPINRAIN);
  //matrix.print(rain, DEC);

  // toggle pin (day and night)
  if (digitalRead(TOGGLEPIN) == HIGH ) {
    timeOfDay = HIGH;
  }
  else {
    timeOfDay = LOW;
  }
  
  temp = analogRead(SLIDEPIN);


  // slide potentiometer for temperature 
  if (counter % 2000 == 0) {
    if (temp >= 512 && wind >= 512 && rain < 341){
      Serial.print("Tornado\n");//sun 
    }
    else if (temp >= 512 && wind >= 512 && rain >= 682){
      Serial.print("Hurricane\n");// tornado 
    }
    else if (timeOfDay == LOW && rain < 341) { 
      Serial.print("Night\n");// snow 
    }
    else if(timeOfDay == HIGH && rain < 341){
      Serial.print("Sun\n"); // hurricane
    }
    else if(timeOfDay == HIGH && wind < 512 && rain >= 341 && rain < 682 && temp >= 512){
      Serial.print("Rainbow\n"); // rain 
    }
    else if( rain >= 341 && temp < 512){
      Serial.print("Snow\n");// rainbow
    }
    else{
      Serial.println("Rain\n");
    }
    Serial.println("------");
    Serial.println(rain);
    Serial.println(timeOfDay);
    Serial.println(wind);
    Serial.println(temp);
    Serial.println("------");
    counter = 0;
  }

}
