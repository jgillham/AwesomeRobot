#ifndef ARM_CLASS_INCLUDED
#define ARM_CLASS_INCLUDED

#include "ArmDriver.h"

#define ABS( X ) ( (X) < 0? (-X) : (X)  )


class Arm {
  public:
    int newTheta[ARM_SERVOS];
    int oldTheta[ARM_SERVOS];
    int delay[ARM_SERVOS];
    int startTime;
    //XXX needs to be singleton.
    Arm( );
    void setNewTheta( int newTheta[ARM_SERVOS], int time );
    void moveAll( int time );

};


#endif // ARM_CLASS_INCLUDED

