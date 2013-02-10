"""
Provides utility to the Robot brain.
Module Tests:
"""

class Map:
    """
    Provides waypoints and other map data.

    Class Tests:
    >>> instance = Map()
    """
    pass

class DataManager:
	"""
    Provides waypoints and other map data.

    Class Tests:
    >>> instance = DataManager()
    """
	pass

class Reading:
    # Static field
	IR_maxRange = 5
	def __init__(self, eyeNum, pos, IR_raw, US_raw):
		self.pos = pos
		self.eyeNum = eyeNum
		self.IR_raw = IR_raw
		self.US_raw = US_raw
		if self.IR_raw != 0:
			self.IR_feet =  (2525.0*pow(IR_raw, - 0.85) - 4)/12
		else:
			self.IR_feet = 0
		self.IR_feet = min(self.IR_feet, self.IR_maxRange)
		self.US_feet = US_raw * 0.1

	def __init__( self, message ):
	    if len( message ) < 6
            raise Exception( "Message is too small" )
        else:
            pos = ord( message[0] )
            IRlsb = ord( message[1] )
            IRmsb = ord( message[2] )
            USlsb = ord( message[3] )
            USmsb = ord( message[4] )
            eyeNum = ord( message[5] )

            IR = IRmsb * 255 + IRlsb
            US = USmsb * 255 + USlsb

            self( eyeNum, pos, IR, US )

class Messenger:
    """
    Facilitates communication accrossed the serial port to the Arduino.

    Class Tests:
    >>> instance = Messenger()
    """
    def __init__( self, serialWrapper ):
        self.__responseHandler = 0
        self.__buffer = ""
        self.__inBox = []
        self.__inMessage = False
        self.__serialWrapper = serialWrapper
    def setResponseHandler( self, stateObject ):
        self.__responseHandler = stateObject
    def checkInBox( self ):
        """
        Reads the bytes coming into the serial port while the buffer
         is full.
        @return True when a full message is received or False otherwise.
        """
		while True:
			# Read input and received chars.
			byte = serialWrapper.read()
			if byte == False:
				return False
			else:
				if byte == ':':
					self.__inMessage = True
				else if byte == ';':
				    self.__inMessage = False
				    if len( self.__buffer ) > 0:
				        self.__message = self.__buffer
				        self.__buffer = ""
				        return True
				else if self.__inMessage:
					self.__buffer = self.__buffer + message
    def getMessage( self ):
        return copy.copy( self.__message )
    def decodeIRMessage( self ):
        if len( self.__message ) == 0:
            return False
        else:
            pos = ord( self.__message[0] )
            IRlsb = ord( self.__message[1] )
            IRmsb = ord( self.__message[2] )
            USlsb = ord( self.__message[3] )
            USmsb = ord( self.__message[4] )
            eyeNum = ord( self.__message[5] )

            IR = IRmsb * 255 + IRlsb
            US = USmsb * 255 + USlsb

            return reading( eyeNum, pos, IR, US )


class SerialPort:
    """
    Isolates the Python serial library of choose from other components of the brain and provides
     easier testing.

    Preconditions:
        >>> import serial
        >>> import settings
    """
    import settings

    def __exit__( self, type, value, traceback ):
        """
        Deconstructor. Called automatically with the "with" statement.

        Example:
            >>> import serial
            >>> try:
            ...     with SerialPort() as t:
            ...         pass
            ... except serial.SerialException:
            ...     raise NameError( "This example requires an arduino plugged in and the correct port address." )
        """
        if not isinstance(value, TypeError):
            self.__ser.close()

    def __init__( self, port = settings.SERIAL_PORT_ADDRESS ):
        """
        Initializes the class by setting local variables and opening the port.

        Throws:
            SerialException -- When the port fails to open.

        Examples:
            >>> import serial
            >>> try:
            ...     SerialPort( port = "/dev/fooBar" )
            ... except serial.SerialException as e:
            ...     print e
            could not open port /dev/fooBar: [Errno 2] No such file or directory: '/dev/fooBar'
            >>> try:
            ...     with instanceOfSerialPort = SerialPort():
            ... except serial.SerialException:
            ...     raise NameError( "This example requires an arduino plugged in and the correct port address." )
        """
        import serial
        import settings
        self.__ser = serial.Serial( port = port, baudrate = settings.SERIAL_PORT_SPEED )
        # Wait 100 ms while reading.
        #ser.timeout = 0.1

    def makeContact( self, timeout = settings.SERIAL_PORT_SESSION_TIMEOUT ):
        """
        Makes contact with the Arduino chip. After a certain time, the method
         failes.

        Parameters:
            timeout -- How long to wait before failing.

        Returns:
            True -- If contact was made sucessfully.
            False -- If contact failed.

        Examples:
            >>> import serial
            >>> try:
            ...     with SerialPort() as instance:
            ...         instance.makeContact()
            ... except serial.SerialException:
            ...     raise NameError( "This example requires an arduino plugged in and the correct port address." )
            True
        """
        sessionTimer = support.makeTimer( timeout )
        byte = 0
        while byte != settings.SERIAL_PORT_HELLO_BYTE:
            if not sessionTimer():
                return False
            ser.write( settings.SERIAL_PORT_HELLO_BYTE )
            print( "PC says: " + pcByte )
            byte = ser.read()
            print( "Arduino says: " + byte )
        # Clear extra input and output in the buffers.
        ser.flushInput()
        ser.flushOutput()
        return True

    def read( self ):
        """
        Reads a byte if there is one waiting in the buffer.

        Returns:
            The byte -- If one is availiable.
            False -- If the buffer is empty.

        Examples:
            >>> import serial
            >>> try:
            ...     with SerialPort() as instance:
            ...         instance.read()
            ... except serial.SerialException as e:
            ...     raise NameError( "This example requires an arduino plugged in and the correct port address." )

        """
        return ser.read()

    def read( self ):
        """
        Reads a byte if there is one waiting in the buffer.

        Returns:
            The byte -- If one is availiable.
            False -- If the buffer is empty.

        Examples:
            >>> import serial
            >>> try:
            ...     with SerialPort() as instance:
            ...         instance.read()
            ... except serial.SerialException as e:
            ...     raise NameError( "This example requires an arduino plugged in and the correct port address." )

        """
        if self.__ser.inWaiting() > 0:
            return ser.read()
        else:
            return False

    def close( self ):
        """
            Closes the serial port connection.

            Examples:
                >>> import serial
                >>> try:
                ...     connection = SerialPort()
                ... except:
                ...     raise NameError( "This example requires an arduino plugged in and the correct port address." )
                ... else:
                ...     connection.close()
        """
        self.__ser.close()

    def write( self, serializable ):
        """
        Writes a object that can be converted to a string to the serial port.
        Examples:
            >>> import serial
            >>> try:
            ...     with SerialPort() as instance:
            ...         instance.write( 'a' )
            ... except serial.SerialException:
            ...     raise NameError( "This example requires an arduino plugged in and the correct port address." )
        """
        self.__ser.write( str( serializable ) )
