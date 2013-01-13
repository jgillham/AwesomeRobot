#ifndef DECODEDMESSAGE_CLASS_INCLUDED
#define DECODEDMESSAGE_CLASS_INCLUDED
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

#include "ArrayBuilder.h"
#include <string.h>

class DecodedMessage {
  private:
    typedef unsigned int Data;
    typedef ArrayBuilder< Data > DataList;
    char type;
    Data arduinoID;
    Data messageID;
    DataList list;

    DecodedMessage( char type, Data arduinoID, Data messageID )
        : type( type ), arduinoID( arduinoID ), messageID( messageID ) {
    }
  public:
    class BadMessage {};

    static DecodedMessage decodeMessage( const char* message ) {
        Data type, aID, mID;
        if ( sscanf( message, "%c%d/%d%*s", &type, &aID, &mID ) != 3 ) {
            throw new BadMessage( "Invalid message header." );
        }
        DecodedMessage result( type, aID, mID );
        char* nextNumber = strchar( message, ',' );
        while( nextNumber ) {
            Data number;
            if ( sscanf( nextNumber, ",%d%*s", &number ) != 1 ) {
                throw new BadMessage( "Number did not follow comma." );
            }
            result.append( number );
            nextNumber = strchar( nextNumber + 1, ',' );
        }
        return result;
    }
};

#endif // DECODEDMESSAGE_CLASS_INCLUDED

