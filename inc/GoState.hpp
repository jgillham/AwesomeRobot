#ifndef GOSTATE_CLASS_INCLUDED
#define GOSTATE_CLASS_INCLUDED
#include "State.hpp"
#include <vector>
#include "Waypoint.hpp"
class GoState : public State {
  private:
    double theta, x, y;
    std::vector< Waypoint* >* path;

    void goToNextPoint( FirstMate* firstMate );

  public:
    GoState( std::vector< Waypoint* >* path );
    void onBegin( FirstMate* firstMate );
    void onMove( FirstMate* firstMate );
    void onEnd();

};

#endif // GOSTATE_CLASS_INCLUDED

