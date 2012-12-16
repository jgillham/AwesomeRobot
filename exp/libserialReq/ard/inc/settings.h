#ifndef SETTINGS_INCLUDED
#define SETTINGS_INCLUDED


  // The byte the arduino sends to say hello.
#define ARD_HELLO_BYTE '+'

#ifdef _SerialStream_h_
  #define PORT_SPEED LibSerial::SerialStreamBuf::BAUD_9600
  #define CHAR_WIDTH LibSerial::SerialStreamBuf::CHAR_SIZE_8
  #define FLOW_CONTROL LibSerial::SerialStreamBuf::FLOW_CONTROL_NONE
  #define PARITY_MODE LibSerial::SerialStreamBuf::PARITY_NONE
  #define STOP_BITS 1
#else
  #define PORT_SPEED 9600
#endif

#endif // SETTINGS_INCLUDED

