#       command_center.py     #
# SDC BOOTH 2019 - ATMOSPHERE #
# most be located in directory that also has videos folder

# WEATHER CONDITIONS (OUTPUT)
#   - SUN                    
#   - RAIN                   
#   - TORNADO                
#   - HURRICANE              
#   - SNOW
#   - RAINBOW

# WEATHER VARIABLES (INPUT)
#   - TIME OF DAY (DAY, NIGHT)
#   - WIND (HIGH, LOW)
#   - RAIN (NONE, LIGHT, HEAVY)
#   - TEMP (COLD, HOT)

# This Raspberry Pi controls input coming in from two control board Arduino Unos
# NEUTRAL STATE = SUN 


import subprocess, serial, time, os
serIn = serial.Serial('/dev/ttyACM2', 9600)
serOut = serial.Serial('/dev/ttyAMA0', 9600)
#serArd2 = serial.Serial('/dev/ttyUSB1', 9600)

import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library
GPIO.setwarnings(False) # Ignore warning for now
GPIO.setmode(GPIO.BCM) # Use physical pin numbering
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
    

def main():
    #time.sleep(2)
    COMMAND_DICT = {"sun":['omxplayer', '-o', 'local', '--no-keys', 'sun.mp4', '--layer', '5', '&'], 
                     "rain":['omxplayer', '-o', 'local', '--no-keys', 'rain.mp4', '--layer', '5', '&'],
                     "snow":['omxplayer', '-o', 'local', '--no-keys', 'snow.mp4', '--layer', '5', '&'],
                     "tornado":['omxplayer', '-o', 'local', '--no-keys', 'tornado.mp4', '--layer', '5', '&'],
                     "hurricane":['omxplayer', '-o', 'local', '--no-keys', 'hurricane.mp4', '--layer', '5', '&'],
                     "rainbow":['omxplayer', '-o', 'local', '--no-keys', 'rainbow.mp4', '--layer', '5', '&'],
                    #  "night":['omxplayer', '-o', 'local', '--no-keys', 'night.mp4', '--layer', '5', '&'],
                     "bottom-layer":['omxplayer', '-o', 'local', '--no-keys', 'blackbackground.mp4', '--layer', '1', '--loop', '&']}
    

    # Call initialize background layer to hide screen
    #subprocess.Popen(COMMAND_DICT["bottom-layer"], cwd='/home/pi/Desktop/booth2019_atmos/videos/')
    #os.system('omxplayer --no-keys -o local --layer 1 --loop /home/pi/Desktop/booth2019_atmos/videos/blackbackground.mp4 &')
    os.system('pqiv -i --fullscreen /home/pi/Desktop/booth2019_atmos/videos/black.jpg &')

    
    while True:  # constantly check if button pressed and serial input waiting
 
        if serIn.in_waiting > 0 and GPIO.input(23) == GPIO.HIGH:    ###Check if button pushed and serial input in waiting
            line = serIn.readline()
            print(line)
            #Arduinos constantly send data, captured all at once with big "submit" button from raspi
            if "Sun" in line:
                serIn.write(b'1')
                omxplayer = subprocess.Popen(COMMAND_DICT["sun"], cwd='/home/pi/Desktop/booth2019_atmos/videos/')
                time.sleep(10)
                omxplayer.terminate()
                os.system('sudo killall omxplayer.bin')
            elif "Rainbow" in line:
                omxplayer = subprocess.Popen(COMMAND_DICT["rainbow"], cwd='/home/pi/Desktop/booth2019_atmos/videos/')
                serIn.write(b'2')
                time.sleep(10)
                omxplayer.terminate()
                os.system('sudo killall omxplayer.bin')
            elif "Rain" in line:
                omxplayer = subprocess.Popen(COMMAND_DICT["rain"], cwd= '/home/pi/Desktop/booth2019_atmos/videos/')
                serIn.write(b'3')
                time.sleep(10)
                omxplayer.terminate()
                os.system('sudo killall omxplayer.bin')
            elif "Snow" in line:
                #pid = os.system('omxplayer --no-keys -o local --layer 5 /home/pi/Desktop/booth2019_atmos/videos/snow.mp4 &')
                #print(pid)
                omxplayer = subprocess.Popen(COMMAND_DICT["snow"], cwd='/home/pi/Desktop/booth2019_atmos/videos/', stdin=subprocess.PIPE)
                serIn.write(b'4')
                time.sleep(10)
                omxplayer.terminate()
                os.system('sudo killall omxplayer.bin')
            elif "Hurricane" in line:
                omxplayer = subprocess.Popen(COMMAND_DICT["hurricane"], cwd='/home/pi/Desktop/booth2019_atmos/videos/')
                serIn.write(b'5')
                time.sleep(10)
                omxplayer.terminate()
                os.system('sudo killall omxplayer.bin')
            elif "Tornado" in line:
                omxplayer = subprocess.Popen(COMMAND_DICT["tornado"], cwd='/home/pi/Desktop/booth2019_atmos/videos/')
                serIn.write(b'6')
                time.sleep(10)
                omxplayer.terminate()
                os.system('sudo killall omxplayer.bin')
            # elif "Night" in line
            #     omxplayer = subprocess.Popen(COMMAND_DICT["night"], cwd='/home/pi/Desktop/booth2019_atmos/videos/')
            #     serIn.write(b'6')
            #     time.sleep(10)
            #     omxplayer.terminate()
            #     os.system('sudo killall omxplayer.bin')
        
            



if __name__ == '__main__': main()
