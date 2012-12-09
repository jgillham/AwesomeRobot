#include <math.h>

#include "Robot.hpp"
#define ROBOT_MAP_WIDTH 30
#define ROBOT_MAP_HEIGHT 60

Robot::Robot( State* state, int x, int y ): state( state ), x( x ), y( y ), mapTheta( 0 ) {
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

  mapDrawer->drawLine( 200+cornerTL_x, 200+cornerTL_y, 200+cornerTR_x, 200+cornerTR_y );
  mapDrawer->drawLine( 200+cornerTL_x, 200+cornerTL_y, 200+cornerBL_x, 200+cornerBL_y );
  mapDrawer->drawLine( 200+cornerBL_x, 200+cornerBL_y, 200+cornerBR_x, 200+cornerBR_y );
  mapDrawer->drawLine( 200+cornerBR_x, 200+cornerBR_y, 200+cornerTR_x, 200+cornerTR_y );

  mapDrawer->drawLine( 200, 200, 200+frontX, 200+frontY );
}
