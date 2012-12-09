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
  public:
    Robot( State* state, int x, int y );
    void draw( MapDrawer* mapDrawer );
    void turn( double theta );
    void move( double x, double y );
    double calculateTheta( double x, double y );
    void update();
};

#endif // ROBOT_CLASS_INCLUDED
