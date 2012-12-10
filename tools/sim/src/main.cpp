//standard libraries:
#include <stdlib.h>

//SDL libraries:
#include <SDL.h>
#include "SDL_gfxPrimitives.h"

#include "Map.hpp"
#include "Robot.hpp"
#include "GoState.hpp"

#include <vector>
#include "Waypoint.hpp"

//global constants:
const int SCREEN_W = 915;
const int SCREEN_H = 715;
const char* WINDOW_TITLE = "Robot Simulator";

void drawWaypoints( MapDrawer* mapDrawer, std::vector< Waypoint* >* path, double nodeAnimationTheta );

int main(int argc, char **argv) {
    //set up our main SDL objects:
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
    SDL_WM_SetCaption( WINDOW_TITLE, 0 );
    SDL_Event event;
    std::vector< Waypoint* >* path = new std::vector< Waypoint* >();
    path->push_back( new Waypoint{ 1.4, 500, 250 } );
    path->push_back( new Waypoint{ 1.4, 400, 400 } );
    path->push_back( new Waypoint{ 1.4, 200, 300 } );
    path->push_back( new Waypoint{ 1.4, 300, 150 } );
    bool gameRunning = true; //lets us exit the game loop
    GoState* goState = new GoState( path );
    Robot* robot = new Robot( goState, 100, 100 );
    MapDrawer* drawer = new MapDrawer( screen );

    double nodeAnimationTheta = 0;



    while (gameRunning) { //the game loop
        //event checker:
        if (SDL_PollEvent(&event)) { //SDL_PollEvent will return 1 if the targeted event has occured
            //quit if we made event an SDL_QUIT event.
            if (event.type == SDL_QUIT) {
                gameRunning = false;
            }
        }

        //clear surfaces background:
        SDL_FillRect(screen, NULL, 0x0);
        drawWaypoints( drawer, path, nodeAnimationTheta );
        robot->draw( drawer );
        robot->update();

        SDL_Flip(screen);
        nodeAnimationTheta+=0.01;
    }

    SDL_Quit();
    return 0;
}

void drawWaypoints( MapDrawer* mapDrawer, std::vector< Waypoint* >* path, double nodeAnimationTheta ) {
  for( std::vector< Waypoint* >::iterator i = path->begin(); i != path->end(); ++i ) {


  double hWidth = 10;
  double hHeight = 10;


  double radius = sqrt( hWidth * hWidth + hHeight * hHeight );

  //double cornerTL_x = -hWidth;
  //double cornerTL_y = -hHeight;
  double cornerTL_theta = atan( -hHeight / -hWidth );
  double cornerTL_x = radius * -cos( cornerTL_theta + nodeAnimationTheta );
  double cornerTL_y = radius * -sin( cornerTL_theta + nodeAnimationTheta );

  //double cornerTR_x = ROBOT_MAP_WIDTH / 2;
  //double cornerTR_y = -hHeight;
  double cornerTR_theta = atan( -hHeight / hWidth );
  double cornerTR_x = radius * -cos( cornerTR_theta + nodeAnimationTheta );
  double cornerTR_y = radius * -sin( cornerTR_theta + nodeAnimationTheta );

  //double cornerBL_x = -ROBOT_MAP_WIDTH / 2;
  //double cornerBL_y = hHeight;
  double cornerBL_theta = atan( hHeight / -hWidth );
  double cornerBL_x = radius * cos( cornerBL_theta + nodeAnimationTheta );
  double cornerBL_y = radius * sin( cornerBL_theta + nodeAnimationTheta );

  //double cornerBR_x = ROBOT_MAP_WIDTH / 2;
  //double cornerBR_y = ROBOT_MAP_HEIGHT / 2;
  double cornerBR_theta = atan( hHeight / hWidth );
  double cornerBR_x = radius * cos( cornerBR_theta + nodeAnimationTheta );
  double cornerBR_y = radius * sin( cornerBR_theta + nodeAnimationTheta );

  //mapDrawer->drawLine( x, y, x + ROBOT_MAP_WIDTH, y );
  //mapDrawer->drawLine( x, y, x, y + ROBOT_MAP_HEIGHT );
  //mapDrawer->drawLine( x, y + ROBOT_MAP_HEIGHT, x + ROBOT_MAP_WIDTH, y + ROBOT_MAP_HEIGHT );
  //mapDrawer->drawLine( x + ROBOT_MAP_WIDTH, y, x + ROBOT_MAP_WIDTH, y + ROBOT_MAP_HEIGHT );

  mapDrawer->drawLine( (*i)->x+cornerTL_x, (*i)->y+cornerTL_y, (*i)->x+cornerTR_x, (*i)->y+cornerTR_y );
  mapDrawer->drawLine( (*i)->x+cornerTL_x, (*i)->y+cornerTL_y, (*i)->x+cornerBL_x, (*i)->y+cornerBL_y );
  mapDrawer->drawLine( (*i)->x+cornerBL_x, (*i)->y+cornerBL_y, (*i)->x+cornerBR_x, (*i)->y+cornerBR_y );
  mapDrawer->drawLine( (*i)->x+cornerBR_x, (*i)->y+cornerBR_y, (*i)->x+cornerTR_x, (*i)->y+cornerTR_y );
  }
}
