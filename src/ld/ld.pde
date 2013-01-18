
#include "Settings.h"
#include "WProgram.h"

#ifdef HAS_ARM_SERVO
/// The arm servos.
Servo R[ARM_SERVOS];
/// Initial angles for the arm.
Number initArmThetas[ ARM_SERVOS ] = { 0, 0, 0 };
/// Tracks the arm and helps control it.
Arm armManager( initArmThetas );
#endif

/// A counter for out going IDs.
int messageID = 0;

char inBoxBuffer[ 1000 ];
int inBoxBuffer_newChar = 0;

void establishContact( );
bool readMessage( );

void setup() {
    #ifdef HAS_ARM_SERVO
    R[0].attach(ARM_SERVO_ID1);
    R[1].attach(ARM_SERVO_ID2);
    R[2].attach(ARM_SERVO_ID3);
    for( int i = 0; i < ARM_SERVOS; ++i ) {
        R[ i ].write( initArmThetas[ i ] );
    }
    #endif
    Serial.begin( ROBOT_SERIAL_PORT_SPEED );
    establishContact( );
    Serial.flush();
    delay( 100 );
}

void loop() {
    if ( Serial.available() > 0 ) {
        if ( readMessage( ) ) {
            char type;
            int id;
            int numOfVars = sscanf( inBoxBuffer, "%c%d", &type, &id );
            if ( numOfVars != 2 ) {
                switch( type ) {
                #ifdef HAS_WHEEL_MOTOR
                  case ROBOT_SERVICE_WHEEL_SPEED:
                  {
                    Serial.write( ":C" );
                    Serial.print( id );
                    Serial.write( ';' );
                  }
                  break;
                #endif
                #ifdef HAS_WHEEL_SERVO
                  case ROBOT_SERVICE_WHEEL_ANGLE:
                  {
                    Serial.write( ":C" );
                    Serial.print( id );
                    Serial.write( ';' );
                  }
                  break;
                #endif
                #ifdef HAS_WHEEL_ENCODER
                  case ROBOT_SERVICE_WHEEL_ENCODER:
                  {
                    Serial.write( ":C" );
                    Serial.print( id );
                    Serial.write( ';' );
                  }
                  break;
                #endif
                #ifdef HAS_IR_SERVO
                  case ROBOT_SERVICE_IRSENSOR_SERVO:
                  {
                    Serial.write( ":C" );
                    Serial.print( id );
                    Serial.write( ';' );
                  }
                  break;
                #endif
                #ifdef HAS_IR_SENSOR
                  case ROBOT_SERVICE_IRSENSOR_POLL:
                  {
                    Serial.write( ":C" );
                    Serial.print( id );
                    Serial.write( ';' );
                  }
                  break;
                #endif
                #ifdef HAS_ARM_SERVO
                  case ROBOT_SERVICE_ARM_SERVO:
                  {
//                    if ( result->list.len() == 3 ) {
Serial.write( ":C" );
Serial.print( id );
Serial.write( ';' );
                        armManager.setNewTheta( millis(), result->list );


//                    }
//                    else {
//                        sprintf( tempOutString, "%c%c%dError: wrong number arguments to servo.",
//                            ROBOT_MSG_START, ROBOT_RESPONSE_ERROR, ROBOT_SERIAL_ERROR_WRONG_ARGUMENTS, ROBOT_MSG_TERMINATOR );
//                        serialOutBox.append( tempOutString, strlen( tempOutString ) );
//                    }

                  }
                  break;
                #endif
                  default:
                  {
                    Serial.write( ":E" );
                    Serial.print( id );
                    Serial.write( "Error: No such service. Message was\"" );
                    Serial.write( inBoxBuffer );
                    Serial.write( "\";" );

                  }
                }
            }
            else {
                Serial.write( ":E" );
                Serial.write( "Error: Bad message. Message was\"" );
                Serial.write( inBoxBuffer );
                Serial.write( "\";" );
            }
        }
    }
    #ifdef HAS_ARM_SERVO
    if ( armManager.inMove() ) {
        for(int i = 0; i < ARM_SERVOS; ++i ) {
          int theta = armManager.currentTheta[ i ];
          if ( armManager.move( i, millis(), &theta ) ) {
              R[ i ].write( theta );
          }
        }
    }
    #endif
    delay( 150 );
}

/**
 * Reads the bytes from the serial buffer and returns true
 *  when a full message is received in full.
 *
 * @param serial can take the "Serial" object.
 * @param outMessage is used to accumulate bytes from the buffer.
 *
 * @return TRUE if a message is received or FALSE otherwise.
 */
bool readMessage( ) {
    char chr;
    static bool foundMessage = false;
    while ( Serial.available() > 0 ) {
        chr = Serial.read();
        if ( chr == ROBOT_SERIAL_MESSAGE_START ) {
            foundMessage = true;
            inBoxBuffer_newChar = 0;
        }
        else if ( chr == ROBOT_SERIAL_MESSAGE_STOP ) {
            if ( inBoxBuffer_newChar != 0 ) {
                inBoxBuffer[ inBoxBuffer_newChar ] = '\0';
                return true;
            }
            foundMessage = false;
        }
        else if ( foundMessage )
            inBoxBuffer[ inBoxBuffer_newChar++ ] = chr;
    }
    inBoxBuffer[ inBoxBuffer_newChar ] = '\0';
    return false;
}

/**
 * Waits for a greeting then returns a greeting. This
 *  function could never terminate if a byte is not
 *  received.
 *
 * Preconditions:
 * -Serial.begin() has been called successfully.
 *
 * @param serial can take the "Serial" object.
 */
void establishContact( ) {
  while( Serial.available() <= 0 ) {
    delay( 300 );
  }
  // Write back one char.
  Serial.write( Serial.read() );
}



