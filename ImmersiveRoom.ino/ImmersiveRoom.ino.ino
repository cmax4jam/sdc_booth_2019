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

  calm();
}

void both_write(int chan, int val){
  DmxSimple.write(chan, val);
  DmxSimple.write(chan + 4, val);
}

/*
 * Returns the number of milliseconds to wait before triggering the next lightning strike
 */
long lightning_time(){
  return random(450,3000);
}

void lightning(){

  unsigned long lightning_duration = 200;

  both_write(1,0);
  
  both_write(2, 255); //R
  both_write(3, 255); //G
  both_write(4, 255); //B

  delay(750);

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

  both_write(1,0);
  delay(2000);

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
  both_write(4,100);

  while(millis() < rain_start + 18000){
    both_write(3,red);
    red = red + sign;

    if(red > 30){
      sign = -1;
    } else if (red < 5){
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
      both_write(4,100);

      // Find the next lightning bolt
      lightning_start = millis() + lightning_time();
    }

    delay(20);
  }

  both_write(1,255);
}

void calm(){
  both_write(1,255);
  int blue_base = 50;
  int red_base = 0;

  // Turn off the green
  both_write(3, 0);

  both_write(4, blue_base);

  both_write(2, red_base);

  unsigned long start = millis();

  unsigned long end_time = start + 20000;

  int sign = 1;

  while(millis() < end_time){
//    red_base = red_base + sign;
//
//    both_write(2, red_base);

//    if(red_base > 5){
//      sign = -1;
//    } else if(red_base <= 0){
//      sign = 1;
//    }

    blue_base = blue_base + sign;

    both_write(4, blue_base);

    if(blue_base > 50){
      sign = -1;
    } else if(blue_base <= 20){
      sign = 1;
    }


    delay(100);
  }
}

void loop() {
  char incoming;
  
  if(Serial.available() > 0){
    incoming = Serial.read();

    if (incoming == 'c'){
      calm();
    } else if (incoming == 's'){
      rain();
    }

  }
}
