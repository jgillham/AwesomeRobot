#ifndef FIRSTMATE_CLASS_INCLUDED
#define FIRSTMATE_CLASS_INCLUDED
#include "Waypoint.hpp"

class FirstMate  {
  public:
    virtual void turn( Waypoint& next ) = 0;
    virtual void move( Waypoint& next ) = 0;
    virtual bool needToTurn( Waypoint& next ) = 0;
    virtual bool needToMove( Waypoint& next ) = 0;
};

#endif // FIRSTMATE_CLASS_INCLUDED

