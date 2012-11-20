#ifndef NODE_H
#define NODE_H


#include "SDL.h"
#include "SDL_gfxPrimitives.h"

class node
{
    public:
        float x, y, theta;
        int label;
        int neighbors[];

        void setNode(int label_in, float x_in, float y_in, float theta_in);
        void drawMe(SDL_Surface* screen);

        node();
        virtual ~node();
    protected:
    private:
};


#endif // NODE_H
