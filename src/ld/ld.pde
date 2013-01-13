#include "Support.h"
#include "Settings.h"



typedef ArrayBuilder< char > StringBuilder;
StringBuilder serialOutBox;


void setup() {
    Serial.begin( ROBOT_SERIAL_PORT_SPEED );
    establishContact( Serial );
}

void loop() {
    if ( Serial.available() > 0 ) {
        StringBuilder message;
        if ( readMessage( Serial, message ) ) {
            // Message received and decode.
        }
    }
    if ( serialOutBox.len() > 0 ) {
        Serial.write( (const char*)serialOutBox );
        serialOutBox.reset();
    }
}


