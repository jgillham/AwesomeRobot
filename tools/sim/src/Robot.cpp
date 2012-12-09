#include <math.h>

#include "Robot.hpp"
#define ROBOT_MAP_WIDTH 30
#define ROBOT_MAP_HEIGHT 60
#define TURN_RATE 0.5
#define MOVE_RATE 0.5
#define SIGN( X ) ((x < 0) ? -1 : 1)
#define MIN( A, B ) ( A < B ? A : B )

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

  double cornerTL_theta = atan( -hHeight / -hWidth );
  double cornerTL_x = radius * -cos( cornerTL_theta + this->mapTheta );
  double cornerTL_y = radius * -sin( cornerTL_theta + this->mapTheta );

  double cornerTR_theta = atan( -hHeight / hWidth );
  double cornerTR_x = radius * -cos( cornerTR_theta + this->mapTheta );
  double cornerTR_y = radius * -sin( cornerTR_theta + this->mapTheta );

  double cornerBL_theta = atan( hHeight / -hWidth );
  double cornerBL_x = radius * cos( cornerBL_theta + this->mapTheta );
  double cornerBL_y = radius * sin( cornerBL_theta + this->mapTheta );

  double cornerBR_theta = atan( hHeight / hWidth );
  double cornerBR_x = radius * cos( cornerBR_theta + this->mapTheta );
  double cornerBR_y = radius * sin( cornerBR_theta + this->mapTheta );

  mapDrawer->drawLine( this->x+cornerTL_x, this->y+cornerTL_y, this->x+cornerTR_x, this->y+cornerTR_y );
  mapDrawer->drawLine( this->x+cornerTL_x, this->y+cornerTL_y, this->x+cornerBL_x, this->y+cornerBL_y );
  mapDrawer->drawLine( this->x+cornerBL_x, this->y+cornerBL_y, this->x+cornerBR_x, this->y+cornerBR_y );
  mapDrawer->drawLine( this->x+cornerBR_x, this->y+cornerBR_y, this->x+cornerTR_x, this->y+cornerTR_y );

  mapDrawer->drawLine( this->x, this->y, this->x+frontX, this->y+frontY );
}

void Robot::turn( double theta ) {
  double dif = theta - this->mapTheta;
  this->deltaTheta = SIGN( dif ) * MIN( TURN_RATE, abs( dif ) );
  this->deltaY = 0;
  this->deltaX = 0;
  this->endCounter = this->counter + abs( dif ) / TURN_RATE;
}
void Robot::move( double x, double y ) {
  double totalX = x - this->x;
  double totalY = y - this->y;
  double distance = sqrt( totalX * totalX + totalY * totalY );
  if ( distance < MOVE_RATE ) {
    this->deltaY = totalY;
    this->deltaX = totalX;
  }
  else {
    this->deltaY = totalY * ( MOVE_RATE / distance );
    this->deltaX = totalX * ( MOVE_RATE / distance );
  }
  this->deltaTheta = 0;
  this->endCounter = this->counter + distance / MOVE_RATE;
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
    this->state->onMove( this );
  }
  ++this->counter;
}
double Robot::calculateTheta( double x, double y ) {
  double totalX = x - this->x;
  double totalY = y - this->y;
  return atan( totalY / totalX );
}
