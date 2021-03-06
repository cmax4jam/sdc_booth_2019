/* Welcome to DmxSimple. This library allows you to control DMX stage and
** architectural lighting and visual effects easily from Arduino. DmxSimple
** is compatible with the Tinker.it! DMX shield and all known DIY Arduino
** DMX control circuits.
**
** DmxSimple is available from: http://code.google.com/p/tinkerit/
** Help and support: http://groups.google.com/group/dmxsimple       */

/* To use DmxSimple, you will need the following line. Arduino will
** auto-insert it if you select Sketch > Import Library > DmxSimple. */

#include <DmxSimple.h>

unsigned long storm_start;

// How long each weather effect lasts
// 10 seconds
unsigned long weather_duration = 10000;

void setup() {
  /* The most common pin for DMX output is pin 3, which DmxSimple
  ** uses by default. If you need to change that, do it here. */
  DmxSimple.usePin(2);

  Serial.begin(9600);

  /* DMX devices typically need to receive a complete set of channels
  ** even if you only need to adjust the first channel. You can
  ** easily change the number of channels sent here. If you don't
  ** do this, DmxSimple will set the maximum channel number to the
  ** highest channel you both_write() to. */
  DmxSimple.maxChannel(256);
}

void allOff(){
  both_write(1,0);
}

/*
 * Returns the number of milliseconds to wait before triggering the next lightning strike
 */
long lightning_time(){
  return random(450,3000);
}

void both_write(int chan, int val){
  DmxSimple.write(chan, val);
  DmxSimple.write(chan + 4, val);
}

void lightning(){

  unsigned long lightning_duration = 100;

  both_write(1,0);
  
  both_write(2, 255); //R
  both_write(3, 255); //G
  both_write(4, 155); //B

  delay(100);

  // If it is time to start the lightning strike
  DmxSimple.write(1,128);
  delay(33);
  DmxSimple.write(5,128);

  delay(lightning_duration/3 - 33);
  DmxSimple.write(1,0);

  delay(33);
  DmxSimple.write(5,0);

  delay(lightning_duration/3 - 33);
  
  DmxSimple.write(1,128);

  delay(33);

  DmxSimple.write(5,128);

  delay(lightning_duration/3 + 50 - 33);

  return;
}

void rain(){

  // The time in milliseconds to stop the flash
  unsigned long lightning_stop;

  // If there is currently a flash going on
  boolean lightning_on = false;
  
  unsigned long rain_start = millis();

  unsigned long lightning_start = rain_start + lightning_time();

  // Whether it should be getting brighter or darker
  int sign = 1;

  int red = 50;

  both_write(1, 100);
  both_write(2, red);
  both_write(3, 0);
  both_write(4,200);

  while(millis() < rain_start + weather_duration){
    both_write(3,red);
    red = red + sign;

    if(red > 60){
      sign = -1;
    } else if (red < 10){
      sign = 1;
    }

    // If it is time for lightning
    if(millis() >= lightning_start){
      // Trigger the lightning flash
      lightning();

      // Continue the cycle
      both_write(1, 100);
      both_write(2, red);
      both_write(3, 0);
      both_write(4,200);

      // Find the next lightning bolt
      lightning_start = millis() + lightning_time();
    }

    delay(20);
  }

  both_write(1,255);
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  both_write(2, red);
  both_write(3, green);
  both_write(4, blue);
 }

void rainbow(){
   unsigned int rgbColour[3];

  // Start off with red.
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;  

  both_write(1,255);

  // Choose the colours to increment and decrement.
  for (int decColour = 0; decColour < 3; decColour += 1) {
    int incColour = decColour == 2 ? 0 : decColour + 1;

    // cross-fade the two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;
      
      setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
      delay(13);
    }
  }
}


void snow(){
  both_write(1,255);
  both_write(2,55);
  both_write(3,55);
  both_write(4,75);

  unsigned long snow_start = millis();

  int scale = 100;
  int sign = -1;

  while(millis() < snow_start + 10000){
    
    if (scale < 40){
      sign = 1;
    } else if (scale > 90){
      sign = -1;
    }

    scale = scale + sign;

    both_write(1, 125);
    both_write(2, 55 * scale/100);
    both_write(3, 55 * scale/100);
    both_write(4, 75 * scale/100);

    delay(30);
  }
}

void sunny(){
  both_write(1,125);
  both_write(2,205);
  both_write(3,124);
  both_write(4,24);
  delay(10000);
}

long flicker_time(){
  return random(100, 1500);
}

void tornado(){
  unsigned long tornado_start = millis();

  both_write(1,255);
  both_write(2,160);
  both_write(3,160);
  both_write(4,160);

  boolean on = true;

  unsigned long flicker_start = tornado_start + flicker_time();
  unsigned long flicker_end = flicker_start + random(50,800);

  unsigned long cur_time = millis();
 
  while(cur_time < tornado_start + 10000){
    cur_time = millis();
    
    if(cur_time >= flicker_start and on == true){
      both_write(1,0);
      on = false;
    }
    if(cur_time >= flicker_end and on == false){
      both_write(1,255);
      on = true;

      flicker_start = flicker_end + flicker_time();
      flicker_end = flicker_start + random(50,800);
    }
  }
}

void flicker(){
  both_write(1,0);
  delay(random(50,800));
  both_write(1,100);
  return;
}

void hurricane(){
  
  unsigned long rain_start = millis();

  unsigned long flicker_start= rain_start + flicker_time();

  // Whether it should be getting brighter or darker
  int sign = 1;

  int green = 50;

  both_write(1, 100);
  both_write(2, 0);
  both_write(3, green);
  both_write(4,200);

  while(millis() < rain_start + weather_duration){
    both_write(3,green);
    green = green + sign;

    if(green > 150){
      sign = -1;
    } else if (green < 10){
      sign = 1;
    }

    // If it is time for lightning
    if(millis() >= flicker_start){
      // Trigger the lightning flash
      flicker();

      // Continue the cycle
      both_write(1, 100);
      both_write(2, 0);
      both_write(3, green);
      both_write(4,200);

      // Find the next lightning bolt
      flicker_start = millis() + flicker_time();
    }

    delay(10);
  }

  both_write(1,255);
}


void loop() {
  if(Serial.available()){         //From RPi to Arduino
    int r = 1;
    r = r * (Serial.read() - '0');  //conveting the value of chars to integer
    switch(r){
      case 1:
        sunny();
        break;
      case 2:
        rainbow();
        break;
      case 3:
        rain();
        break;
      case 4:
        snow();
        break;
      case 5:
        hurricane();
        break;
      case 6:
        tornado();
        break;
    }
  }
  else{
    //Night
    both_write(1,255);
    both_write(2,5);
    both_write(3,2);
    both_write(4,0);
  }
}

