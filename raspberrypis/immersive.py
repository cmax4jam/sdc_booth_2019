import RPi.GPIO as GPIO
import time
import serial
import random
import os

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

# Configure the GPIO pins
GPIO.setup(17, GPIO.OUT)
GPIO.setup(18, GPIO.OUT)
GPIO.setup(27, GPIO.OUT)
GPIO.setup(22, GPIO.OUT)
GPIO.setup(23, GPIO.OUT)
GPIO.setup(24, GPIO.OUT)
GPIO.setup(25, GPIO.OUT)
GPIO.setup(4, GPIO.OUT)

# Which pins map to which outlet
pins = [17,18,27,22,23,24,25,4]

ser = serial.Serial("/dev/ttyACM0",9600)
ser.baudrate=9600

# Loop infinitely
while(True):
  for pin in pins:
    GPIO.output(pin, GPIO.HIGH)

  # Trigger arduino
  ser.write('c')
  
  # Flicker stars
  for i in range(20):

    flicker = random.randint(0,7)  
    

    GPIO.output(pins[flicker], GPIO.LOW)
    
    time.sleep(1)
    
    GPIO.output(pins[flicker], GPIO.HIGH)
    
  for pin in pins:
    GPIO.output(pin, GPIO.LOW)

  
  ser.write('s')  
  os.system('omxplayer --no-keys -o local /home/pi/atmosphere/20secThunder.wav')
