#include "SDL.h"
#include <stdlib.h> //for Rand()
#include "SDL_gfxPrimitives.h"//SDL_gfxPrimitives give me all the basic shapes I need
#include <math.h> //we will be doing LOTS of math
#include <time.h> //to seed rand()
#include <stdio.h>

#define PI 3.141579
#define SMALLERRORS 0 //set to 0 to turn off small errors


const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 700;
const char* WINDOW_TITLE = "Tugg Speedman Simulator v0";

SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0,
SDL_HWSURFACE | SDL_DOUBLEBUF );
bool gameRunning = true;
SDL_Event event;

int i,j,k;

//for now, only rocks...we'll look at trees later
const float X_RockCoords[7] = {1.44, 1.96, 2.24, 4.02, 4.07, 6.24, 7.70};
const float Y_RockCoords[7] = {.894, 2.98, 5.76, 6.96, 3.03, 1.74, 6.01};
const float RockRadius = .2981;

const float X_BotFrameCoords[4] = {   .5,   -.5,    -.5,     .5};  //y coords
const float Y_BotFrameCoords[4] = {.3333, .3333, -.3333, -.3333}; //bot base coords are in feet, in board frame.
float X_Bot = 4; //X_Bot is in feet, it is the x coord of the robot's mast axle -- a global var so we don't waste cycles calling it
                    //in the frame of the board
float Y_Bot = 4 ;//Y_Bot  "" ""
float theta_Bot = 0; // the orientation of the robot, in radians.  Expressed as inclination above x axis
float EchoDistances[360] = {12};  //An array of distances, in feet--initialize to huge

float D_Bot_FoundRocks[7] = {0}; //the distance to the nth rock
float Theta_BR_Bot_FoundRocks[7] = {0}; //the theta to the nth rock from heading


//a function to initialize SDL:
void initialize_SDL(void){
//intialize SDL, a toolkit which handles the graphics
    SDL_Init( SDL_INIT_VIDEO );

    //SDL_Surfaces* are bitmaps
        //SDL_SetVideoMode() makes an SDL_Surface with the right properties
        //for gfx to work its' magic

    SDL_WM_SetCaption( WINDOW_TITLE, 0 );

    //I don't use events in the code yet, but I bet I will later


    //This gives us a flag to halt the main loop
    gameRunning = true;
}

//here is a function that translate BotFrame_X, BotFrame_Y  to BoardFrame_X, BoardFrame_Y;
void Bot_to_Board(float BotFrame_X, float BotFrame_Y, float &BoardFrame_X, float &BoardFrame_Y){
    BoardFrame_X = BotFrame_X*cos(theta_Bot) - BotFrame_Y*sin(theta_Bot) + X_Bot;  //just apply rotation then translation
    BoardFrame_Y = BotFrame_X*sin(theta_Bot) + BotFrame_Y*cos(theta_Bot) + Y_Bot;
}

//here is a function that translate X_Board, Y_Board to X_SDL, Y_SDL (SDL frame is the screen frame)
void Board_to_SDL(float BoardFrame_X, float BoardFrame_Y, short &SDLFrame_X, short &SDLFrame_Y){
    SDLFrame_X = (short)(BoardFrame_X * 60) ;
    SDLFrame_Y = (short)((8-BoardFrame_Y) * 60);
}

//here is a subroutine that draws some window separators on the screen
void DrawLines(void){
     //a black line to separate the board window from the d vs Theta_bot graph
    for (i=0;i<900 ;i++)
    {
        pixelRGBA(screen, // draw a pixel on 'screen'
            i, 480,     //x, y of pixel (origin is upper left corner)
                        //here, we draw a line 448 pixels from the ceiling, separating the board window from the echo data window
            0xFF, 0xFF, 0xFF, 0xFF);  //color of pixel.  RGBalpha.  0xFF = opaque
    }
    //a black line to separate the board window from the numerics window
    lineRGBA(screen,
        480, 480, //start point
        480, 0, //end point
        0xFF, 0xFF, 0xFF, 255);    //color
    //a black line to separate the theta graph from...empty space?
    lineRGBA(screen,
        720, 480, //start point
        720, 700, //end point
        0xFF, 0xFF, 0xFF, 255);    //color
}

//a function that draws a ray--inputs are in board frame, theta is wrt x
void DrawRay(float X_origin, float Y_origin, float theta, int red, int green, int blue){
    short SDLFrame_X1, SDLFrame_X2, SDLFrame_Y1, SDLFrame_Y2;
    Board_to_SDL(X_origin, Y_origin, SDLFrame_X1, SDLFrame_Y1);
    Board_to_SDL(X_origin + 10*cos(theta), Y_origin + 10*sin(theta), SDLFrame_X2, SDLFrame_Y2);

    lineRGBA(screen,
               SDLFrame_X1, SDLFrame_Y1,
               SDLFrame_X2, SDLFrame_Y2,
               red, green, blue, 255);
}

//a function that draws a spoke of a specific length (in feet)
void DrawSpoke(float X_origin, float Y_origin, float theta, float length, int red, int green, int blue){
    short SDLFrame_X1, SDLFrame_X2, SDLFrame_Y1, SDLFrame_Y2;
    Board_to_SDL(X_origin, Y_origin, SDLFrame_X1, SDLFrame_Y1);
    Board_to_SDL(X_origin + length*cos(theta), Y_origin + length*sin(theta), SDLFrame_X2, SDLFrame_Y2);

    lineRGBA(screen,
               SDLFrame_X1, SDLFrame_Y1,
               SDLFrame_X2, SDLFrame_Y2,
               red, green, blue, 255);
}

//A sub that draws the robot's avatar, based on theta_Bot, X_Bot, Y_Bot
void DrawBot(){
    //draw spokes
    for (i=0; i<360; i++)
    {
        DrawSpoke(X_Bot, Y_Bot, theta_Bot + (float)i/360*2*PI, EchoDistances[i], 0, 52, 0);
    }

    // Draw percieved rock vectors
    for (i=0; i<7; i++)
    {
        if (D_Bot_FoundRocks[i] != 0)
        {
            DrawSpoke(X_Bot, Y_Bot, Theta_BR_Bot_FoundRocks[i]+theta_Bot, D_Bot_FoundRocks[i],
                      0xFF,0xFF,0xFF);
        }
    }

    //robot body:
    float x_float[4];
    float y_float[4];
    short x[4]; //these are the corners of the bot, as displayed on the screen
    short y[4];
    for (i=0; i<4; i++)
    {
        Bot_to_Board(X_BotFrameCoords[i], Y_BotFrameCoords[i], x_float[i],y_float[i]);
        Board_to_SDL(x_float[i], y_float[i], x[i], y[i]);
    }

    polygonRGBA(screen,
                  x, y,
                  4,  //number of sides?
                  00, 255, 255, 155);

    //robot heading line:
    DrawRay(X_Bot, Y_Bot, theta_Bot, 255,0,0);
}

//A sub that changes X_Bot, Y_Bot, and theta to random parameters (with crude collision avoidance)
void RandomizeBot(void){
    bool tooClose=true;
    while (tooClose)
    {
        //(theta_Bot is defined as theta_board - theta_bot, where _theta_Bot is the angle the bot is pointing
        X_Bot = (float)rand()/RAND_MAX * 7 + .5;
        Y_Bot = (float)rand()/RAND_MAX * 7 + .5;
        theta_Bot = (float)rand()/RAND_MAX * 2*PI; //make it random

        tooClose = false;
        //check if we're too close
        for (i=0; i<=7;i++)
        if (pow(X_RockCoords[i]-X_Bot,2)+pow(Y_RockCoords[i]-Y_Bot,2)<RockRadius+.3){tooClose=true;}
    }
}

//A sub that draws trees
void DrawTreesAndRocks(void){
    for (i=0; i<7; i++)
    {
        short x,y;
        short r = RockRadius /8 * 480;
        Board_to_SDL(X_RockCoords[i], Y_RockCoords[i],x,y);
        ellipseRGBA(screen,
            x,y,  //center
            r, r,  //semimajor axes (we use as radii)
            155, 155, 0, 200); //color--I opt for brown
    }
}

//A sub that displays bars on range vs. Theta graph
void DrawRangeGraph(){
    for (i=0; i<360; i++){
        lineRGBA(screen,
            i*2, 700, //start point is bottom of screen, moving right
            i*2, 700-(EchoDistances[i]/11.3*220), //end point is directly above start, and can be 0 to 220 pixels above
            0, 0xFF, 0, 255);    //color - green
    }
}

//A sub that calculates echodistances
void CalcEchoDistances(){
    //first, set EchoDistances high:
    for (i=0; i<360; i++)
    {
        EchoDistances[i] = 9.8; //9.8 is the maximum accurate rangefind of PING)))
        //EchoDistances[i] = (float)i*5/360;
    }
    //now we start whittling out chunks

    for (i=0; i<7;i++)
    {
        float delta_X = X_RockCoords[i]-X_Bot;
        float delta_Y = Y_RockCoords[i]-Y_Bot;
        float theta_Rock = atan2(delta_Y,delta_X); //must use atan2 to avoid sign errors
        if (theta_Rock<0){theta_Rock += 2*PI;}
        float theta_BR = theta_Rock-theta_Bot;
        if (theta_BR<0){theta_BR += 2*PI;}
        float d = sqrt( pow(delta_X,2) + pow(delta_Y,2) ); //pythagoran theorem to get true distance to rock

        for (j=0;j<360; j++)
        {
            float theta_e; //theta_e for echo.  This is the degrees between thetabot and the echolocator
            theta_e = (float)j/360 * 2 * PI;
            float range_rock;
            float Lim = asin(RockRadius/d);
            if ((theta_BR - Lim < theta_e || theta_e < Lim)
                && (theta_e < theta_BR + Lim || theta_e > 2*PI-Lim)) //whew!  This long condition is surely a source of error
            {
                range_rock = d*(cos(theta_e-theta_BR)-sqrt(pow(RockRadius/d,2)-pow(sin(theta_e-theta_BR), 2)));
                //range_rock = d;
                if (range_rock < EchoDistances[j]){EchoDistances[j]=range_rock;}
                if (SMALLERRORS)
                {
                    EchoDistances[j] += (float)rand()/RAND_MAX*.13 - .065;
                }
            }
        }
    }
}

//A sub that prints errors in the found rocks vector to the terminal
void PrintRockVectorError(void){
    printf("\n\n");

    for (i=0; i<7; i++) //one for each real rock
    {
            float MinWrongD = 100;
            float MinWrongTheta = 100;
            //this next bit copied from CalcEchoDistances -- should make function instead?
            float delta_X = X_RockCoords[i]-X_Bot;
            float delta_Y = Y_RockCoords[i]-Y_Bot;
            float theta_Rock = atan2(delta_Y,delta_X); //must use atan2 to avoid sign errors
            if (theta_Rock<0){theta_Rock += 2*PI;}
            float real_theta_BR = theta_Rock-theta_Bot;
            if (real_theta_BR<0){real_theta_BR += 2*PI;}
            float real_d = sqrt( pow(delta_X,2) + pow(delta_Y,2) ); //pythagoran theorem to get true distance to rock

            for (j=0; j<7; j++) //one for each percieved rock
            {
                if (fabs(real_d-D_Bot_FoundRocks[j]) < MinWrongD) {MinWrongD = fabs(real_d-D_Bot_FoundRocks[j]);}
                if (fabs(real_theta_BR-Theta_BR_Bot_FoundRocks[j]) < MinWrongTheta)
                    {MinWrongTheta = fabs(real_theta_BR-Theta_BR_Bot_FoundRocks[j]);}
            }
            printf("Error for tree %d :  d = %10.3f, theta = %10.3f \n", i, MinWrongD, MinWrongTheta*real_d);
    }
}

//A sub that uses EchoDistances[] to find the nearby rocks
void Bot_FindRocks(void){

    D_Bot_FoundRocks = {0};
    Theta_BR_Bot_FoundRocks = {0};
    int runThru = 360; //we declare the limits with a variable in case we start in a rock and need to rerun part
    int thisRock_Angle = 0; //the angle subtended by this rock in degrees
    bool inRock = 0; //if we are (or believe we are) in a rock
    bool startInRock =0;
    int rockCount = 0;  //how many rocks have we seen so far?
    if (EchoDistances[0] < 8) //8 is about as far as we can get from a rock
        {startInRock = 1;}
    int i_minusone;
    float thisRock_DSum = 0; //to keep a rolling sum of our distances
    for (j=0; j<runThru; j++) //this one is a little weird...
                    //we need to use 2 counting vars so that we can wrap around 360 if we start in rock
    {
        i = j%360; //see?  wrapping around
        //if (startInRock == 1){runThru++;} //if we start in rock, we're going to have to re-analyze that bit later
        //if (runThru == 480) {startInRock=0;} //some bugs cause endless loops, this breaks them
        if (i==0){i_minusone = 359;} else {i_minusone = i-1;}
        if (EchoDistances[i_minusone] - EchoDistances[i] > 1 && EchoDistances[i] < 8) //no two rocks are w/in 2 foot of each other, so this
            //should distinguish between rocks--this means we've started looking at a new rock
        {
            thisRock_Angle=0; //we just started on a new rock
            inRock = 1;
            thisRock_DSum = 0;
            DrawRay(X_Bot, Y_Bot, (float)i/360*2*PI + theta_Bot, 222,222,222);
        }
        if (EchoDistances[i_minusone] - EchoDistances[i] < -1 && inRock == 1) //now we're done looking at that rock
        {
            inRock = 0;
            startInRock=0;

            float Bot_theta_BR; //the angle the robot thinks is between its heading and the rock
            float Bot_distance; //the distance the robot thinks the rock is away
            Bot_distance = (float)thisRock_DSum/thisRock_Angle + .785*RockRadius; //why .785? it's PI/4.  why PI/4? Ask Max
            Bot_theta_BR = (float)(i - 1 - (thisRock_Angle / 2))/360 *2 * PI; //Bot_theta is in radians

            D_Bot_FoundRocks[rockCount] = Bot_distance;
            Theta_BR_Bot_FoundRocks[rockCount] = Bot_theta_BR;
            rockCount++;

            DrawRay(X_Bot, Y_Bot, (float)(i-1)/360*2*PI + theta_Bot, 222,222,222);
        }
        if (inRock)
        {
            thisRock_Angle++;
            thisRock_DSum += EchoDistances[i];
        }
    }
    PrintRockVectorError();
}

//-------------------------------------MAIN------------------------------------------
//-----------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    initialize_SDL(); //gotta initialize SDL

    srand(time(NULL));


    RandomizeBot();
    CalcEchoDistances();
    Bot_FindRocks();

    while (gameRunning) //the main loop
    {
        //event checker:
        if (SDL_PollEvent(&event)){
            //SDL_PollEvent will return 1 if the targeted event has occured
            if (event.type == SDL_QUIT) //quit if we made event an SDL_QUIT event.
            {
                gameRunning = false;
            }
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_r:
                        RandomizeBot();
                        CalcEchoDistances();
                        Bot_FindRocks();
                        break;
                }
            }
        }

        //the event checker likely changed the worldstate, so we need to recalculate



        //Here's where we draw:

        //First let's make a black background
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        //now we lay out the screen
        DrawLines();



        DrawBot();
        DrawTreesAndRocks();
        DrawRangeGraph();

      SDL_Flip(screen);
   }

   SDL_Quit();

   return 0;
}
