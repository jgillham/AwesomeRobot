  // Enable testing
#define TEST
  // For print.
#include <stdio.h>

#include "Robot.hpp"
#include "Waypoint.hpp"
#include "matha.h"
#include "tests.h"

  // Forward declaration.
int goodBehavior_TestSuite();

/**
 * Main calls test_suite() and returns results.
 */
int main() {
	int ret=goodBehavior_TestSuite();
	return ret;
}

  // Keep track of the results.
/// Holds the number of failed assertions.
int bad_asserts = 0;
/// Holds the number of total assertions.
int total_assertions = 0;
/// Holds the number of failed tests.
int bad_tests = 0;
/// Holds the number of total tests.
int total_tests = 0;

/**
 * Proves calculateTheta() can produce the correct angles
 *  for all vectors around the clock.
 *
 * @return TRUE if the test succeeds.
 */
bool goodBehavior_calculateTheta() {
  bool status = true;
  ++total_tests;

    // 45 degree angles:
  TEST_FLOAT(
    Robot::calculateTheta( 200, 200, 300, 300 ), (-3*PI / 4), THETA_TOLORANCE
  );
  TEST_FLOAT(
    Robot::calculateTheta( 200, 200, 100, 100 ), (PI / 4), THETA_TOLORANCE
  );
  TEST_FLOAT(
    Robot::calculateTheta( 200, 200, 300, 100 ), (-PI / 4), THETA_TOLORANCE
  );
  TEST_FLOAT(
    Robot::calculateTheta( 200, 200, 100, 300 ), (3*PI / 4), THETA_TOLORANCE
  );

    // 60 degree angles.
  TEST_FLOAT(
    Robot::calculateTheta( 300, 100  * sqrt( 3 ), 100, 300 * sqrt( 3 ) ), (5*PI/6), THETA_TOLORANCE
  );
  TEST_FLOAT(
    Robot::calculateTheta( 100, 100  * sqrt( 3 ), 300, 300  * sqrt( 3 ) ), -(5*PI/6), THETA_TOLORANCE
  );
  TEST_FLOAT(
    Robot::calculateTheta( 300, 300  * sqrt( 3 ), 100, 100  * sqrt( 3 ) ), (PI/3), THETA_TOLORANCE
  );
  TEST_FLOAT(
    Robot::calculateTheta( 100, 300  * sqrt( 3 ), 300, 100  * sqrt( 3 ) ), -(PI/3), THETA_TOLORANCE
  );

  if ( status )
    printf( "Test %s successful!\n", __FUNCTION__ );
  return status;
}

/**
 * Proves that needToTurn() will return true when
 *  the robot is not lined up with his next waypoint
 *  or false other wise.
 *
 * @return TRUE if the test succeeds.
 */
bool goodBehavior_needToTurn() {
  bool status = true;
  ++total_tests;
  Waypoint wp = (Waypoint){ 1.4, 500, 250 };
  TEST_(
    Robot::needToTurn( 100, 100, 0, wp, THETA_TOLORANCE ),
    (void)0
  );
  if ( status )
    printf( "Test %s successful!\n", __FUNCTION__ );
  return status;
}

/**
 * Proves that needToMove returns true when the
 *  robot is too far from its waypoint or false
 *  otherwise.
 *
 * @return TRUE if the test succeeds.
 */
bool goodBehavior_needToMove() {
  bool status = true;
  ++total_tests;
  // True returns.
  for( int x = 1; x < 20; ++x ) {
    for( int y = 1; y < 20; ++y ) {
      Waypoint wp = (Waypoint){ 1.4, 100+x, 100+y };
      TEST_(
        Robot::needToMove( 100, 100, wp, POSITION_TOLERANCE ),
        printf( "x: %d, y: %d\n", x, y )
      );
    }
  }
  // False returns.
  for( int x = 0; x < 20; ++x ) {
    for( int y = 0; y < 20; ++y ) {
      Waypoint wp = (Waypoint){ 1.4, 100+x/20, 100+y/20 };
      TEST_(
        !Robot::needToMove( 100, 100, wp, POSITION_TOLERANCE ),
        printf( "x: %d, y: %d\n", x, y )
      );
    }
  }
  if ( status )
    printf( "Test %s successful!\n", __FUNCTION__ );
  return status;
}

/**
 * Holds all the test cases. Arguments can be passed and the return type changed.
 *
 * Local variables hold successes, failures, and other information.
 * local var TEST_SUITE_UNSUCCESSFUL_TESTS holds the unsuccessful test count.
 * local var TEST_SUITE_TOTAL_TESTS holds the total test count.
 */
int goodBehavior_TestSuite(){
  bad_asserts = 0;
  total_assertions = 0;
  printf( "BEGIN Good Behavior Tests\n");

    // Run each test and count the successes.
  if ( !goodBehavior_calculateTheta() )
    ++bad_tests;

  if ( !goodBehavior_needToTurn() )
    ++bad_tests;

  if ( !goodBehavior_needToMove() )
    ++bad_tests;

  printf( "END Good Behavior Tests\n");

    // Prints results.
  printf( "%d of %d assertions successful!\n", (total_assertions - bad_asserts), total_assertions );
  printf( "%d of %d tests successful!\n", (total_tests - bad_tests), total_tests );

    // Print status.
  if( bad_asserts == 0 )
    printf("Success!\n");
  else
    printf("Failure!\n");

  return bad_asserts;
}


