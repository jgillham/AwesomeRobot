#include "support.h"
#include "settings.h"
#include "StringBuilder.h"
  // Include arduino libraries.
#include <WProgram.h>
  // Declared in serialMsgQ.pde
extern StringBuilder serialInBox;

/**
 * Says hello until the other end says
 *  hello back by printing a byte upstream
 *  until a byte is received.
 */
void establishContact() {
  while( Serial.available() <= 0 ) {
    delay( 300 );
  }
  // Write back everything.
  while( Serial.available() > 0 )
    Serial.write( Serial.read() );
}

void readBytes( char buffer[], int numOfBytes ) {
  static boolean foundMessage = false;
  // Handle each byte.
    for( int i = 0; i < numOfBytes; ++i ) {
      char chr = buffer[ i ];
      switch( chr ) {
        case MSG_START:
        {
          foundMessage = true;
          //XXX Clear inbox.
        }
        break;
        case MSG_TERMINATOR:
        {
          if ( serialInBox.len() > 0 ) {
              // What to do once we have the message?
            int messageID;
              // Read ID.
              // sscanf returns the number of variables read.
            if ( sscanf( (const char*)serialInBox, "D%d", &messageID ) == 1 ) {
                // Write confirmation message.
              char tempOutString[MAX_MESSAGE_SIZE];
              sprintf( tempOutString, ":C%d%c;", messageID, MSG_TERMINATOR );
              Serial.write( tempOutString );
            }
            foundMessage = false;
              // Discard message.
            serialInBox.reset();
          }
        }
        break;
        default:
        {
          if ( foundMessage )
            serialInBox.append( chr );
        }
        break;
      }
    }
}
