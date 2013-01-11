"""
This program sends messages to the arduino using a FIFO scheme. Each message
 has an unique id tag. The program sends the first item on the deque and waits
 for the confirmation.  When the program matches the ID tag, it removes the
 first message from the deque.

The program builds on the first example to show how to handle long waits for the
 confirmations, dropped data, or damaged data. The message is sent then resent
 every so often while the confirmation is not received. This system will ensure
 the integrity of the data transfered.

@author Josh Gillham
@version 12-20-12
"""


## BEGIN Programmer settings. Please customize these according to your computer.

                        # Port description:
PORT = "/dev/ttyACM0"
                        # Message being sent through the port:
MESSAGE = "I love you!"
                        # Maximum seconds to wait before the relationship fails.
SESSION_TIMEOUT = 40
                        # This speed must match the code on the arduino.
SPEED = 115200
                        # Total messages to send.
TOTAL_MESSAGES = 30

## END Programmer settings.

                    # Required communication library.
import serial
                    # Required to detect time out.
import time
                    # Required for deque.
import collections

"""
Makes a lambda function which returns true while their is time remaining.

@param seconds is the number seconds to return true.

@return a lambda function thats true while for number of seconds.
Tests:
>>>makeTimer( 1 )()
True
"""
def makeTimer( seconds ):
  startTime = time.time()
  return lambda : time.time() - startTime < seconds

def alwaysFalse( ):
  return lambda : False

# Load up the outBox with messages.
outBox = collections.deque( )
i = 0
while i < TOTAL_MESSAGES:
	outBox.append( ":D" + str(i) + ";" )
	i = i + 1

# Start the timer now!
startTime = time.time()
sessionTimer = makeTimer( SESSION_TIMEOUT )

# Open the port to the arduino.
ser = serial.Serial( port = PORT, baudrate = SPEED)

# Avoid race condition
time.sleep(2)
                    # Necessary initial value.
byte = '+'
                    # What the PC sends and expects back.
pcByte = 'H'
                    # Wait 100 ms seconds while reading
ser.timeout = 0.1


# Make contact.
# Keep talking and listening until the Arduino
#  answers with the same byte.
while byte != pcByte and sessionTimer():
	ser.write( pcByte )
	print( "PC says: " + pcByte )
	byte = ser.read()
	print( "Arduino says: " + byte )
print( "Made contact!" )
connectedTime = time.time()

# Clear extra input and output in the buffers.
ser.flushInput()
ser.flushOutput()

# Necessary initial values
foundMessage = 0
inMessage = ""
badConfirmations = 0
messagesSent = 0
confirmationsReceived = 0
hasSentMessage = 0
cu = 0
                                    # Timer should return false the first time.
resendMessageTimer = alwaysFalse( )

# Send one message and receive the confirmation for each message.
while len( outBox ) > 0 and sessionTimer():
	# Send a limited number of duplicate messages.
	if resendMessageTimer() == False:
		print( "PC sends: " + outBox[0] )
		ser.write( outBox[0] )
		messagesSent = messagesSent + 1
		hasSentMessage = 1
                                          # Resend messages every 1/10th of a second.
		resendMessageTimer = makeTimer( 0.1 )
  # Check for bytes in the read buffer.
	while ser.inWaiting() > 0:
		byte = ser.read()
		# The start of the message.
		if byte == ':':
			foundMessage = 1
			inMessage = ""
		# The end of the message.
		elif byte == ';':
			if len(inMessage) > 0:
				confirmationNumber = inMessage[1:]
				# Compare the numeric parts of the strings.
				if len( outBox ) > 0 and confirmationNumber == (outBox[0])[2:-1]:
					outBox.popleft()
					print( "Confirmation#" + confirmationNumber + " received." )
					hasSentMessage = 0
					confirmationsReceived = confirmationsReceived + 1
					resendMessageTimer = alwaysFalse( )
				else:
					badConfirmations = badConfirmations + 1
			foundMessage = 0
			inMessage = ""
		# Append all other characters.
		else:
			if foundMessage:
				inMessage = inMessage + byte
# Calculate times.
totalTime = time.time() - startTime
portConnectionTime = connectedTime - startTime
messageRelayTime = totalTime - portConnectionTime
# Print report.
print( "-------------------------------------------------------" )
print( "Port Connect Time: " + str( portConnectionTime ) )
print( "Message Relay Time: " + str( messageRelayTime ) )
print( "Total Time: " + str( totalTime ) )
print( "Messages Sent: " + str( messagesSent ) )
print( "Bad Confirmations: " + str( badConfirmations ) )
print( "Confirmations Received: " + str( confirmationsReceived ) )
