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
serArd1 = serial.Serial('/dev/ttyUSB0', 9600)
serArd2 = serial.Serial('/dev/ttyUSB1', 9600)
    

def main():
    #time.sleep(2)
    subprocess.call(COMMAND_DICT["sun"], cwd='videos/')

    COMMAND_DICT = {"sun":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '&'], 
                     "rain":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '&'],
                     "snow":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '&'],
                     "tornado":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '&'],
                     "hurricane":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '&'],
                     "rainbow":['omxplayer', '-o', 'local', '--no-keys', 'INSERTVIDEOFILE', '&'],
                     "bottom-layer"}
    while True:
        if ser.in_waiting > 0 and BUTTON PRESSED:
            
            #Arduinos constantly send data, captured all at once with big "submit" button from raspi
            if SUN CONDITIONS:
                subprocess.call(COMMAND_DICT["sun"], cwd='videos/')
            elif RAIN CONDITIONS:
                subprocess.call(COMMAND_DICT["rain"], cwd='videos/')
            elif HURRICANE CONDITIONS:
                subprocess.call(COMMAND_DICT["hurricane"], cwd='videos/')
            elif TORNADO CONDITIONS:
                subprocess.call(COMMAND_DICT["tornado"], cwd='videos/')
            elif SNOW CONDITIONS:
                subprocess.call(COMMAND_DICT["snow"], cwd='videos/')
            elif RAINBOW CONDITIONS:
                subprocess.call(COMMAND_DICT["rainbow"], cwd='videos/')



if __name__ == '__main__': main()