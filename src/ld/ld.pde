#include "Support.h"
#include "Settings.h"
#include "DecodedMessage.h"

#define HAS_WHEEL_MOTOR

typedef ArrayBuilder< char > StringBuilder;
StringBuilder serialOutBox;
int messageID = 0;


void setup() {
    Serial.begin( ROBOT_SERIAL_PORT_SPEED );
    establishContact( Serial );
}

void loop() {
    if ( Serial.available() > 0 ) {
        StringBuilder message;
        if ( readMessage( Serial, message ) ) {
            DecodedMessage* result = decodeMessage( message );
            switch( result->type ) {
            #ifdef HAS_WHEEL_MOTOR
              case ROBOT_SERVICE_WHEEL_SPEED:
              {
                char tempOutString[ROBOT_MAX_MESSAGE_SIZE];
                sprintf( tempOutString, "%c%c%d%c", ROBOT_MSG_START, ROBOT_RESPONSE_COMFIRM, result->messageID, ROBOT_MSG_TERMINATOR );
                Serial.write( tempOutString );
                serialOutBox.appends( tempOutString );
              }
              break;
            #endif
              default:
              {
                char tempOutString[ROBOT_MAX_MESSAGE_SIZE];
                sprintf( tempOutString, "%c%cError service does not exist%c", ROBOT_MSG_START, ROBOT_RESPONSE_ERROR, ROBOT_MSG_TERMINATOR );
                serialOutBox.appends( tempOutString );
              }
            }
        }
    }
    if ( serialOutBox.len() > 0 ) {
        Serial.write( (const char*)serialOutBox );
        serialOutBox.reset();
    }
}


