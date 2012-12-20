/**
 * This program receives messages from the PC. Each message has
 *  an ID. The program sends a confirmation per message. Each
 *  confirmation has the corresponding message ID.
 *
 * @author Josh Gillham
 * @version 12-19-12
 */
 
#include "StringBuilder.h"
#define PORT_SPEED 115200//9600
#define MAX_MESSAGE_SIZE 200
#define MSG_TERMINATOR ';'
#define MSG_START ':'
/**
 * Says hello until the other end says
 *  hello back by printing a byte upstream
 *  until a byte is received.
 */
void establishContact() {
  while( Serial.available() <= 0 ) {
    delay( 300 );
  }
  while( Serial.available() > 0 )
    Serial.write( Serial.read() );
}

void setup() {
   Serial.begin( PORT_SPEED );
   establishContact();
}
 
StringBuilder serialInBox;

boolean foundMessage = false;
void loop() {
  if ( Serial.available() > 0 ) {
    int numOfBytes = Serial.available();
    //char chr = Serial.read();
    //Serial.write( "\'" );
    //  Serial.write( chr );
    //  Serial.write( "\'" );
    //  return;
    
    char buffer[numOfBytes];
    
    // First grab all the bytes.
    for( int i = 0; i < numOfBytes; ++i ) {
      buffer[ i ] = Serial.read();
    }
    
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
              // sscanf returns the number of variables read.
            if ( sscanf( (const char*)serialInBox, "D%d", &messageID ) == 1 ) {
              char tempOutString[MAX_MESSAGE_SIZE];
              //Serial.write( ":" );
              //Serial.write( (const char*)serialInBox );
              //Serial.write( ";" );
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
}
