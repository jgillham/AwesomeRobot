#include "ArmDriver.h"

#include <Servo.h>
#include <WProgram.h>


Servo R[ARM_SERVOS];

bool armServosInit( ) {
    R[0].attach(ARM_SERVO_ID1);
    R[1].attach(ARM_SERVO_ID2);
    R[2].attach(ARM_SERVO_ID3);
}

bool armServosWrite( int theta[] ) {
    for( int i = 0; i < ARM_SERVOS; ++i ) {
        R[ i ].write( theta[ i ] );
    }
}
