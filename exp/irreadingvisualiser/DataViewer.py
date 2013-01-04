from Tkinter import *
import time
import serial
import math

## Boolean variable that will represent 
## whether or not the arduino is connected
connected = False

## open the serial port that your ardiono 
## is connected to.
ser = serial.Serial("/dev/ttyACM18", 115200)

## loop until the arduino tells us it is ready
while not connected:
    serin = ser.read()
    connected = True



root = Tk()
root.title("Blobs")
root.resizable(0, 0)

frame = Frame(root, bd=5, relief=SUNKEN)
frame.pack()

canvas = Canvas(frame, width=480, height=480, bd=0, highlightthickness=0)
canvas.pack()

canvas.create_rectangle(0,0,480,480, fill="black")

lines = list()
#make a bunch of lines
for i in range (0,181):
	lines.append(canvas.create_line(0, 0, 0, 0, fill="green"))
root.update() # fix geometry

readout = list()
# main loop:
while 1:
	while (ser.read()!='a'):
		pass
	readout = list()	
	for i in range (0,3): # 0 = pos, 1 = IRlsb, 2 = IRmsb	
		x = ser.read()
		while (x==0):
			x = ser.read()
		readout.append(x)

	pos = ord(readout[0])
	IRlsb = ord(readout [1])
	IRmsb = ord(readout [2])

	#great!  Now we've read a set of data from the serial port!
	IR = IRmsb*255 + IRlsb
	if (IR!=0): IR = 2525*math.pow(IR, -0.850) - 5
	out = repr(IR) + " inches at " + repr(pos)
	print(out)
	IR_screen = IR * 480/96
	canvas.coords(lines[pos],0,pos,IR_screen,pos) 
#        time.sleep(0.1)
	root.update() # process events

