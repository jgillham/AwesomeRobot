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

/**
 * Sets up the port and establishes contact.
 */
void setup() {
   Serial.begin( PORT_SPEED );
   establishContact();
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
  // Simulate damaged or lost data.
  delay( 300 );
}
