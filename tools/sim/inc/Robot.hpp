#ifndef ROBOT_CLASS_INCLUDED
#define ROBOT_CLASS_INCLUDED
#include "MapDrawer.hpp"
#include "State.hpp"
#include "FirstMate.hpp"

#define ROBOT_MAP_WIDTH 30
#define ROBOT_MAP_HEIGHT 60

#define MOVE_RATE 0.5
#define TURN_RATE 0.01
#define POSITION_TOLERANCE 1
#define THETA_TOLORANCE 1

/**
 * The robot class handles drawing the robot.
 */
class Robot : public FirstMate {
  private:
    double x, y;
    double mapTheta;
    State* state;
    int counter;

    double deltaX, deltaY, deltaTheta;
    int endCounter;

    double calculateTheta( double x, double y );
  public:
    // Static methods:
    static bool needToTurn( double x, double y, double heading, Waypoint& next, double tolerance );
    static bool needToMove( double x, double y, Waypoint& next, double tolerance );
    static double calculateTheta( double startX, double startY, double endX, double endY );

    // Instance methods:
    Robot( State* state, int x, int y );
    void draw( MapDrawer* mapDrawer );
    void update();
    // First mate implemetation:
    void turn( Waypoint& next );
    void move( Waypoint& next );
    bool needToTurn( Waypoint& next );
    bool needToMove( Waypoint& next );
    void signalEndState();
};

#endif // ROBOT_CLASS_INCLUDED
