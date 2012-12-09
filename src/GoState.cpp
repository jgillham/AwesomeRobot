#include "GoState.hpp"

GoState::GoState( double theta, double x, double y ):
    theta( theta ), x( x ), y( y ) {

}

void GoState::onBegin( FirstMate* firstMate ) {
  firstMate->changePosition( theta, x, y );
}
void GoState::onEnd() {

}
