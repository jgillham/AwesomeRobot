#include "state.h"
#include "SDL.h"
#include "SDL_gfxPrimitives.h"
//#include "coords.h"

state::state()
{
    //variables
    x = 4; y = 4; z=.5; theta = 0;
    isCollided = false;
    x_dot = 0; y_dot = 0; theta_dot = .1; //expressed in ft/ms or deg/ms

    //constants
    float botHalfWidth = .5;
    float wheelHalfWidth = .05;
    float wheelRadius = .125;
    wheelAnchor.x = .5-.150;
    wheelAnchor.y = .5-.150;
}

state::~state()
{
    //dtor
}

void state::updatePose(void)
{
    x += x_dot; y += y_dot; theta+=theta_dot;
    if (theta > 360) {theta-=360;}
    if (theta < 0) {theta+=360;} //keep theta between 0 and 360 (wrap-around)
    if (.5>x || x>7.5 || .5>y || y>7.5) {isCollided = true;}
}

void state::readFromSensors(void)
{

}

void state::writeToMotors(void)
{

}

//drawMe needs some prototypes:
struct pt_B {public: float x, y;};
pt_B Bot_to_Board(float x_R, float y_R, float x_B, float y_B, float theta_B);
struct pt_S {public: short x, y;};
pt_S BoardToScreen(pt_B boardPt);
void DrawRay(SDL_Surface* board, float x_in_B, float y_in_B, float theta_in_B, float length, Uint32 color);

void state::drawMe(SDL_Surface* board, Uint32 color)
{
    //robot body:
    //float x_R[4] = {wheelAnchor.x, wheelAnchor.x, -wheelAnchor.x, -wheelAnchor.x};
    //float y_R[4] = {wheelAnchor.y, -wheelAnchor.y, -wheelAnchor.y, wheelAnchor.y};
    //float x_R[4] = {botHalfWidth, botHalfWidth, -botHalfWidth, -botHalfWidth};
    //float y_R[4] = {botHalfWidth, -botHalfWidth, -botHalfWidth, botHalfWidth};
    float x_R[4] = {.5, .5, -.5, -.5};
    float y_R[4] = {.5, -.5, -.5, .5};

    short x_S[4], y_S[4];
    int i; for (i=0; i<4; i++)
    {
        pt_B boardPt = Bot_to_Board(x_R[i], y_R[i], x, y, theta);
        pt_S screenPt = BoardToScreen(boardPt);
        x_S[i] = screenPt.x, y_S[i] = screenPt.y;
    }
    polygonColor(board, x_S, y_S, 4, color);
    //robot heading:
    DrawRay(board, x, y, theta, 1, color);
}
