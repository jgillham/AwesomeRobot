#ifndef STATE_CLASS_INCLUDED
#define STATE_CLASS_INCLUDED
#include "FirstMate.hpp"
/**
 * State is an interface for any robot state. It has
 *  methods that will be called by the first mate to
 *  signal events.
 *
 * @author Josh Gillham
 * @version 12-9-12
 */
class State {
  public:
    /** Called when the state is getting started. */
    virtual void onBegin( FirstMate* firstMate ) = 0;
    /** Called when the move has been completed. */
    virtual void onMove( FirstMate* firstMate ) = 0;
    /** Called when the turn has been completed. */
    virtual void onTurn( FirstMate* firstMate ) = 0;
    /** Called right before the state ends. */
    virtual void onEnd() = 0;
};
#endif // STATE_CLASS_INCLUDED
