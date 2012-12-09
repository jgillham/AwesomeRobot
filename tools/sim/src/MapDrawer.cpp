#include "MapDrawer.hpp"

MapDrawer::MapDrawer( SDL_Surface* surface ) {
  this->surface = surface;
  this->color = 0xFFFFFFFF;
}
void MapDrawer::setColor( uint color ){
  this->color = color;
}
void MapDrawer::drawLine( int x1, int y1, int x2, int y2 ) {
  lineColor( this->surface, x1, y1, x2, y2, this->color );
}

