// Enable testing
#define TESTING
// For print.
#include <stdio.h>
// Testing macros.
#include "tests.h"
// For strlen()
#include <string.h>

// BEGIN Mock Declarations
#include <malloc.h>
void delay( int ) {
}
class HardwareSerial {
  private:
    const char* buffer;
    int nextChar;
  public:
    HardwareSerial( const char* buffer )
        : buffer( buffer ), nextChar( 0 ) {
    }
    char read() {
        char ret = buffer[ nextChar ];
        if ( ret ) {
            ++nextChar;
        }
        return ret;
    }
    int available() {
        return strlen( buffer + nextChar );
    }
    void write(char) {
    }
};
// END Mock Declarations

// Pull in test file.
#include "../Support.cpp"

// Forward declaration.
int goodBehavior_TestSuite();

/**
 * Main calls test_suite() and returns results.
 *
 * @return the number of failures.
 */
int main() {
	int ret=goodBehavior_TestSuite();
	return ret;
}

// BEGIN Results
/// Holds the number of failed assertions.
int bad_asserts = 0;
/// Holds the number of total assertions.
int total_assertions = 0;
/// Holds the number of failed tests.
int bad_tests = 0;
/// Holds the number of total tests.
int total_tests = 0;
// END Results

/**
 * Proves readMessage can handle most input from the serial
 *  port.
 *
 * @return TRUE if the test succeeds.
 */
bool goodBehavior_readMessage() {
  bool status = true;
  ++total_tests;
  // Check a typical message.
  {
      const char* expected = "Sample";
      char input[50];
      sprintf( input, ":%s;", expected );
      HardwareSerial serial( input );
      StringBuilder message;
      TEST_(
            readMessage( serial, message ),
            printf( "FAILURE BECAUSE: readMessage should have found a message.\n" )
      );
      TEST_(
            strcmp( message, expected ) == 0 && strlen( message ) == strlen( expected ),
            printf( "FAILURE BECAUSE: Message length should be the same as \"%s\".\n", expected )
      );
  }
  // Check a zero-length message
  {
      HardwareSerial serial( ":;");
      StringBuilder message;
      TEST_(
            !readMessage( serial, message ),
            printf( "FAILURE BECAUSE: readMessage should have NOT found a message.\n" )
      );
      TEST_(
            strlen( message ) == 0,
            printf( "FAILURE BECAUSE: Message should have been empty.\n" )
      );
  }
  // Check a unterminated message.
  {
      const char* expected = "Sample";
      char input[50];
      sprintf( input, ":%s", expected );
      HardwareSerial serial( input );
      StringBuilder message;
      TEST_(
            !readMessage( serial, message ),
            printf( "FAILURE BECAUSE: readMessage should have NOT found a message.\n" )
      );
      TEST_(
            strcmp( message, expected ) == 0 && strlen( message ) == strlen( expected ),
            printf( "FAILURE BECAUSE: Message should be \"%s\".\n", expected )
      );
  }
  // Check message growth.
  {
      const char* expected = "Sample";
      char input[50];
      sprintf( input, ":%s;", expected );
      StringBuilder message;
      {
          HardwareSerial serial( ":Sam");

          TEST_(
                !readMessage( serial, message ),
                printf( "FAILURE BECAUSE: readMessage should have NOT found a message.\n" )
          );
          TEST_(
                strlen( message ) == 3,
                printf( "FAILURE BECAUSE: Message should be \"Sam\".\n" )
          );
      }
      {
          HardwareSerial serial( "ple;");

          TEST_(
                readMessage( serial, message ),
                printf( "FAILURE BECAUSE: readMessage should have found a message.\n" )
          );
          TEST_(
                strcmp( message, expected ) == 0 && strlen( message ) == strlen( expected ),
                printf( "FAILURE BECAUSE: Message should be \"%s\" but was \"%s\".\n", expected, (const char*)message )
          );
      }
  }
  // Check a messed up message.
  {
      const char* expected = "amps";
      char input[50];
      sprintf( input, "Sa:%s;e", expected );
      HardwareSerial serial( "Sa:amps;e");
      StringBuilder message;
      TEST_(
            readMessage( serial, message ),
            printf( "FAILURE BECAUSE: readMessage should have found a message.\n" )
      );
      TEST_(
            strcmp( message, expected ) == 0 && strlen( message ) == strlen( expected ),
            printf( "FAILURE BECAUSE: Message should be \"%s\".\n", expected )
      );
  }

  if ( status )
    printf( "Test %s successful!\n", __FUNCTION__ );
  return status;
}

/**
 * Runs "good" behavor tests.
 *
 * @return the number of failures
 */
int goodBehavior_TestSuite(){
  bad_asserts = 0;
  total_assertions = 0;
  printf( "BEGIN Good Behavior Tests\n");

    // Run each test and count the successes.
  if ( !goodBehavior_readMessage() )
    ++bad_tests;

  printf( "END Good Behavior Tests\n");

    // Prints results.
  printf( "%d of %d assertions successful!\n", (total_assertions - bad_asserts), total_assertions );
  printf( "%d of %d tests successful!\n", (total_tests - bad_tests), total_tests );

    // Print status.
  if( bad_tests == 0 )
    printf("Success!\n");
  else
    printf("Failure!\n");

  return bad_tests;
}

