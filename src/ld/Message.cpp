#include "Message.h"

#ifdef TESTING
#include <cstdio>
#else
#include "WProgram.h"
#endif


Message result;

Message* decodeMessage( const char* message ) {
    result.list.reset();
    if ( sscanf( message, "%d%c", &(result.messageID), &(result.type) ) != 2 )
        return 0;

    //static DecodedMessage result( type, mID );
    const char* nextNumber = strchr( message, result.type );
    if ( !*( nextNumber + 1 ) )
        nextNumber = 0;
    printf( "nextNumber: %s\n", nextNumber );
    while( nextNumber ) {

        Number number;
        if ( sscanf( nextNumber + 1, "%d%*s", &number ) != 1 ) {
            return 0;
        }
        result.list.append( number );
        nextNumber = strchr( nextNumber + 1, ',' );
        printf( "nextNumber: %s\n", nextNumber );
    }
    return &result;
}

bool encodeMessage( Message& message, char* outBuffer ) {
    int charsWritten =
        sprintf( outBuffer, "%c%d%c%c", ROBOT_SERIAL_MESSAGE_START, message.messageID, message.type );
    if ( charsWritten < 0 )
        return false;
    for( int i = 0; i < message.list.len(); ++i ) {
        // Move to the end of the string.
        outBuffer += charsWritten;
        if ( !i ) {
            charsWritten = sprintf( outBuffer, "%d", message.list[i] );
        }
        else {
            charsWritten = sprintf( outBuffer, ",%d", message.list[i] );
        }
        if ( charsWritten < 0 )
            return false;
    }
    // Move to the end of the string.
    outBuffer += charsWritten;
    charsWritten = sprintf( outBuffer, "%c", ROBOT_SERIAL_MESSAGE_STOP );
    if ( charsWritten < 0 )
        return false;
    return true;
}
