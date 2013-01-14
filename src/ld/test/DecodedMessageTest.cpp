// Enable testing
#define TESTING
// For print.
#include <stdio.h>
// Testing macros.
#include "tests.h"
// For strlen()
#include <string.h>



// Pull in test file.
#include "../DecodedMessage.cpp"

#undef delay
#undef HardwareSerial

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
 * Proves decodeMessage will convert a string message into
 *  a decodedMessage in most cases.
 *
 * @return TRUE if the test succeeds.
 */
bool goodBehavior_decodeMessage() {
  bool status = true;
  ++total_tests;
  // Check an empty message.
  try {
      const char* input = "12C";
      DecodedMessage& actual = *decodeMessage( input );
      TEST_EQUAL( 'C', actual.type );
      TEST_EQUAL( 12, actual.messageID );
  }
  catch ( DecodedMessage::BadMessage* ex ) {
      TEST_( 0, printf( "FAILURE BECAUSE: %s\n", ex->what() ) )
  }
  // Check a message with one data piece.
  try {
      const char* input = "50C13";
      DecodedMessage& actual = *decodeMessage( input );
      DecodedMessage expected( 'C', 50 );
      TEST_EQUAL( 'C', actual.type );
      TEST_EQUAL( 50, actual.messageID );
      int length = actual.list.len();
      TEST_EQUAL( 1, length );

      const unsigned int* dataList = (const unsigned int*)(actual.list);
      TEST_EQUAL( 13, dataList[0] );
      printf( "dataList[0]: %d\n", dataList[0] );


  }
  catch ( DecodedMessage::BadMessage* ex ) {
      TEST_( 0, printf( "FAILURE BECAUSE: %s\n", ex->what() ) )
  }
  // Check a message with one data piece.
  try {
      const char* input = "11T223,5463";
      DecodedMessage& actual = *decodeMessage( input );
      TEST_EQUAL( 'T', actual.type );
      TEST_EQUAL( 11, actual.messageID );
      int length = actual.list.len();
      TEST_EQUAL( 2, length );

      const unsigned int* dataList = (const unsigned int*)(actual.list);
      TEST_EQUAL( 223, dataList[0] );
      TEST_EQUAL( 5463, dataList[1] );


  }
  catch ( DecodedMessage::BadMessage* ex ) {
      TEST_( 0, printf( "FAILURE BECAUSE: %s\n", ex->what() ) )
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
  if ( !goodBehavior_decodeMessage() )
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


