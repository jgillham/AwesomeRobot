'''
Created on 2011-12-02

@author: Bobby Wood
'''

## import the serial library
import serial


## Boolean variable that will represent 
## whether or not the arduino is connected
connected = False

## open the serial port that your ardiono 
## is connected to.
ser = serial.Serial("/dev/ttyACM0", 115200)

## loop until the arduino tells us it is ready
while not connected:
    serin = ser.read()
    connected = True

## Tell the arduino to blink!

x=0
z=0
while 1:
    x=ser.read()
    
    if (x!=0):
       y= ser.read()
       while (y==0):
            y= ser.read()
       z = (ord(x)*255 + ord(y))
       print (z, ord(x), ord(y))
       print ("::")
    
## close the port and end the program
ser.close()
