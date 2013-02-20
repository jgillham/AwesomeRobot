"""
Module Tests:
"""

class IMO:
    """
    Provides input/output to the IMO sensor.
    Examples:
        >>> instance = IMO()
    """
    pass

class Camera:
    """
    Examples:
        >>> instance = Camera()
    """
    pass
def parseIMUReading( line ):
    """
    Examples:
        >>> parseIMUReading( "#YPR=18,70,134" )
        (4,2,5)
    """
    import math
    line = line[5:]   # Delete "#YPR="
    ypr = line.split( "," )    # Fields split
    print ypr
    if not len( ypr ) == 3:
        raise Exception( "Bad text." )
    yaw = float(ypr[0])*math.pi/180.0
    pitch = -float(ypr[1])*math.pi/180.0
    roll = -float(ypr[2])*math.pi/180.0
    return yaw, pitch, roll 
