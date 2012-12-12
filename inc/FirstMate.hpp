#ifndef FIRSTMATE_CLASS_INCLUDED
#define FIRSTMATE_CLASS_INCLUDED
#include "Waypoint.hpp"
/**
 * FirstMate is responsible for giving advice to the state
 *  and passing down requests from the state. His functions
 *  tell the state what position the robot is in.
 *
 * @author Josh Gillham
 * @version 12-9-12
 */
class FirstMate  {
  public:
    /** Passes the request down to turn. */
    virtual void turn( Waypoint& next ) = 0;
    /** Passes the request down to move. */
    virtual void move( Waypoint& next ) = 0;
    /** Checks to see if a turn is needed. */
    virtual bool needToTurn( Waypoint& next ) = 0;
    /** Checks to see if a move is needed. */
    virtual bool needToMove( Waypoint& next ) = 0;
    /** Tells the first mate to change the state. */
    virtual void signalEndState() = 0;
};
#endif // FIRSTMATE_CLASS_INCLUDED
