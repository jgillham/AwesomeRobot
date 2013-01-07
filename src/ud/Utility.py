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
    pass
