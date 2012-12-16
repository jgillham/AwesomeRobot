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

char* readBuffer( SerialStream& stream, int index = 0 ) {
  char* buffer = 0;
  //std::cout << "stream.rdbuf()->in_avail(): " << stream.rdbuf()->in_avail() << std::endl;
  if ( stream.rdbuf()->in_avail()  != 0 ) {
    //std::cout << "stream.rdbuf()->in_avail(): " << stream.rdbuf()->in_avail() << std::endl;
    char byte;
    stream.get( byte );
    if ( byte != 0 ) {
      buffer = readBuffer( stream, index + 1 );
      buffer[ index ] = byte;
      return buffer;
    }
  }

  if ( index > 0 ) {
      // One additional char for the null.
      // index, on this branch, will be the char count.
    buffer = (char*)malloc( index + 1 );
    buffer[ index ] = '\0';
  }

  return buffer;
}
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
char* bytesOf( char* pointer, int size ) {
  char* bytes = new char[size]();
  for( int i = 0; i < size; ++i )
    bytes[i] = *( pointer + i );
  return bytes;
}

template<class T > char* bytesOf( T& value ) {
  int sizeOfT = sizeof( T );
  char* pointer = reinterpret_cast<char*>(&value);
  return bytesOf( pointer, sizeOfT );
}

template<class T, int N > char* bytesOf( T (&value)[N] ) {
  int sizeOfT = N * sizeof( T );
  char* pointer = &value;
  return bytesOf( pointer, sizeOfT );
}
/**
 * Starts the program. Listens to the port for
 *  a greeting from the arduino. Sends a response
 *  after the greeting is received.
 *
 * @returns 0 if the operation was successful.
 */
int main() {
  int* test = (int*)1;
  bytesOf( test );
  const char* operations[] = {
    "A15,20",
    "A48,17",
    "A13,8"
  };
  const int opLen = sizeof( operations ) / sizeof(char*);
  int currentOperation = 0;
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
  bool startRequests = false;
  bool done = false;
  int sentRequests = 0;
  int answers = 0;
  std::cout << "opLen: " << opLen << std::endl;
    // Limit the passes through the loop.
  while( !done && i++ < SESSION_LIMIT ) {
    //std::cout << i << "checkpoint: " << __LINE__ << std::endl;
    if ( stream.rdbuf()->in_avail()  != 0 ) {
      char* message = readBuffer( stream );
      AutoFree garbageCollector( message );

      std::cout << "Arduino says: "<< message << std::endl;
      #define SUM_COMPLETE 'S'
      switch( *message ) {
        case ARD_HELLO_BYTE:
          startRequests = true;
        break;
        case SUM_COMPLETE:
          ++answers;
          int result;
          sscanf( message, "S%d", &result );
          std::cout << "Sum result: "<< result << std::endl;
        break;
      }
      if ( answers == sentRequests && currentOperation == opLen )
        done = true;
    }

    if ( startRequests && currentOperation < opLen ) {
      const char* request = operations[ currentOperation++ ];
      stream << request;
      stream << '\0';
      std::cout << "PC says: "<< request << std::endl;
      ++sentRequests;
    }

    usleep( 100000 );
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
SerialSetupExitCodes setupSerialPort( SerialStream& stream, const char* portDesc ) {
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
