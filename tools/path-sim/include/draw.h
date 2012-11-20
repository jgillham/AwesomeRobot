//some functions that help with drawing:

void DrawRay(SDL_Surface* board, float x_in_B, float y_in_B, float theta_in_B, float length, Uint32 color)
{
    pt_B b_start, b_finish;
    b_start.x = x_in_B; b_start.y = y_in_B;
    b_finish.x = b_start.x + length*cos(theta_in_B*3.14159/180);
    b_finish.y = b_start.x + length*sin(theta_in_B*3.14159/180);

    pt_S s_start, s_finish;
    s_start = BoardToScreen(b_start);
    s_finish = BoardToScreen(b_finish);
    lineColor(board, s_start.x, s_start.y, s_finish.x, s_finish.y, color);
}
