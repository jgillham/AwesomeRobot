#ifndef ROBOT_CLASS_INCLUDED
#define ROBOT_CLASS_INCLUDED
#include "MapDrawer.hpp"
#include "State.hpp"
/**
 * The robot class handles drawing the robot.
 */
class Robot {
  private:
    int x, y;
    double mapTheta;
    State* state;
  public:
    Robot( State* state, int x, int y );
    void draw( MapDrawer* mapDrawer );
};

#endif // ROBOT_CLASS_INCLUDED
