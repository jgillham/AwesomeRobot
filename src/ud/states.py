"""
Module Tests:
"""

class Mode:
	"""
	Class Tests:
	>>> instance = Base()
	"""
	def onMessageReceived( self, message ):
		category = message[0]
		if category == settings.SERVICE_IRSENSOR_POLL:
			self.onIRReadingReceived( utility.Reading( message ) )
	def onIRReadingReceived( self, reading ):
		pass

class Go( Base ):
    """
    Class Tests:
    >>> instance = Go()
    >>> isinstance( instance, Base )
    True
    """
    pass

class Localize( Base ):
    """
    Class Tests:
    >>> instance = Localize()
    >>> isinstance( instance, Base )
    True
    """
    pass


class Grab( Base ):
    """
    Class Tests:
    >>> instance = Grab()
    >>> isinstance( instance, Base )
    True
    """
    pass

mode = Mode()
messenger = Messenger( utility.SerialPort() )
while True:
    if messenger.checkInBox():
        mode.onMessageReceived( messenger.getMessage() )
