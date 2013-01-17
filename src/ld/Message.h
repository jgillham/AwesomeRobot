#ifndef DECODEDMESSAGE_CLASS_INCLUDED
#define DECODEDMESSAGE_CLASS_INCLUDED

#include "ArrayBuilder.h"
#include <string.h>
#include "Settings.h"

class Message {
  public:
    typedef ArrayBuilder< Number > DataList;

    char type;
    Number messageID;
    DataList list;

    Message() {
    }

    Message( char type, Number messageID )
        : type( type ), messageID( messageID ) {
    }
};

Message* decodeMessage( const char* message );
bool encodeMessage( Message& message, char* outBuffer );

#endif // DECODEDMESSAGE_CLASS_INCLUDED

