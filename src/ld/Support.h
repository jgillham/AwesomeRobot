#ifndef SUPPORT_INCLUDED
#define SUPPORT_INCLUDED

#ifndef TESTING
#include "WProgram.h"
#endif
#include "ArrayBuilder.h"



bool readMessage( HardwareSerial& serial, StringBuilder& outMessage );
void establishContact( HardwareSerial& serial );

#endif // SUPPORT_INCLUDED

