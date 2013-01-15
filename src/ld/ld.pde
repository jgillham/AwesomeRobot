#include "Support.h"
#include "Settings.h"
#include "DecodedMessage.h"
#include "Arm.h"

typedef ArrayBuilder< char > StringBuilder;
StringBuilder serialOutBox;
int messageID = 0;

void setup() {
    Serial.begin( ROBOT_SERIAL_PORT_SPEED );
    establishContact( Serial );
    Serial.flush();
    delay( 100 );
}
char tempOutString[ROBOT_MAX_MESSAGE_SIZE];
Arm armManager;

void loop() {
    if ( Serial.available() > 0 ) {
        StringBuilder message;
        if ( readMessage( Serial, message ) ) {
            DecodedMessage* result = decodeMessage( message );
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
                        armManager.setNewTheta( result->list, millis() );

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
        armManager.moveAll( millis() );
    }
    #endif
    if ( serialOutBox.len() > 0 ) {
        Serial.write( (const char*)serialOutBox );
        serialOutBox.reset();
    }
}



