/// Author: Josh Gillham
/// Date: 12-9-12
/// Description:
///  Holds the methods for the GoState class.
///
#include "GoState.hpp"

/**
 * Initializes class variables.
 *
 * @param path is the list of Waypoints for the
 *  robot to move through.
 */
GoState::GoState( std::vector< Waypoint* >* path ):
    path( path ) {
}

/**
 * Called to get the state started. Tells the robot to
 *  move towards the next point.
 *
 * @param firstMate the pointer to the First Mate.
 */
void GoState::onBegin( FirstMate* firstMate ) {
  if ( !this->path->empty() ) {
    Waypoint& next = *this->path->back();
    //this->onTurn( firstMate );
    firstMate->turn( next );
    //firstMate->move( next );
  }
}

/**
 * Decides which action will be appropriate to bring the
 *  robot closer to its target. It must choose between a
 *  move and a turn. The first mate will give it solid
 *  advice as to which move will be appropriate.
 *
 * @param firstMate the pointer to the firstMate.
 *
 * @return TRUE if the robot has reached the next waypoint
 *  OR FALSE if the robot will be changing its pose.
 */
bool GoState::goToNextPoint( FirstMate* firstMate ) {
  if ( !this->path->empty() ) {
    Waypoint& next = *this->path->back();
    if ( firstMate->needToTurn( next ) ) {
      firstMate->turn( next );
    }
    else if ( firstMate->needToMove( next ) ) {
      firstMate->move( next );
    }
    else return true;
  }
  else return true;
  return false;
}

/**
 * Called when the first mate thinks the turn has
 *  been completed.
 *
 * @param firstMate the pointer to the first mate.
 */
void GoState::onTurn( FirstMate* firstMate ) {
  if ( !this->path->empty() ) {
    Waypoint& next = *this->path->back();
    firstMate->move( next );
  }
}

/**
 * Called when the first mate thinks the move has
 *  been completed.
 *
 * @param firstMate the pointer to the first mate.
 */
void GoState::onMove( FirstMate* firstMate ) {
  if ( !this->path->empty() ) {
    this->path->pop_back();
  }
  if ( !this->path->empty() ) {
    Waypoint& next = *this->path->back();
    firstMate->turn( next );
  }
}

/**
 * Called right before the state ends.
 */
void GoState::onEnd() {
  // Prepare for next state.
}
