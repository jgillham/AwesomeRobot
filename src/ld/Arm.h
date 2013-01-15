#ifndef ARM_CLASS_INCLUDED
#define ARM_CLASS_INCLUDED

#include "ArmDriver.h"

#define ABS( X ) ( (X) < 0? (-X) : (X)  )


class Arm {
  public:
    unsigned int newTheta[ARM_SERVOS];
    unsigned int oldTheta[ARM_SERVOS];
    unsigned int delay[ARM_SERVOS];
    unsigned int startTime;
    //XXX needs to be singleton.
    Arm( );
    void setNewTheta( unsigned int newTheta[ARM_SERVOS], unsigned int time );
    void moveAll( unsigned int time );
    bool inMove();

};


#endif // ARM_CLASS_INCLUDED

