import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 9600)
ser.flushInput()
state=ser.read(16)
print( "%s\n" % (state) )
ser.close()
