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
bool goodBehavior_append_array() {
  bool status = true;
  ++total_tests;
  // Check after appending a string.
  {
      StringBuilder instance;
      const char* expected = "My String";
      instance.append( expected, strlen( expected ) );
      const char* actual = instance;
      TEST_(
            strcmp( expected, actual ) == 0,
            printf( "FAILURE DUE TO: expected \"%s\" but actual was \"%s\".", expected, actual );
      );
      TEST_EQUAL( strlen( expected ), strlen( actual ) );
      TEST_EQUAL( strlen( expected ), instance.len() );
  }
  // Check after append chars and a string.
  {
      StringBuilder instance;
      const char* input = "My String";
      instance.append( 'd' );
      instance.append( 'a' );
      instance.append( input, strlen( input ) );
      const char* actual = instance;
      const char* expected = "daMy String";
      TEST_(
            strcmp( expected, actual ) == 0,
            printf( "FAILURE DUE TO: expected \"%s\" but actual was \"%s\".", expected, actual );
      );
      TEST_EQUAL( strlen( expected ), strlen( actual ) );
      TEST_EQUAL( strlen( expected ), instance.len() );
  }
  // Check after appending two strings.
  {
      StringBuilder instance;
      const char* input = "My String";
      const char* input2 = "Theta";
      instance.append( input, strlen( input ) );
      instance.append( input2, strlen( input2 ) );
      const char* actual = instance;
      const char* expected = "My StringTheta";
      TEST_(
            strcmp( expected, actual ) == 0,
            printf( "FAILURE DUE TO: expected \"%s\" but actual was \"%s\".", expected, actual );
      );
      TEST_EQUAL( strlen( expected ), strlen( actual ) );
      TEST_EQUAL( strlen( expected ), instance.len() );
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
  if ( !goodBehavior_append_array() )
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


