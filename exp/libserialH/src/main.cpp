/**
 * This program connects to the serial port and reads
 *  the hello byte from the stream. After the hello
 *  byte is read a message is sent to the arduino. The
 *  arduino will send the exact message back.
 *
 * @author Josh Gillham
 * @version 12-15-12
 */

#include <SerialStream.h>
  // For exit().
#include <cstdlib>
  // For cout and cerr.
#include <iostream>

  // Settings are shared between arduino code.
  //  Declares hello byte and port setttings.
#include "settings.h"
  // Declares enums and forward declarations
#include "main_private.hpp"

using namespace LibSerial;

/**
 * Starts the program. Listens to the port for
 *  a greeting from the arduino. Sends a response
 *  after the greeting is received.
 *
 * @returns 0 if the operation was successful.
 */
int main() {
  char pcMessage[] = "I am your leader!";
  int pcMsgIndex = 0;
    // Allocate on the stack.
  SerialStream stream;
    // Open and configure the port.
  SerialSetupExitCodes setupResult =
    setupSerialPort( stream, PORT );
  if ( setupResult != SUCCESS ) {
    displaySetupErrorMessage( setupResult );
    exit( setupResult );
  }

    // Count each pass through loop.
  int i = 0;
  char next_byte;
    // Limit the passes through the loop.
  while( ++i < SESSION_LIMIT  ) {
    stream.get(next_byte);
    std::cout << "Arduino says: "<< next_byte << std::endl;
    if ( next_byte == ARD_HELLO_BYTE ){
      while( pcMessage[ pcMsgIndex ] != 0 ) {
        stream << pcMessage[ pcMsgIndex ];
        std::cout << "PC says: "<< pcMessage[ pcMsgIndex ] << std::endl;
        ++pcMsgIndex;
      }
    }
  }
    // Free system resource. Does this happen in deconstructor???
  stream.Close();

  return 0;
}

/**
 * Shows the error message to the user which occured while
 *  calling setupSerialPort().
 *
 * @param errorNum is the return from setupSerialPort().
 */
void displaySetupErrorMessage( SerialSetupExitCodes errorNum ) {
  switch( errorNum ) {
    case FAILED_TO_OPEN:
      std::cerr << "Error: Could not open serial port."
                  << std::endl ;
    break;
    case FAILED_TO_SET_SPEED:
      std::cerr << "Error: Could not set the baud rate." <<  std::endl ;
    break;
    case FAILED_TO_SET_CHAR_WIDTH:
      std::cerr << "Error: Could not set the character size." <<
                  std::endl ;
    break;
    case FAILED_TO_SET_FLOW_CONTROL:
      std::cerr << "Error: Could not use hardware flow control."
                  << std::endl ;
    break;
    case FAILED_TO_SET_PARITY:
      std::cerr << "Error: Could not disable the parity." <<std::endl ;
    break;
    case FAILED_TO_SET_STOP_BITS:
      std::cerr << "Error: Could not set the number of stop bits."
                  << std::endl ;
    break;
  }
}

/**
 * Opens the serial port and configures it according
 *  to the arduino settings.
 *
 * Preconditions:
 * -stream is brand new.
 *
 * Post Conditions:
 * -stream is open and configured.
 *
 * @param stream the new serial stream class.
 * @param portDesc is location of the port.
 */
SerialSetupExitCodes setupSerialPort( SerialStream& stream, char* portDesc ) {
      // Open the port.
    stream.Open(portDesc);
    if ( ! stream.good() )
      return FAILED_TO_OPEN;

      // Set the connection speed.
    stream.SetBaudRate( PORT_SPEED );
    if ( ! stream.good() )
      return FAILED_TO_SET_SPEED;

      // Transfer one byte at a time.
    stream.SetCharSize( CHAR_WIDTH );
    if ( ! stream.good() )
      return FAILED_TO_SET_CHAR_WIDTH;

      // No slave-master control.
    stream.SetFlowControl( FLOW_CONTROL );
    if ( ! stream.good() )
      return FAILED_TO_SET_FLOW_CONTROL;

      // No error checking codes.
    stream.SetParity( PARITY_MODE );
    if ( ! stream.good() )
      return FAILED_TO_SET_PARITY;

      // Not sure.
    stream.SetNumOfStopBits( STOP_BITS );
    if ( ! stream.good() )
      return FAILED_TO_SET_STOP_BITS;

    return SUCCESS;
}
