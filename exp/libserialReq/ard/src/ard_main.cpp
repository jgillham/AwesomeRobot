#include <WProgram.h>
#include "settings.h"

int main() {
  init();

  setup();

  while(1)
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

#define ADD_REQUEST 'A'
//char requestTypes[] = "T";
//enum RequestType {
//  ADD = 'A'
//};
#include <stdio.h>
//#include <malloc>

char* readBuffer( int index = 0 ) {
  char* buffer = 0;
  if ( Serial.available() > 0 ) {
    char byte = Serial.read();
    if ( byte != 0 ){
      buffer = readBuffer( index + 1 );
      buffer[ index ] = byte;
      return buffer;
    }
  }

  if ( index > 0 ) {
      // One additional char for the null.
      // index, on this branch, will be the char count.
    buffer = (char*)malloc( index + 1 );
    buffer[ index ] = '\0';
    return buffer;
  }
  return 0;
}
class AutoFree {
  public:
    AutoFree( void* pointer ): pointer( pointer ) {;
    }
    ~AutoFree() {
      free( this->pointer );
    }
  private:
    void* pointer;
};

void loop() {
  if (Serial.available() > 0) {
    char messageType = Serial.read();
    //Serial.print( messageType );
    switch( messageType ) {
      case ADD_REQUEST:
        int amount1;
        int amount2;
        char* encodedMessage;
        AutoFree garbageCollector( encodedMessage = readBuffer() );
        sscanf( encodedMessage, "%d,%d", &amount1, &amount2 );
        int result = amount1 + amount2;
        char encodedResult[100];
        sprintf( encodedResult, "S%d", result );
        Serial.print( encodedResult );
        Serial.print( '\0' );
      break;
    }
  }
  //delay( 100 );
}
