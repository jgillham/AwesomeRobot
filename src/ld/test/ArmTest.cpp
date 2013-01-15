// Enable testing
#define TESTING
// For print.
#include <stdio.h>
// Testing macros.
#include "tests.h"
// For strlen()
#include <string.h>



// Pull in test file.
#include "../Arm.cpp"

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
bool armServosInit( ) {
}


int lastThetaWritten2[ ARM_SERVOS ];
bool armServosWrite( int theta[ARM_SERVOS] ) {
    for( int i = 0; i < ARM_SERVOS; ++i ) {
        lastThetaWritten2[ i ] = theta[ i ];
    }
}
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
bool goodBehavior_integration() {
  bool status = true;
  ++total_tests;
  // Check after appending a string.
  {
      Arm instance;
      int newTheta[ ARM_SERVOS ] = { 30, 30, 30 };
      int time = 5000;
      instance.setNewTheta( newTheta, 5000 );
      TEST_EQUAL( 30, instance.newTheta[ 0 ] );
      TEST_EQUAL( 30, instance.newTheta[ 1 ] );
      TEST_EQUAL( 30, instance.newTheta[ 2 ] );
      TEST_EQUAL( 15, instance.delay[ 0 ] );
      TEST_EQUAL( 15, instance.delay[ 1 ] );
      TEST_EQUAL( 15, instance.delay[ 2 ] );

      for( int i = 0; i <= 30; ++i ) {
          for( ; time < ARM_DELAYMS; ++time ) {
              instance.moveAll( time );
              TEST_EQUAL( time / ARM_DELAYMS, lastThetaWritten2[ 0 ] );
              TEST_EQUAL( time / ARM_DELAYMS, lastThetaWritten2[ 1 ] );
              TEST_EQUAL( time / ARM_DELAYMS, lastThetaWritten2[ 2 ] );
          }
      }


      time = 5000;
      instance.moveAll( time += ARM_DELAYMS );
      TEST_EQUAL( 1, lastThetaWritten2[ 0 ] );
      TEST_EQUAL( 1, lastThetaWritten2[ 1 ] );
      TEST_EQUAL( 1, lastThetaWritten2[ 2 ] );

      instance.moveAll( time += ARM_DELAYMS / 2 );
      TEST_EQUAL( 1, lastThetaWritten2[ 0 ] );
      TEST_EQUAL( 1, lastThetaWritten2[ 1 ] );
      TEST_EQUAL( 1, lastThetaWritten2[ 2 ] );

      instance.moveAll( time += ARM_DELAYMS );
      TEST_EQUAL( 2, lastThetaWritten2[ 0 ] );
      TEST_EQUAL( 2, lastThetaWritten2[ 1 ] );
      TEST_EQUAL( 2, lastThetaWritten2[ 2 ] );
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
  if ( !goodBehavior_integration() )
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
