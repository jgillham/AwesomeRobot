#ifndef GOSTATE_CLASS_INCLUDED
#define GOSTATE_CLASS_INCLUDED
#include "State.hpp"
class GoState : public State {
  private:
    double theta, x, y;

  public:
    GoState( double theta, double x, double y );
    void onBegin( FirstMate* firstMate );
    void onEnd();

};

#endif // GOSTATE_CLASS_INCLUDED

