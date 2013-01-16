#ifndef DECODEDMESSAGE_CLASS_INCLUDED
#define DECODEDMESSAGE_CLASS_INCLUDED

#include "ArrayBuilder.h"
#include <string.h>
#include "Settings.h"

class DecodedMessage {
  public:
    typedef ArrayBuilder< Number > DataList;

    char type;
    Number messageID;
    DataList list;

    DecodedMessage() {
    }

    DecodedMessage( char type, Number messageID )
        : type( type ), messageID( messageID ) {
    }
};

DecodedMessage* decodeMessage( const char* message );

#endif // DECODEDMESSAGE_CLASS_INCLUDED

