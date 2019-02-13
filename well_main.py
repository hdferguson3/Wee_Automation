# Well Automation Project - 12/28/2018
#
# Doug Ferguson (https://github.com/hdferguson3/Well_Automation.git) 
#
# Read pulse count water flow meters, pressure, and pump cycle
# Publish results to OLED and mySQL database

import time
import datetime
import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306
import mysql.connector
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
import subprocess
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_UP) # configure pin 23 as meter 1 input

global m1_count
m1_count=0

def counter_1(channel):
   global m1_count
   m1_count = m1_count+1 # increment counter

j=0 # initialize db write increment

# Raspberry Pi pin configuration:
RST = None     # on the PiOLED this pin isnt used
# Note the following are only used with SPI:
DC = 23
SPI_PORT = 0
SPI_DEVICE = 0

# 128x32 display with hardware I2C:
#disp = Adafruit_SSD1306.SSD1306_128_32(rst=RST)

# 128x64 display with hardware I2C:
disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST)

# Initialize library.
disp.begin()

# Clear display.
disp.clear()
disp.display()

# Create blank image for drawing.
# Make sure to create image with mode '1' for 1-bit color.
width = disp.width
height = disp.height
image = Image.new('1', (width, height))

# Get drawing object to draw on image.
draw = ImageDraw.Draw(image)

# Draw a black filled box to clear the image.
draw.rectangle((0,0,width,height), outline=0, fill=0)

# Draw some shapes.
# First define some constants to allow easy resizing of shapes.
padding = -2
top = padding
bottom = height-padding
# Move left to right keeping track of the current x position for drawing shapes.
x = 0

# Load default font.
font = ImageFont.load_default()

# Add interupts events

GPIO.add_event_detect(23, GPIO.FALLING, callback=counter_1, bouncetime=1)

#########################################################################################
#											#
#			Main Loop							#
#											#
#########################################################################################

while True:
    try:
    	# Get IP address
	cmd = "hostname -I | cut -d\' \' -f1"
	IP = subprocess.check_output(cmd, shell = True)
	if IP and not IP.isspace():
		pass # pass IP string
	else:
		IP = "No IP address"

	# Get data from GPIO

    	state = "23.0,5.3,19.7,60.1,1"
    	data = state.split(",")
    	if data[4]==0:
		pump="OFF"
    	else:
		pump="ON"

    	# Fomrat timestamp
    	ts = time.time()
    	timestamp = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')

    	# Draw a black filled box to clear the image.
    	draw.rectangle((0,0,width,height), outline=0, fill=0)

    	# Write two lines of text.

    	draw.text((x, top),       "IP: " + str(IP), font=font, fill=255)
	draw.text((x, top+8),     str(timestamp),  font=font, fill=255)
    	draw.text((x, top+16),    "Meter 1:" + str(data[0]), font=font, fill=255)
    	draw.text((x, top+25),    "Meter 2:" + str(data[1]),  font=font, fill=255)
    	draw.text((x, top+33),    "Meter 3:" + str(data[2]),  font=font, fill=255)
	draw.text((x, top+41),    "Pressure:" + str(data[3]), font=font, fill=255)
        draw.text((x, top+49),    "Pump:" + str(pump), font=font, fill=255)

    	# Display image.
    	disp.image(image)
    	disp.display()
    	time.sleep(1)

    	# Write data to database
    	if j == 3600:
		j = 0 # reinitialize j index

		# Open database connection
		mydb = mysql.connector.connect(
			host="localhost",
			user="pi",
			passwd="raspberry",
			database="welldb"
			)

		mycursor = mydb.cursor()

		sql = "INSERT INTO data (meter1,meter2,meter3,press1,pump1,timestamp) VALUES (%s, %s, %s, %s, %s, '%s')"% (data[0], data[1], data[2], data[3], data[4], timestamp)
		mycursor.execute(sql)
		print "%s\n"% (sql)
		mydb.commit()

		m1_count = 0 # reinitialize m1 counter
		continue

    	else:
		j += 1
		continue
    except KeyboardInterrupt:
	GPIO.cleanup()
    GPIO.cleanup()
