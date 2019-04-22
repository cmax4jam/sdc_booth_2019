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
const int OUTPUTONE = 8;
const int OUTPUTTWO = 9;
const int OUTPUTTHREE = 10;

int temp;
int wind;
int rain;
int pWind;
int pRain;
bool timeOfDay;
int slidePot;
int potentiometer;
String weather;
String readValue;


//Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  pinMode(POTPINWIND, INPUT_PULLUP);
  pinMode(POTPINRAIN, INPUT_PULLUP);
  pinMode(OUTPUTONE, OUTPUT);
  pinMode(OUTPUTTWO, OUTPUT);
  pinMode(OUTPUTTHREE, OUTPUT);
  //matrix.begin(0x70);

}

void loop() {
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
  if (temp >= 512 && wind >= 512 && rain < 341){ //tornado
    digitalWrite(OUTPUTONE, HIGH);
    digitalWrite(OUTPUTTWO, LOW);
    digitalWrite(OUTPUTTHREE, LOW);  
  }
  else if (temp >= 512 && wind >= 512 && rain >= 682){ //hurricane
    digitalWrite(OUTPUTONE, LOW);
    digitalWrite(OUTPUTTWO, HIGH);
    digitalWrite(OUTPUTTHREE, LOW);  
  }
  else if (timeOfDay == LOW && rain < 341) { //night
    digitalWrite(OUTPUTONE, LOW);
    digitalWrite(OUTPUTTWO, LOW);
    digitalWrite(OUTPUTTHREE, HIGH);  
  }
  else if(timeOfDay == HIGH && rain < 341){ //sun
    digitalWrite(OUTPUTONE, HIGH);
    digitalWrite(OUTPUTTWO, HIGH);
    digitalWrite(OUTPUTTHREE, LOW);  
  }
  else if(timeOfDay == HIGH && wind < 512 && rain >= 341 && rain < 682 && temp >= 512){ //rainbow
    digitalWrite(OUTPUTONE, HIGH);
    digitalWrite(OUTPUTTWO, LOW);
    digitalWrite(OUTPUTTHREE, HIGH);   
  }
  else if( rain >= 341 && temp < 512){ //snow
    digitalWrite(OUTPUTONE, LOW);
    digitalWrite(OUTPUTTWO, HIGH);
    digitalWrite(OUTPUTTHREE, HIGH);  
  }
  else{ //rain
    digitalWrite(OUTPUTONE, HIGH);
    digitalWrite(OUTPUTTWO, HIGH);
    digitalWrite(OUTPUTTHREE, HIGH);  
  }
 
}
