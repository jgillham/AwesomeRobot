#include "Arm.h"

#define ABS( X ) ( ( (X) < 0 )? -(X) : (X)  )
//#define SIGN( X )

Arm::Arm( Number initThetas[ARM_SERVOS] )
        :startTime( 0 ) {
    for(int i = 0; i < ARM_SERVOS; ++i ) {
        oldTheta[ i ] = initThetas[ i ];
        newTheta[ i ] = initThetas[ i ];
        currentTheta[ i ] = initThetas[ i ];
        inProgress[ i ] = false;
    }
    //armServosInit( newTheta );
}

void Arm::setNewTheta( int time, Number newTheta[ARM_SERVOS] ) {
    int max = 0;
    for( int i = 0; i < ARM_SERVOS; ++i ) {
        this->newTheta[ i ] = newTheta[ i ];

        int temp = this->newTheta[ i ] - this->oldTheta[ i ];
        int diff = ABS( temp );
        if ( max < diff ) {
            max = diff;
        }
    }
    for( int i = 0; i < ARM_SERVOS; ++i ) {
        int diff = this->newTheta[ i ] - this->oldTheta[ i ];
        delay[ i ] = ARM_DELAYMS * max / diff;
        inProgress[ i ] = true;
    }
    startTime = time;
}

bool Arm::move( int index, int time, Number* outNextTheta ) {
    bool foundDiff = false;
    int diff = newTheta[ index ] - currentTheta[ index ];
    if ( diff != 0 ) {
        foundDiff = true;
        int change = ( time - startTime ) / delay[ index ] + oldTheta[ index ] - currentTheta[ index ];

        if ( change != 0 ) {
            if ( ABS( change ) < ABS( diff ) ) {
                currentTheta[ index ] += change;
            } else {
                oldTheta[ index ] = currentTheta[ index ] = newTheta[ index ];
            }
            *outNextTheta = currentTheta[ index ];
        }
    }
    inProgress[ index ] = foundDiff;
    return foundDiff;
}
bool Arm::inMove() {
    for( int i = 0; i < ARM_SERVOS; ++i ) {
        if ( this->inProgress[ i ] )
            return true;
    }
    return false;
}
