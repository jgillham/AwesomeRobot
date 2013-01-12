#include "ArrayBuilder.h"
#include "Settings.h"

typedef ArrayBuilder< char > StringBuilder;
StringBuilder serialOutBox;

void establishContact();
void readBytes( char buffer[], int numOfBytes );
bool readMessage( StringBuilder& outMessage );

void setup() {
    Serial.begin( ROBOT_SERIAL_PORT_SPEED );
    establishContact();
}

void loop() {
    if ( Serial.available() > 0 ) {
        StringBuilder message;
        if ( readMessage( message ) ) {
            // Message received and decode.
        }
    }
    if ( serialOutBox.len() > 0 ) {
        Serial.write( (const char*)serialOutBox );
        serialOutBox.reset();
    }
}

/**
 * Reads the bytes from the serial buffer and returns true
 *  when a message is received in full.
 *
 * @param outMessage is used to accumulate bytes from the buffer.
 *
 * @return TRUE if a message is received or FALSE otherwise.
 */
bool readMessage( StringBuilder& outMessage ) {
    char chr;
    bool foundMessage = false;
    while ( Serial.available() > 0 ) {
        chr = Serial.read();
        if ( chr == ROBOT_SERIAL_MESSAGE_START ) {
            foundMessage = true;
            outMessage.reset();
        }
        else if ( chr == ROBOT_SERIAL_MESSAGE_STOP ) {
            if ( outMessage.len() > 0 ) {
                return true;
            }
            foundMessage = false;
        }
        else if ( foundMessage )
            outMessage.append( chr );
    }
    return false;
}

/**
 * Says hello until the other end says
 *  hello back by printing a byte upstream
 *  until a byte is received. This function
 *  could never terminate if a byte is not
 *  received.
 *
 * Preconditions:
 * -Serial.begin() has been called successfully.
 *
 * Post Condtions:
 * -Serial.available() should be <= 0.
 */
void establishContact() {
  while( Serial.available() <= 0 ) {
    delay( 300 );
  }
  // Write back one char.
  Serial.write( Serial.read() );
}
