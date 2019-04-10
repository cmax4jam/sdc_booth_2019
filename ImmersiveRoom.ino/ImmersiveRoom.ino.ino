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
}

void both_write(int chan, int val){
  DmxSimple.write(chan, val);
  DmxSimple.write(chan + 4, val);
}

void calm(){
  int blue_base = 50;
  int red_base = 10;

  // Turn off the green
  both_write(3, 0);

  both_write(4, blue_base);

  unsigned long start = millis();

  unsigned long end_time = start + 20000;

  int sign = 1;

  while(millis() > end_time){
    red_base = red_base + sign;

    if(red_base > 40){
      sign = -1;
    } else if(red_base < 10){
      sign = 1;
    }

    delay(5);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  calm();
}
