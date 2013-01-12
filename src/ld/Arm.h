#ifndef ARM_CLASS_INCLUDED
#define ARM_CLASS_INCLUDED

#include <Servo.h>
#define ARM_SERVOS 3
#define ARM_DELTA
#define ARM_SERVO_ID1  5
#define ARM_SERVO_ID2  6
#define ARM_SERVO_ID3  10

class Arm {
  private:
    int newTheta[ARM_SERVOS];
    int oldTheta[ARM_SERVOS];
    Servo R[ARM_SERVOS]
  public:
    Arm( ): newTheta( {0,0,0} ), oldTheta( {0,0,0} ), delta( {0,0,0} ) {
        R[0].attach(ARM_SERVO_ID1);
        R[1].attach(ARM_SERVO_ID2);
        R[2].attach(ARM_SERVO_ID3);
    }
    void setNewTheta( int num, int val ) {
        newTheta[ num ] = val;
    }
    void moveAll() {
        for( int i = 0; i < ARM_SERVOS; ++i ) {
            if ( newTheta[ i ] != oldTheta[ i ] ) {

            }
        }
    }

};


#endif // ARM_CLASS_INCLUDED

