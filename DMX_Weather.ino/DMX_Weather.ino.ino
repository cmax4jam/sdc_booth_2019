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

unsigned long lightning_duration = 50;

void setup() {
  /* The most common pin for DMX output is pin 3, which DmxSimple
  ** uses by default. If you need to change that, do it here. */
  DmxSimple.usePin(2);
  Serial.begin(9600);

  /* DMX devices typically need to receive a complete set of channels
  ** even if you only need to adjust the first channel. You can
  ** easily change the number of channels sent here. If you don't
  ** do this, DmxSimple will set the maximum channel number to the
  ** highest channel you DmxSimple.write() to. */
  DmxSimple.maxChannel(256);

  storm();
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

void storm(){
  storm_start = millis();

  // The storms last 10 seconds
  unsigned long storm_end = storm_start + 10000;

  // The time in milliseconds to start the flash
  // Not the duration but the actual time
  unsigned long lightning_start;

  // The time in milliseconds to stop the flash
  unsigned long lightning_stop;

  // If there is currently a flash going on
  boolean lightning_on = false;

  DmxSimple.write(1,0);
  DmxSimple.write(2, 255); //R
  DmxSimple.write(3, 255); //G
  DmxSimple.write(4, 155); //B

  lightning_start = storm_start + lightning_time();
  lightning_stop = lightning_start + lightning_duration;

  while(true){
    unsigned long cur_time = millis();

    /*
     * If we've passed the end of the storm stop triggering
     * lightning
     */
    if(cur_time >= storm_end){
      return;
    }

    // If it is time to start the lightning strike
    if(cur_time >= lightning_start and  !lightning_on){
      DmxSimple.write(1,255);
      lightning_on = true;
    }


    // Flicker off after 3 milliseconds
    if(cur_time - lightning_start >= 16 & cur_time - lightning_start < 32){
      DmxSimple.write(1,0);
    }

    if(cur_time - lightning_start >= 32 & cur_time - lightning_start < 50){
      DmxSimple.write(1,255);
    }

    // If it is time to turn off the lightning strike
    if(cur_time >= lightning_stop and lightning_on){
      DmxSimple.write(1,0);
      lightning_on = false;

      // Find the time of the next lightning bolt
      lightning_start = lightning_start + lightning_time();
      lightning_stop = lightning_start + lightning_duration;
    }
  }

  storm();
}


void loop() {
  
}

