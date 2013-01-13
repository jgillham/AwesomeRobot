#ifndef ARM_CLASS_INCLUDED
#define ARM_CLASS_INCLUDED

#include <Servo.h>
#define ARM_SERVOS 3
#define ARM_DELTA
#define ARM_SERVO_ID1  5
#define ARM_SERVO_ID2  6
#define ARM_SERVO_ID3  10
#define ARM_DELAYMS 15

class Arm {
  private:
    int newTheta[ARM_SERVOS];
    int oldTheta[ARM_SERVOS];
    Servo R[ARM_SERVOS];
    int delay[ARM_SERVOS];
    int startTime;
  public:
    Arm( ): newTheta( {0,0,0} ), oldTheta( {0,0,0} ), delta( {0,0,0} ) {
        R[0].attach(ARM_SERVO_ID1);
        R[1].attach(ARM_SERVO_ID2);
        R[2].attach(ARM_SERVO_ID3);
    }
    void setNewTheta( int val, int newTheta[ARM_SERVOS] ) {
        int max = 0;
        for( int i = 0; i < ARM_SERVOS; ++i ) {
            this->newTheta[ i ] = newTheta[ i ];
            int diff = ABS( this->newTheta[ i ] - this->oldTheta[ i ] );
            if ( max < diff ) {
                max = diff;
            }
        }
        for( int i = 0; i < ARM_SERVOS; ++i ) {
            int diff = this->newTheta[ i ] - this->oldTheta[ i ];
            delay[ i ] = max / diff;
        }
        startTime = millis();
    }
    void moveAll() {
        for( int i = 0; i < ARM_SERVOS; ++i ) {
            int diff = newTheta[ i ] - oldTheta[ i ];
            if ( diff != 0 ) {
                int change = ( millis() - startTime ) / delay[ i ];
                if ( change > 0 ) {
                    if ( newTheta[ i ] - oldTheta[ i ] - change < diff ) {
                        oldTheta[ i ] += change;
                    } else {
                        oldTheta[ i ] = newTheta[ i ];
                    }
                    //XXX Set servo
                }
            }
        }
    }

};


#endif // ARM_CLASS_INCLUDED

