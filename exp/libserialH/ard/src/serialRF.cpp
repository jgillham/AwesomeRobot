/**
 * Sends a hello upstream to the pc until a
 *  byte is received back. Any byte that is
 *  received is echoed back.
 *
 * @author Josh Gillham
 * @version 12-15-12
 */

  // Declares all the arduino functionality.
#include <WProgram.h>
  // Declares hello byte and port speed.
#include "settings.h"

  // Forward declaration.
void establishContact();

int main() {
    // Required to set up the arduino.
  init();
    // Setup port and establish contact.
  setup();
    // Never ending loop.
  while( 1 )
    loop();
  return 0;
}

/**
 * Says hello until the other end says
 *  hello back by printing a byte upstream
 *  until a byte is received.
 */
void establishContact() {
  while( Serial.available() <= 0 ) {
    Serial.print( ARD_HELLO_BYTE );
    delay( 300 );
  }
}

/**
 * Setups the port.
 */
void setup() {
  Serial.begin( PORT_SPEED );
  establishContact();
}

/**
 * Acts as a mirror, that is, every byte
 *  received is printed upstream.
 */
void loop() {
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    delay( 100 );
    Serial.print( char( inByte ) );
  }
  delay( 100 );
}
