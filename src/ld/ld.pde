
#include <Servo.h>

#include "Support.h"
#include "Settings.h"
#include "Message.h"
#include "Arm.h"
#include "ArrayBuilder.h"

#ifdef HAS_ARM_SERVO
/// The arm servos.
Servo R[ARM_SERVOS];
/// Initial angles for the arm.
Number initArmThetas[ ARM_SERVOS ] = { 0, 0, 0 };
/// Tracks the arm and helps control it.
Arm armManager( initArmThetas );
#endif

StringBuilder serialOutBox;
/// A counter for out going IDs.
int messageID = 0;
/// A temporary buffer.
char tempOutString[ROBOT_MAX_MESSAGE_SIZE];

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
    establishContact( Serial );
    Serial.flush();
    delay( 100 );
}

void loop() {
    if ( Serial.available() > 0 ) {
        StringBuilder message;
        if ( readMessage( Serial, message ) ) {
            Message* result = decodeMessage( message );
            if ( result != 0 ) {
                switch( result->type ) {
                #ifdef HAS_WHEEL_MOTOR
                  case ROBOT_SERVICE_WHEEL_SPEED:
                  {
                    sprintf( tempOutString, "%c%c%d%c", ROBOT_MSG_START, ROBOT_RESPONSE_COMFIRM, result->messageID, ROBOT_MSG_TERMINATOR );
                    serialOutBox.append( tempOutString, strlen( tempOutString ) );
                  }
                  break;
                #endif
                #ifdef HAS_WHEEL_SERVO
                  case ROBOT_SERVICE_WHEEL_ANGLE:
                  {
                    sprintf( tempOutString, "%c%c%d%c", ROBOT_MSG_START, ROBOT_RESPONSE_COMFIRM, result->messageID, ROBOT_MSG_TERMINATOR );
                    serialOutBox.append( tempOutString, strlen( tempOutString ) );
                  }
                  break;
                #endif
                #ifdef HAS_WHEEL_ENCODER
                  case ROBOT_SERVICE_WHEEL_ENCODER:
                  {
                    sprintf( tempOutString, "%c%c%d%c", ROBOT_MSG_START, ROBOT_RESPONSE_COMFIRM, result->messageID, ROBOT_MSG_TERMINATOR );
                    serialOutBox.append( tempOutString, strlen( tempOutString ) );
                  }
                  break;
                #endif
                #ifdef HAS_IR_SERVO
                  case ROBOT_SERVICE_IRSENSOR_SERVO:
                  {
                    sprintf( tempOutString, "%c%c%d%c", ROBOT_MSG_START, ROBOT_RESPONSE_COMFIRM, result->messageID, ROBOT_MSG_TERMINATOR );
                    serialOutBox.append( tempOutString, strlen( tempOutString ) );
                  }
                  break;
                #endif
                #ifdef HAS_IR_SENSOR
                  case ROBOT_SERVICE_IRSENSOR_POLL:
                  {
                    sprintf( tempOutString, "%c%c%d%c", ROBOT_MSG_START, ROBOT_RESPONSE_COMFIRM, result->messageID, ROBOT_MSG_TERMINATOR );
                    serialOutBox.append( tempOutString, strlen( tempOutString ) );
                  }
                  break;
                #endif
                #ifdef HAS_ARM_SERVO
                  case ROBOT_SERVICE_ARM_SERVO:
                  {
                    if ( result->list.len() == 3 ) {
                        sprintf( tempOutString, "%c%c%d%c", ROBOT_MSG_START, ROBOT_RESPONSE_COMFIRM, result->messageID, ROBOT_MSG_TERMINATOR );
                        serialOutBox.append( tempOutString, strlen( tempOutString ) );
                        armManager.setNewTheta( millis(), result->list );


                    }
                    else {
                        sprintf( tempOutString, "%c%c%dError: wrong number arguments to servo.",
                            ROBOT_MSG_START, ROBOT_RESPONSE_ERROR, ROBOT_SERIAL_ERROR_WRONG_ARGUMENTS, ROBOT_MSG_TERMINATOR );
                        serialOutBox.append( tempOutString, strlen( tempOutString ) );
                    }

                  }
                  break;
                #endif
                  default:
                  {
                    sprintf( tempOutString, "%c%c%dError: service does not exist%c",
                            ROBOT_MSG_START, ROBOT_RESPONSE_ERROR, ROBOT_SERIAL_ERROR_BAD_SERVICE, ROBOT_MSG_TERMINATOR );
                    serialOutBox.append( tempOutString, strlen( tempOutString ) );
                  }
                }
            }
            else {
                char tempOutString[ROBOT_MAX_MESSAGE_SIZE];
                sprintf( tempOutString, "%c%c%dError: bad message.%c",
                        ROBOT_MSG_START, ROBOT_RESPONSE_ERROR, ROBOT_SERIAL_ERROR_BAD_DECODE, ROBOT_MSG_TERMINATOR );
                serialOutBox.append( tempOutString, strlen( tempOutString ) );
            }
        }
    }
    #ifdef HAS_ARM_SERVO
    if ( armManager.inMove() ) {
        for(int i = 0; i < ARM_SERVOS; ++i ) {
          int theta = armManager.currentTheta[ i ];
          if ( armManager.move( i, millis(), &theta ) ) {
              R[ i ].write( theta );
              sprintf( tempOutString, "%carmWrite[%d]=%d%c", ROBOT_MSG_START, i, theta, ROBOT_MSG_TERMINATOR );
              serialOutBox.append( tempOutString, strlen( tempOutString ) );
          }
        }
    }
    #endif
    if ( serialOutBox.len() > 0 ) {
        Serial.write( (const char*)serialOutBox );
        serialOutBox.reset();
    }
    delay( 150 );
}



