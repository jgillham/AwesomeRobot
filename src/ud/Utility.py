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

class Messenger:
    """
    Facilitates communication accrossed the serial port to the Arduino.

    Class Tests:
    >>> instance = Messenger()
    """
    pass

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
        ser.timeout = 0.1

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

    def readByteIfAvailiable( self ):
        """
        Reads a byte if there is one waiting in the buffer.

        Returns:
            The byte -- If one is availiable.
            False -- If the buffer is empty.

        Examples:
            >>> import serial
            >>> try:
            ...     with SerialPort() as instance:
            ...         instance.readByteIfAvailiable()
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
