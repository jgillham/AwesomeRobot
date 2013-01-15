#ifndef ARMDRIVER_CLASS_INCLUDED
#define ARMDRIVER_CLASS_INCLUDED


bool armServosInit( );

bool armServosWrite( int theta[] );

#define ARM_SERVOS 3
#define ARM_DELTA
#define ARM_SERVO_ID1  5
#define ARM_SERVO_ID2  6
#define ARM_SERVO_ID3  10
#define ARM_DELAYMS 15



#endif // ARMDRIVER_CLASS_INCLUDED

