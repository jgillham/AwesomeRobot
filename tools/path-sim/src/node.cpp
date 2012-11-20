#include "node.h"


void DrawRay(SDL_Surface* board, float x_in_B, float y_in_B, float theta_in_B, float length, Uint32 color);

struct pt_S {public: short x, y;};
pt_S BoardToScreen(float x_board, float y_board);


node::node()
{
    x=0; y=0; theta=0;
}

node::~node()
{
    //dtor
}

void node::setNode(int label_in, float x_in, float y_in, float theta_in)
{
    label = label_in; x=x_in; y=y_in; theta=theta_in;
}

void node::drawMe(SDL_Surface* board)
{
    DrawRay(board, x, y, theta, .5, 0xFF8F00FF);
    DrawRay(board, x, y, theta + 90, .1, 0xFF8F00FF);
    DrawRay(board, x, y, theta + 180, .1, 0xFF8F00FF);
    DrawRay(board, x, y, theta + 270, .1, 0xFF8F00FF);
}
