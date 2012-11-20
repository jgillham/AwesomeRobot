#ifndef STATE_H
#define STATE_H

#include "SDL.h"
#include "SDL_gfxPrimitives.h"
//#include "coords.h"


class state
{
    public:
        //attributes:
        float x, y, z, theta;
        float x_dot, y_dot, z_dot, theta_dot;
        bool isCollided;

        //methods:
        void updatePose(void);
        void readFromSensors(void);
        void writeToMotors(void);
        void drawMe(SDL_Surface* board, Uint32 color);

        //constructor/destructor:
        state();
        virtual ~state();

                //here's where we keep parameters relating to the bot's dimensions:
        //they are expressed in half-lengths to slightly speed execution time and simplify notation
        float botHalfWidth;
        float wheelHalfWidth;
        float wheelRadius;
        struct pt_R{public: float x, y;} wheelAnchor;
    protected:

    private:
};

#endif // STATE_H
