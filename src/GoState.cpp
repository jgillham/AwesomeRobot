#include "GoState.hpp"


GoState::GoState( std::vector< Waypoint* >* path ):
    path( path ) {

}

void GoState::onBegin( FirstMate* firstMate ) {
  if ( !this->path->empty() ) {
    Waypoint& next = *this->path->back();
    //this->onTurn( firstMate );
    firstMate->turn( next );
    //firstMate->move( next );
  }
}

//bool needToTurn( FirstMate* firstMate, Waypoint* next ) {
//  double pathTheta = firstMate->calculateTheta( next->x, next->y );
//  double needTheta = pathTheta - firstMate->getHeading();
//  if ( THETA_TOLORANCE < ABS( needTheta ) ) {
//    firstMate->turn( pathTheta );
//    return false;
//  } else {
//    firstMate->move( next->x, next->y );
//  }
//}
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
//  if ( !this->path->empty() ) {
//    Waypoint* next = this->path->back();
//    if ( needToTurn( firstMate, next ) ) {
//      firstMate->turn( pathTheta );
//    } else {
//      firstMate->move( next->x, next->y );
//    }
//  }
//}
void GoState::onTurn( FirstMate* firstMate ) {
  if ( !this->path->empty() ) {
    Waypoint& next = *this->path->back();
    firstMate->move( next );
  }
}
void GoState::onMove( FirstMate* firstMate ) {
  if ( !this->path->empty() ) {
    this->path->pop_back();
  }
  if ( !this->path->empty() ) {
    Waypoint& next = *this->path->back();
    firstMate->turn( next );
  }
//  if ( !this->path->empty() ) {
//    if ( this->goToNextPoint( firstMate ) ) {
//      this->path->pop_back();
//      this->onMove( firstMate );
//    }
//  }
}
//    if ( needToTurn( firstMate, next ) ) {
//      firstMate->turn( pathTheta );
//    } else {
//      firstMate->move( next->x, next->y );
//    }
//    if ( this->arriveAtNext( firstMate, back ) ) {
//      this->path->pop_back();
//      this->onMove( firstMate );
//    }
//  }
//}
void GoState::onEnd() {

}
