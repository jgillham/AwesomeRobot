#pragma once
#include <math.h>

#define WORLD_SIZE 64

struct SearchCell
{
    public:
        int x_coord, z_coord;
        int m_id;
        SearchCell *parent;  //??  ASK DANE
        float G; //cost of path
        float H; //heuristic estimate = estimated distance to goal

        SearchCell() : parent(0)  {} //says {parent = 0;} - default parent is NULL
        SearchCell(int x, int z, SearchCell *_parent = 0) : m_xcoord(x), m_zcoord(z), parent(_parent), m_id(x*WORLD_SIZE + x), G(0), H(0);

        float GetF() {return G+H;} //F is heuristic
        float ManHattanDistance(SearchCell *nodeEnd)
        {
            float x = (float) (fabs(this->m_xcoord - nodeEnd->m_xcoord));
            float z = (float) (fabs(this->m_zcoord - nodeEnd->m_zcoord));
            return x+z;
        }

};

