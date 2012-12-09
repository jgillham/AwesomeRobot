#include <math.h>

#include "Robot.hpp"
#define ROBOT_MAP_WIDTH 30
#define ROBOT_MAP_HEIGHT 60

Robot::Robot( State* state, int x, int y ):
    state( state ), x( x ), y( y ), mapTheta( 0 ),
    counter( 0 ), deltaX( 0 ), deltaY( 0 ), endCounter( -1 ) {
  state->onBegin( this );
}

void Robot::draw( MapDrawer* mapDrawer ) {

  double hWidth = ROBOT_MAP_WIDTH / 2;
  double hHeight = ROBOT_MAP_HEIGHT / 2;

  double frontLegth = hHeight * 1.5;
  double frontX = frontLegth * sin( this->mapTheta );
  double frontY = frontLegth * -cos( this->mapTheta );


  double radius = sqrt( hWidth * hWidth + hHeight * hHeight );

  //double cornerTL_x = -hWidth;
  //double cornerTL_y = -hHeight;
  double cornerTL_theta = atan( -hHeight / -hWidth );
  double cornerTL_x = radius * -cos( cornerTL_theta + this->mapTheta );
  double cornerTL_y = radius * -sin( cornerTL_theta + this->mapTheta );

  //double cornerTR_x = ROBOT_MAP_WIDTH / 2;
  //double cornerTR_y = -hHeight;
  double cornerTR_theta = atan( -hHeight / hWidth );
  double cornerTR_x = radius * -cos( cornerTR_theta + this->mapTheta );
  double cornerTR_y = radius * -sin( cornerTR_theta + this->mapTheta );

  //double cornerBL_x = -ROBOT_MAP_WIDTH / 2;
  //double cornerBL_y = hHeight;
  double cornerBL_theta = atan( hHeight / -hWidth );
  double cornerBL_x = radius * cos( cornerBL_theta + this->mapTheta );
  double cornerBL_y = radius * sin( cornerBL_theta + this->mapTheta );

  //double cornerBR_x = ROBOT_MAP_WIDTH / 2;
  //double cornerBR_y = ROBOT_MAP_HEIGHT / 2;
  double cornerBR_theta = atan( hHeight / hWidth );
  double cornerBR_x = radius * cos( cornerBR_theta + this->mapTheta );
  double cornerBR_y = radius * sin( cornerBR_theta + this->mapTheta );

  //mapDrawer->drawLine( x, y, x + ROBOT_MAP_WIDTH, y );
  //mapDrawer->drawLine( x, y, x, y + ROBOT_MAP_HEIGHT );
  //mapDrawer->drawLine( x, y + ROBOT_MAP_HEIGHT, x + ROBOT_MAP_WIDTH, y + ROBOT_MAP_HEIGHT );
  //mapDrawer->drawLine( x + ROBOT_MAP_WIDTH, y, x + ROBOT_MAP_WIDTH, y + ROBOT_MAP_HEIGHT );

  mapDrawer->drawLine( this->x+cornerTL_x, this->y+cornerTL_y, this->x+cornerTR_x, this->y+cornerTR_y );
  mapDrawer->drawLine( this->x+cornerTL_x, this->y+cornerTL_y, this->x+cornerBL_x, this->y+cornerBL_y );
  mapDrawer->drawLine( this->x+cornerBL_x, this->y+cornerBL_y, this->x+cornerBR_x, this->y+cornerBR_y );
  mapDrawer->drawLine( this->x+cornerBR_x, this->y+cornerBR_y, this->x+cornerTR_x, this->y+cornerTR_y );

  mapDrawer->drawLine( this->x, this->y, this->x+frontX, this->y+frontY );
}
#define THETA_RATE 0.5
#define MOVE_RATE 0.5
#define X_RATE 0.5
#define Y_RATE 0.5
void Robot::changePosition( double theta, double x, double y ) {
  this->deltaX = X_RATE;
  this->deltaY = Y_RATE;
  this->endCounter = this->counter + abs( x - this->x ) / this->deltaX;
}
void Robot::update() {
  this->x += this->deltaX;
  this->y += this->deltaY;
  this->mapTheta += this->deltaTheta;
  if ( this->endCounter > -1 &&
      this->counter > this->endCounter ) {
    this->deltaX = 0;
    this->deltaY = 0;
    this->deltaTheta = 0;
    this->endCounter = -1;
  }
  ++this->counter;
}
