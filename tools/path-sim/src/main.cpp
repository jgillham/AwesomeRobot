/*this is version 1.1 of the Best Robot simulator
//by Max Lichtenstein

//please read the README file attached for an overview of the program
*/

//standard libraries:
#include <stdlib.h>
//SDL libraries:
#include <SDL.h>

#include "SDL_gfxPrimitives.h"
//class headers:
#include "state.h"
#include "node.h"
//custom libraries:
#include "apply_surface.h" //used for SDL blitting
#include "coords.h"
#include "draw.h"


#include "nodeList.h"

//some typedefs:
typedef int Wire_In;
typedef int Wire_Out;

//global constants:
const int SCREEN_W = 915;
const int SCREEN_H = 715;
const int BOARD_W = 480;
const int BOARD_H = 480;
const int GRAPH_W = 720;
const int GRAPH_H = 260;
const int STACK_W = 420;
const int STACK_H = 480;
const char* WINDOW_TITLE = "The Best Robot v1.2";

int i, j, k;  //counting vars

int main(int argc, char **argv)
{
    //set up our main SDL objects:
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
    SDL_Surface* board = SDL_CreateRGBSurface(0, BOARD_W, BOARD_H, screen->format->BitsPerPixel, 0, 0, 0, 0);
    SDL_Surface* graph = SDL_CreateRGBSurface(0, GRAPH_W, GRAPH_H, screen->format->BitsPerPixel, 0, 0, 0, 0);
    SDL_Surface* stack = SDL_CreateRGBSurface(0, STACK_W, STACK_H, screen->format->BitsPerPixel, 0, 0, 0, 0);  //WILL IMPLEMENT LATER
    SDL_WM_SetCaption( WINDOW_TITLE, 0 );
    SDL_Event event;
    bool gameRunning = true; //lets us exit the game loop

    //world objects

    state RealBot;
    state PercBot;
    int numHypoBots = 10;
    state HypoBot[numHypoBots];
    node Node[99];
    fillNodes(Node);

    while (gameRunning) //the game loop
    {
        //------------------------  (a) USER INPUT---------------------------------
        //event checker:
        if (SDL_PollEvent(&event)) //SDL_PollEvent will return 1 if the targeted event has occured
        {
            //quit if we made event an SDL_QUIT event.
            if (event.type == SDL_QUIT) {gameRunning = false;}
        }

    //------------------------  (b) ADVANCE ROBOT POSES + CONFIGURATIONS-------
            //take data from Wire Inputs:
            //Increment pose + config:
        RealBot.updatePose();
    //------------------------  (c) UPDATE ROBOT SENSOR SIGNALS ---------------
            //take data from Wire Inputs, put in robot's state
    //------------------------  (d) ROBOT MAIN LOOP ---------------------------
            //the entire Robot Main Loop is kept in an include file:
        #include "r_main.h"

    //------------------------  (e) UPDATE ROBOT MOTOR SIGNALS-----------------
    //------------------------  (f) DRAW TO SCREEN ----------------------------
        //clear surfaces background:
        SDL_FillRect(screen, NULL, 0xFFFFFFFF);
        SDL_FillRect(board, NULL, 0xFF000000);
        //draw the board:
        RealBot.drawMe(board, 0xFFFFFFFF);
        for (i=0; i<sizeof(Node)/sizeof(node);i++)
        {
            j=sizeof(Node)/sizeof(node);
            Node[i].drawMe(board);
        }
        //apply the surfaces:
        apply_surface(5,5, board, screen);
        apply_surface(5, BOARD_H + 10, graph, screen);
        apply_surface(BOARD_W + 10, 5, stack, screen);
        //flip:
        SDL_Flip(screen);
   }

   SDL_Quit();
   return 0;
}
