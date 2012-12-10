#ifndef ROBOT_CLASS_INCLUDED
#define ROBOT_CLASS_INCLUDED
#include "MapDrawer.hpp"
#include "State.hpp"
#include "FirstMate.hpp"
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
    Robot( State* state, int x, int y );
    void draw( MapDrawer* mapDrawer );
    void update();
    // First mate implemetation:
    void turn( Waypoint& next );
    void move( Waypoint& next );
    bool needToTurn( Waypoint& next );
    bool needToMove( Waypoint& next );
};

#endif // ROBOT_CLASS_INCLUDED
