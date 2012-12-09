#ifndef MAP_DRAWER_CLASS_INCLUDED
#define MAP_DRAWER_CLASS_INCLUDED
#include "SDL_gfxPrimitives.h"
class MapDrawer {
  private:
    typedef unsigned int uint;
    SDL_Surface* surface;
    uint color;
  public:
    MapDrawer( SDL_Surface* surface );
    void setColor( uint color );
    void drawLine( int x1, int y1, int x2, int y2 );
};

#endif // MAP_DRAWER_CLASS_INCLUDED

