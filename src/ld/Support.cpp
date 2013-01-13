#include "Support.h"
#include "Settings.h"

/**
 * Reads the bytes from the serial buffer and returns true
 *  when a full message is received in full.
 *
 * @param serial can take the "Serial" object.
 * @param outMessage is used to accumulate bytes from the buffer.
 *
 * @return TRUE if a message is received or FALSE otherwise.
 */
bool readMessage( HardwareSerial& serial, StringBuilder& outMessage ) {
    char chr;
    bool foundMessage = false;
    while ( serial.available() > 0 ) {
        chr = serial.read();
        if ( chr == ROBOT_SERIAL_MESSAGE_START ) {
            foundMessage = true;
            outMessage.reset();
        }
        else if ( chr == ROBOT_SERIAL_MESSAGE_STOP ) {
            if ( outMessage.len() > 0 ) {
                return true;
            }
            foundMessage = false;
        }
        else if ( foundMessage )
            outMessage.append( chr );
    }
    return false;
}

/**
 * Says hello until the other end says
 *  hello back by printing a byte upstream
 *  until a byte is received. This function
 *  could never terminate if a byte is not
 *  received.
 *
 * Preconditions:
 * -Serial.begin() has been called successfully.
 *
 * Post Condtions:
 * -Serial.available() should be <= 0.
 *
 * @param serial can take the "Serial" object.
 */
void establishContact( HardwareSerial& serial ) {
  while( serial.available() <= 0 ) {
    delay( 300 );
  }
  // Write back one char.
  serial.write( serial.read() );
}
