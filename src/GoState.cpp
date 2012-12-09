#include "GoState.hpp"

GoState::GoState( std::vector< Waypoint* >* path ):
    path( path ) {

}

void GoState::onBegin( FirstMate* firstMate ) {
  //firstMate->changePosition( theta, x, y );
  this->goToNextPoint( firstMate );
}

void GoState::goToNextPoint( FirstMate* firstMate ) {
  if ( !this->path->empty() ) {
    Waypoint* node = this->path->back();
    firstMate->move( node->x, node->y );
  }
}

void GoState::onMove( FirstMate* firstMate ) {
  if ( !this->path->empty() ) {
    this->path->pop_back();
  }
  goToNextPoint( firstMate );
}
void GoState::onEnd() {

}
