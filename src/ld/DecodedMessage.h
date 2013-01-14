#ifndef DECODEDMESSAGE_CLASS_INCLUDED
#define DECODEDMESSAGE_CLASS_INCLUDED

#include "ArrayBuilder.h"
#include <string.h>

class DecodedMessage {
  public:
    typedef unsigned int Data;
    typedef ArrayBuilder< Data > DataList;

    char type;
    Data messageID;
    DataList list;

    DecodedMessage() {
    }

    DecodedMessage( char type, Data messageID )
        : type( type ), messageID( messageID ) {
    }

    class BadMessage {
        const char* msg;
      public:
        BadMessage( const char* message ): msg( message ) {
        }
        const char* what() {
            return msg;
        }

    };


};

DecodedMessage* decodeMessage( const char* message );

#endif // DECODEDMESSAGE_CLASS_INCLUDED

