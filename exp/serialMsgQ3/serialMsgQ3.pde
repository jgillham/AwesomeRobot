/**
 * This program receives messages from the PC. Each message has
 *  an ID. The program sends a confirmation per message. Each
 *  confirmation has the corresponding message ID.
 *
 * @author Josh Gillham
 * @version 12-19-12
 */

#include "StringBuilder.h"
#include "support.h"
#include "settings.h"

extern StringBuilder serialOutBox;

/**
 * Sets up the port and establishes contact.
 */
void setup() {
   Serial.begin( PORT_SPEED );
   establishContact();
   Serial.print( ":");
      Serial.print( "timeRequestEndTime ");
      Serial.print( timeRequestEndTime );
      Serial.print( ";");
}

/**
 * Catches all the input and calls readBytes() to
 *  respond to the input.
 */
void loop() {
  if ( Serial.available() > 0 ) {
    int numOfBytes = Serial.available();

    char buffer[numOfBytes];

    // First grab all the bytes.
    for( int i = 0; i < numOfBytes; ++i ) {
      buffer[ i ] = Serial.read();
    }

    // Now handle each byte.
    readBytes( buffer, numOfBytes );


  }
  if ( timeRequestEndTime > 0 &&
        timeRequestEndTime <= millis() ) {
    // Write confirmation message.
    // How to handle multiple time requests?
    char tempOutString[MAX_MESSAGE_SIZE];
    sprintf( tempOutString, "%ct%c", MSG_START, MSG_TERMINATOR );
    serialOutBox.appends( tempOutString );
    timeRequestEndTime = 0;
  }
  if ( serialOutBox.len() > 0 ) {
    Serial.write( (const char*)serialOutBox );
    serialOutBox.reset();
  }
  delay( 1000 );
}
