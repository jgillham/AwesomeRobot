/**
 * This model provides needed functionality to serialMsgQ.pde.
 *
 * @author Josh Gillham
 * @version 12-20-12
 */

#include "support.h"
#include "settings.h"
#include "StringBuilder.h"
  // Include arduino libraries.
#include <WProgram.h>
  // Declared in serialMsgQ.pde
StringBuilder serialInBox;

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
  // Write back everything.
  while( Serial.available() > 0 )
    Serial.write( Serial.read() );
}

/**
 * Reads the bytes in the buffer. Interprets messages as
 *  it detects them.
 *
 * Preconditions:
 * -serialInBox has been initialized.
 * -MAX_MESSAGE_SIZE number of bytes of memory availiable
 *   on the stack.
 * -Serial.begin() has been called successfully.
 * -serialInBox may need more memory on the heap.
 *
 * Post Conditions:
 * -serialInBox may have additional bytes from buffer if the proper
 *   begginning and ending chars are received and the message is
 *   properly formatted.

 * @param buffer is the array of characters to read.
 * @param numOfBytes is the length of the array.
 */
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
