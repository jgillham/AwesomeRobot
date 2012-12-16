#ifndef MAIN_PRIVATE_INCLUDED
#define MAIN_PRIVATE_INCLUDED

  // The port location.
#define PORT "/dev/ttyACM0"
  // The maximum passes through the listening loop.
#define SESSION_LIMIT 25

/** The error codes for setupSerialPort(). */
typedef enum {
  SUCCESS,
  FAILED_TO_OPEN,
  FAILED_TO_SET_SPEED,
  FAILED_TO_SET_CHAR_WIDTH,
  FAILED_TO_SET_FLOW_CONTROL,
  FAILED_TO_SET_PARITY,
  FAILED_TO_SET_STOP_BITS
} SerialSetupExitCodes;

  // Forward declaration.
SerialSetupExitCodes setupSerialPort( LibSerial::SerialStream& stream, const char* portDesc );
void displaySetupErrorMessage( SerialSetupExitCodes errorNum );

#endif // MAIN_PRIVATE_INCLUDED

