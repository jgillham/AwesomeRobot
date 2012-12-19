'''
This program first makes contact with the arduino and then sends it message accrossd.
 We expect the arduino to return the same message.

@author: Josh Gillham
Created on 12-18-12
'''
## BEGIN Programmer settings. Please customize these according to your computer.
	# Port description:
PORT = "/dev/ttyACM0"
	# Message being sent through the port:
MESSAGE = "I love you!"
	# Maximum seconds to wait before the relationship fails.
SESSION_TIMEOUT = 5

## END Programmer settings.

	# This speed must match the code on the arduino.
SPEED = 9600


	# Required serial library.
import serial
	# Required to detect time out.
import time


	# Open the port to the arduino.
ser = serial.Serial( port = PORT, baudrate = SPEED)

	# Necessary initial values.
i = 0
byte = '+'
	# Start the timer now!
startTime = time.time()

	# Make contact.
	# Keep talking and listening until the Arduino
	#  answers with the same byte.
while byte == '+' and (time.time() - startTime) < SESSION_TIMEOUT:
	byte = 'H'
	ser.write( byte )
	print( "PC says: " + byte )
	byte = ser.read() 
	print( "Android says Hello: " + byte )
	i = i + 1

	# Clear extra input and output in the buffers.
print( "Made contact!" )
ser.flushInput()
ser.flushOutput()

	# Talk to arduino.
ser.write( MESSAGE )
print( "PC says: " + MESSAGE )


	# Listen to arduino.
while (time.time() - startTime) < SESSION_TIMEOUT:
	if ser.inWaiting() > 0:
		byte = ser.read()
		print( "Android says Hello: " + byte )
    
	# close the port and end the program
ser.close()
