import RPi.GPIO as GPIO
import time, sys

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.IN, pull_up_down = GPIO.PUD_UP) # setup on counter pin 18

global count
count = 0

def countPulse(channel):
   global count
   count = count+1
   #print count

GPIO.add_event_detect(18, GPIO.FALLING, callback=countPulse) # add event to monitor pin 18

while True:
    try:
        time.sleep(10)
	print count
	count = 0
    except KeyboardInterrupt:
        print '\ncaught keyboard interrupt!, bye'
        GPIO.cleanup()
        sys.exit()
