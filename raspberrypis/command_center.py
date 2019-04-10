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


import subprocess, serial, time
ser = serial.Serial('/dev/ttyUSB0', 9600)
#serArd2 = serial.Serial('/dev/ttyUSB1', 9600)
    

def main():
    #time.sleep(2)
    subprocess.call(COMMAND_DICT["bottom-layer"], cwd='videos/')

    COMMAND_DICT = {"sun":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '--layer', '5', '&'], 
                     "rain":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '--layer', '5', '&'],
                     "snow":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '--layer', '5', '&'],
                     "tornado":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '--layer', '5', '&'],
                     "hurricane":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '--layer', '5', '&'],
                     "rainbow":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '--layer', '5', '&'],
                     "bottom-layer":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '--layer', '1', '--loop','&']}
    while True:
        if ser.in_waiting > 0 and BUTTON PRESSED:    ###FIX THIS
            line = ser.readline()
            #Arduinos constantly send data, captured all at once with big "submit" button from raspi
            if line == "Sun":
                subprocess.call(COMMAND_DICT["sun"], cwd='videos/')
            elif line == "Rain":
                subprocess.call(COMMAND_DICT["rain"], cwd='videos/')
            elif line == "Hurricane":
                subprocess.call(COMMAND_DICT["hurricane"], cwd='videos/')
            elif line == "Tornado":
                subprocess.call(COMMAND_DICT["tornado"], cwd='videos/')
            elif line == "Snow":
                subprocess.call(COMMAND_DICT["snow"], cwd='videos/')
            elif line == "Rainbow":
                subprocess.call(COMMAND_DICT["rainbow"], cwd='videos/')



if __name__ == '__main__': main()