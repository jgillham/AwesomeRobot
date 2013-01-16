#ifndef ARM_CLASS_INCLUDED
#define ARM_CLASS_INCLUDED

#include "Settings.h"
#include "ArmDriver.h"

class Arm {
  public:
    Number newTheta[ARM_SERVOS];
    Number currentTheta[ARM_SERVOS];
    Number oldTheta[ARM_SERVOS];
    Number delay[ARM_SERVOS];
    bool inProgress[ARM_SERVOS];
    int startTime;
    //XXX needs to be singleton.
    Arm( Number initThetas[ARM_SERVOS] );
    void setNewTheta(int time, Number newTheta[ARM_SERVOS] );
    //void moveAll( int time );
    bool move( int index, int time, Number* outNextTheta );
    bool inMove();

};


#endif // ARM_CLASS_INCLUDED

