#include <math.h>

struct pt_B {public: float x, y;};
pt_B B(float x, float y)
{
    pt_B temp;
    temp.x = x; temp.y = y;
    return temp;
}

struct pt_R {public: float r, theta, x, y;};
pt_R R_cart(float x, float y)
{
    pt_R temp;
    temp.x = x; temp.y =y;
    temp.r = sqrt(pow(x,2) + pow(y,2));
    temp.theta = atan2(y,x);
    return temp;
}

struct pt_S {public: short x, y;};
pt_S S(short x, short y)
{
    pt_S temp;
    temp.x = x;
    temp.y = y;
    return temp;
}

pt_S BoardToScreen(pt_B boardPt)
{
    pt_S screenPt;
    screenPt.x = (short)(boardPt.x * 60);
    screenPt.y = (short)((8-boardPt.y) * 60);
    return screenPt;
}

pt_S BoardToScreen(float x_board, float y_board)
{
    pt_S screenPt;
    screenPt.x = (short)(x_board * 60);
    screenPt.y = (short)((8-y_board) * 60);
    return screenPt;
}

pt_B ScreenToBoard(pt_S screenPt)
{
    pt_B boardPt;
    boardPt.x = (float)(screenPt.x/60);
    boardPt.y = (float)((480-screenPt.y)/60);
    return boardPt;
}

//here is a function that translate BotFrame_X, BotFrame_Y  to BoardFrame_X, BoardFrame_Y;
pt_B Bot_to_Board(float x_R, float y_R, float x_B, float y_B, float theta_B)
{
    pt_B boardPt;
    boardPt.x = x_R*cos(theta_B*3.14159/180) - y_R*sin(theta_B*3.14159/180) + x_B;  //just apply rotation then translation
    boardPt.y = x_R*sin(theta_B*3.14159/180) + y_R*cos(theta_B*3.14159/180) + y_B;
    return boardPt;
}
/*
//here is a function that translate X_Board, Y_Board to X_SDL, Y_SDL (SDL frame is the screen frame)
void Board_to_SDL(float BoardFrame_X, float BoardFrame_Y, short &SDLFrame_X, short &SDLFrame_Y){
    SDLFrame_X = (short)(BoardFrame_X * 60) ;
    SDLFrame_Y = (short)((8-BoardFrame_Y) * 60);}*/
