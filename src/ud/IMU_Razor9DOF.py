import serial
import string
import math
from time import time
grad2rad = 3.141592/180.0
# IMU COM PORT
ser = serial.Serial(port='COM7',baudrate=57600, timeout=1)
roll=0
pitch=0
yaw=0
while 1:
    line = ser.readline()
    line = line.replace("#YPR=","")   # Delete "#YPR="
    print line
    ypr = string.split(line,",")    # Fields split
    if len(ypr) > 2:
        try:
            yaw = float(ypr[0])*grad2rad
            pitch = -float(ypr[1])*grad2rad
            roll = -float(ypr[2])*grad2rad
        except:
            print "Invalid line"
ser.close

