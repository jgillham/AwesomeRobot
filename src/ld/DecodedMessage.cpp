#include "DecodedMessage.h"

#ifdef TESTING
#include <cstdio>
#else
#include "WProgram.h"
#endif


DecodedMessage result;

DecodedMessage* decodeMessage( const char* message ) {
    result.list.reset();
    if ( sscanf( message, "%d%c", &(result.messageID), &(result.type) ) != 2 )
        return 0;

    //static DecodedMessage result( type, mID );
    const char* nextNumber = strchr( message, result.type );
    if ( !*( nextNumber + 1 ) )
        nextNumber = 0;
    printf( "nextNumber: %s\n", nextNumber );
    while( nextNumber ) {

        DecodedMessage::Data number;
        if ( sscanf( nextNumber + 1, "%d%*s", &number ) != 1 )
            return 0;
        result.list.append( number );
        nextNumber = strchr( nextNumber + 1, ',' );
        printf( "nextNumber: %s\n", nextNumber );
    }
    return &result;
}
