#ifndef STATE_CLASS_INCLUDED
#define STATE_CLASS_INCLUDED
#include "FirstMate.hpp"

class State {
  public:
    virtual void onBegin( FirstMate* firstMate ) = 0;
    virtual void onMove( FirstMate* firstMate ) = 0;
    virtual void onEnd() = 0;
};

#endif // STATE_CLASS_INCLUDED

