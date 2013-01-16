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
 * Proves the arm will move forward.
 *
 * @return TRUE if the test succeeds.
 */
bool goodBehavior_integration_positive_angles() {
  bool status = true;
  ++total_tests;
  // Check moving 3 degrees in 3 steps.
  {
      Number initTheta[ ARM_SERVOS ] = { 0, 0, 0 };
      Number newTheta[ ARM_SERVOS ] = { 3, 3, 3 };
      Arm instance( initTheta );
      TEST_( !instance.inMove(), printf( "FAILURE BECAUSE: arm should not be in a move.\n" )  );
      int time = 5000;
      Number tempTheta;
      instance.setNewTheta( time, newTheta );
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( ARM_DELAYMS, instance.delay[ s ] );
          TEST_EQUAL( newTheta[ s ], instance.newTheta[ s ] );
      }
      TEST_( instance.inMove(), printf( "FAILURE BECAUSE: arm should be in a move.\n" )  );

      time += ARM_DELAYMS;
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( true, instance.move( s, time, &tempTheta ) );
          TEST_EQUAL( 1, tempTheta );
      }
      TEST_( instance.inMove(), printf( "FAILURE BECAUSE: arm should be in a move.\n" )  );

      time += ARM_DELAYMS;
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( true, instance.move( s, time, &tempTheta ) );
          TEST_EQUAL( 2, tempTheta );
      }
      TEST_( instance.inMove(), printf( "FAILURE BECAUSE: arm should be in a move.\n" )  );

      time += ARM_DELAYMS;
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( true, instance.move( s, time, &tempTheta ) );
          TEST_EQUAL( 3, tempTheta );
      }

      TEST_( !instance.inMove(), printf( "FAILURE BECAUSE: arm should not be in a move.\n" )  );
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( false, instance.move( s, time, 0 ) );
      }
      time += ARM_DELAYMS;
      TEST_( !instance.inMove(), printf( "FAILURE BECAUSE: arm should not be in a move.\n" )  );
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( false, instance.move( s, time, 0 ) );
      }

      time += ARM_DELAYMS;
      TEST_( !instance.inMove(), printf( "FAILURE BECAUSE: arm should not be in a move.\n" )  );
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( false, instance.move( s, time, 0 ) );
      }
  }

  // Check move 3 degrees in one step.
  {
      Number initTheta[ ARM_SERVOS ] = { 0, 0, 0 };
      Number newTheta[ ARM_SERVOS ] = { 3, 3, 3 };
      Arm instance( initTheta );
      int time = 5000;
      Number tempTheta;
      instance.setNewTheta( time, newTheta );
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( ARM_DELAYMS, instance.delay[ s ] );
          TEST_EQUAL( newTheta[ s ], instance.newTheta[ s ] );
      }
      TEST_( instance.inMove(), printf( "FAILURE BECAUSE: arm should be in a move.\n" )  );

      time += ARM_DELAYMS * 3;
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( true, instance.move( s, time, &tempTheta ) );
          TEST_EQUAL( 3, tempTheta );
      }
      TEST_( !instance.inMove(), printf( "FAILURE BECAUSE: arm should not be in a move.\n" )  );

      time += ARM_DELAYMS;
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( false, instance.move( s, time, 0 ) );
      }
      TEST_( !instance.inMove(), printf( "FAILURE BECAUSE: arm should not be in a move.\n" )  );
  }

  // Check move 3 degrees in one step with large gap.
  {
      Number initTheta[ ARM_SERVOS ] = { 0, 0, 0 };
      Number newTheta[ ARM_SERVOS ] = { 3, 3, 3 };
      Arm instance( initTheta );
      int time = 5000;
      Number tempTheta;
      instance.setNewTheta( time, newTheta );
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( ARM_DELAYMS, instance.delay[ s ] );
          TEST_EQUAL( newTheta[ s ], instance.newTheta[ s ] );
      }
      TEST_( instance.inMove(), printf( "FAILURE BECAUSE: arm should be in a move.\n" )  );

      time += ARM_DELAYMS * 30;
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( true, instance.move( s, time, &tempTheta ) );
          TEST_EQUAL( 3, tempTheta );
      }
      TEST_( !instance.inMove(), printf( "FAILURE BECAUSE: arm should not be in a move.\n" )  );

      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( false, instance.move( s, time, 0 ) );
      }
      TEST_( !instance.inMove(), printf( "FAILURE BECAUSE: arm should not be in a move.\n" )  );
      time += ARM_DELAYMS;
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( false, instance.move( s, time, 0 ) );
      }
      TEST_( !instance.inMove(), printf( "FAILURE BECAUSE: arm should not be in a move.\n" )  );
  }

  // Check move 30 degrees in 30 steps.
  {
      const int MAX = 30;
      Number initTheta[ ARM_SERVOS ] = { 0, 0, 0 };
      Number newTheta[ ARM_SERVOS ] = { MAX, MAX, MAX };
      Arm instance( initTheta );
      int time = 5000;
      Number tempTheta;
      instance.setNewTheta( time, newTheta );
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( ARM_DELAYMS, instance.delay[ s ] );
          TEST_EQUAL( newTheta[ s ], instance.newTheta[ s ] );
      }
      TEST_( instance.inMove(), printf( "FAILURE BECAUSE: arm should be in a move.\n" )  );


      for( int i = 1; i <= 30; ++i ) {
          time += ARM_DELAYMS ;
          TEST_( instance.inMove(), printf( "FAILURE BECAUSE: arm should be in a move.\n" )  );
          for( int s = 0; s < ARM_SERVOS; ++s ) {
              TEST_EQUAL( true, instance.move( s, time, &tempTheta ) );
              TEST_EQUAL( i, tempTheta );
          }
      }
      TEST_( !instance.inMove(), printf( "FAILURE BECAUSE: arm should not be in a move.\n" )  );

      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( false, instance.move( s, time, 0 ) );
      }
      TEST_( !instance.inMove(), printf( "FAILURE BECAUSE: arm should not be in a move.\n" )  );
      time += ARM_DELAYMS;
      for( int s = 0; s < ARM_SERVOS; ++s ) {
          TEST_EQUAL( false, instance.move( s, time, 0 ) );
      }
      TEST_( !instance.inMove(), printf( "FAILURE BECAUSE: arm should not be in a move.\n" )  );
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
  if ( !goodBehavior_integration_positive_angles() )
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
