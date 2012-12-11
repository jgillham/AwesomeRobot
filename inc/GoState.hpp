#ifndef GOSTATE_CLASS_INCLUDED
#define GOSTATE_CLASS_INCLUDED
  // Needed for base.
#include "State.hpp"
  // Needed for path.
#include <vector>
  // Needed for path.
#include "Waypoint.hpp"
/**
 * Handles events when the robot is in the movement
 *  phase of its operation. Each method inherited
 *  from the State class will be an event that
 *  occurs during this phase. Private methods provide
 *  assistance with duplicate operations.
 *
 * @author Josh Gillham
 * @version 12-9-12
 */
class GoState : public State {
  private:
    /** Holds the angle and coordinate. */
    double theta, x, y;
    /** Holds the list of waypoints.*/
    std::vector< Waypoint* >* path;
    /** Helps the robot get to the next pose. */
    bool goToNextPoint( FirstMate* firstMate );

  public:
    /** Initializes local variables. */
    GoState( std::vector< Waypoint* >* path );
    /** Called to start up the state. */
    void onBegin( FirstMate* firstMate );
    /** Called after the move has been completed. */
    void onMove( FirstMate* firstMate );
    /** Called after the turn has been completed. */
    void onTurn( FirstMate* firstMate );
    /** Called right before the state ends. */
    void onEnd();
};
#endif // GOSTATE_CLASS_INCLUDED
