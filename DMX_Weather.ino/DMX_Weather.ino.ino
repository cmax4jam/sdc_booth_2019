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

unsigned long lightning_duration = 100;

// How long each weather effect lasts
// 10 seconds
unsigned long weather_duration = 10000;

void setup() {
  /* The most common pin for DMX output is pin 3, which DmxSimple
  ** uses by default. If you need to change that, do it here. */
  DmxSimple.usePin(2);

  /* DMX devices typically need to receive a complete set of channels
  ** even if you only need to adjust the first channel. You can
  ** easily change the number of channels sent here. If you don't
  ** do this, DmxSimple will set the maximum channel number to the
  ** highest channel you DmxSimple.write() to. */
  DmxSimple.maxChannel(256);

  rain();
}

void allOff(){
  DmxSimple.write(1,0);
}

/*
 * Returns the number of milliseconds to wait before triggering the next lightning strike
 */
long lightning_time(){
  return random(450,3000);
}


void lightning(){

  DmxSimple.write(1,0);
  DmxSimple.write(2, 255); //R
  DmxSimple.write(3, 255); //G
  DmxSimple.write(4, 155); //B

  delay(100);

  // If it is time to start the lightning strike
  DmxSimple.write(1,128);

  delay(lightning_duration/3);
  DmxSimple.write(1,0);
  

  delay(lightning_duration/3);
  
  DmxSimple.write(1,128);

  delay(lightning_duration/3 + 50);

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

  int green = 50;

  DmxSimple.write(1, 100);
  DmxSimple.write(2, 0);
  DmxSimple.write(3, green);
  DmxSimple.write(4,200);

  while(millis() < rain_start + weather_duration){
    DmxSimple.write(3,green);
    green = green + sign;

    if(green > 100){
      sign = -1;
    } else if (green < 10){
      sign = 1;
    }

    // If it is time for lightning
    if(millis() >= lightning_start){
      // Trigger the lightning flash
      lightning();

      // Continue the cycle
      DmxSimple.write(1, 100);
      DmxSimple.write(2, 0);
      DmxSimple.write(3, green);
      DmxSimple.write(4,200);

      // Find the next lightning bolt
      lightning_start = millis() + lightning_time();
    }

    delay(30);
  }

  DmxSimple.write(1,255);
}


void loop() {
  
}

