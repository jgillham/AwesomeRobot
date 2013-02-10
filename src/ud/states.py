"""
Module Tests:
"""

class Base:
    """
    Class Tests:
    >>> instance = Base()
    """
    def onIRReadingReceived( pos, IRlsb, IRmsb, USlsb, USmsb, eyeNum ):
		pass
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
