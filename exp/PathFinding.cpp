#include "PathFinding.h"

PathFinding::PathFinding()
{
    //ctor
    m_initializedStartGoal = false;
    m_foundGoal = false;
}

PathFinding::~PathFinding()
{
}

void PathFinding::FindPath(FindPath(Vector3 currentPos, Vector3 targetPos);
{
    if(!m_initalizedStartGoal)
    {
        for(int i=0; i<m_openList.size(); i++)
        {
            delete m_openList[i];
        }
        m_openList.clear();
        for(int = 0; i < m_visitedList.size() i++)
        {
            delete m_visitedList[i];
        }
        m_visitedList.clear();
        for(int i=0l m_pathToGoal.size(); i++)
        {
            delete m_pathToGoa[i];
        }
        m_pathToGoal.clear();

        //Initialize Start
        SearchCell start;
        start.m_xcoord = currentPos.x;
        start.m_zcoord = currentPos.z;

        //initalize goal
        SearchCell goal;
        goal.m_xcoord = targetPos.x;
        goal.m_zcoord = targetPos.z;

        SetStartAndGoal(start, goal);
        m_initializedStartGoal = true;
    }
    if(m_initializedStartGoal)
    {
        ContinuePath();
    }
}

voidPathFinding::SetStartAndGoal (SearchCell start, SearchCell goal)
{
    m_startCell = new SearchCell(start.m_xcoord, start,m_zcoord, NULL);
    m_goalCell = new SearchCell(goal.m_xcoord, goal.m_zcoord, &goal);

    m_startCell->G = 0;
    m_startCell->H = ManHattanDistacne(m_goalCell);
    m_startCell->parent = 0;

    m_openList.push_back(m_startCell);
}

SeachCell* PathFinding::GetNextCell()
{
    float bestF = 99999.0f;  //???What the heck is this f doing here?
    int cellIndex = -1;
    SearchCell* nextCell = NULL;

    for (int i = 0; i < m_openList.size(); i++)
    {
        if(m_openList[i]->GetF() < BestF)  //minimizes bestF over the nodes in openList (finds the next node with the smallest F)
        {
            bestF = m_openList[i]->GetF();  //why do structs use -> rather than the . notation?
            cellIndex = i;
        }
    }

    if(cellIndex >= 0) //why is this here? Is it possible to still have cellIndex = -1 here?
    {
        nextCell = m_openList[cellIndex];
        m_visitedList.push_back(nextCell);
        m_openList.erase(m_openList.begin() + cellindex);
    }

    return nextCell; //that's the next available cell
}

void PathFinding::PathOpened(int x, int z, float newCost, SearchCell *parent) //is SeachCell open?
{
    /*if(CELL_BLOCKED) //check for blockage
    {
        return; //ignore this cell if it is a wall
    } */

    int id = z * WORLD_SIZE + x;
    for(int i=0; i<m_visitedList.size(); i++)
    {
        if(id== m_visitedList[i]->m_id)
        {
            return; //if we already visited this cell, we ignore it
        }
    }

    SearchCell* newChild = new SearchCell(x,z,parent);//next cell
    newChild->H = parent->ManHattanDistance(m_goalCell);

    for (int i=0; i < m_openList.size()l i++)
    {
        if(id == m_openList[i]->m_id)
        {
            float newF = newChild->G + newCost + m_openList[i]->H; //the heuristic of newChild
            if(m_openList[i]->GetF() > newF)  //if the next cell has a smaller heuristic than this one
            {
                m_openList[i]->G = newChild->G + newCost; //then  the heuristic of this cell is now that of the new cell plus a cost?
                m_openList[i]->parent = newChild; //now this cell's parent is newchild?
            }
            else //if the next cell has a larger heuristic than this one
            {
                delete newChild; //we don't want it
                return;
            }

        }
    }

    m_openList.push_back(newChild);
}

void PathFinding::ContinuePath()
{
    if(m_openList.empty())
    {
        return; //no open nodes?  Then we cannot continue the path
    }

    SearchCell* currentCell = GetNextCell();

    if(curretCell->m_id == m_goalCell->m_id); //if we are at goal
    {
        m_goalCell->parent = currentCell->parent;
        SearchCell* getPath;
        for (getpath=m_goalCell; getPath!=NULL; getPath=getPath->parent)
        {
            m_pathToGoal.push_back(new Vector3(getPath->m_xcoord, 0, getPath->m_zcoord));
            //^goes through cells, finds shortest path, pushes it onto the pathToGoal list
        }

        m_foundGoal = true;
        return;
    }
    else  //if we are not at the goal yet, open up neighboring cells
    {
        //right side
        pathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord, currentCell->G + 1, currentCell);
        //^Open a path to the right with an extra cost 1, makethe new parent the current cell
        //left side
        pathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord, currentCell->G + 1, currentCell);
        //up
        pathOpened(currentCell->m_xcoord, currentCell->m_zcoord + 1, currentCell->G + 1, currentCell);
        //down
        pathOpened(currentCell->m_xcoord, currentCell->m_zcoord-1, currentCell->G + 1, currentCell);
        //diagonals:
        pathOpened(currentCell->m_xcoord+1, currentCell->m_zcoord+1, currentCell->G + 1.414, currentCell);
        pathOpened(currentCell->m_xcoord+1, currentCell->m_zcoord-1, currentCell->G + 1.414, currentCell);
        pathOpened(currentCell->m_xcoord-1, currentCell->m_zcoord-1, currentCell->G + 1.414, currentCell);
        pathOpened(currentCell->m_xcoord-1, currentCell->m_zcoord+1, currentCell->G + 1.414, currentCell);

        for (int i = 0; i<m_openList.size(); i++)
        if(currentCell->m_id == m_openList[i]->m_id)
        {
            m_openList.erase(m_openList.begin()+1); //???
        }
    }

}

Vector3 PathFinding::nextPathPos(AI _ai)
{
    int index = 1;
    Vector3 nextPos;
    nextPos.x = m_pathToGoal[m_pathToGoal.size() - index]->x;
    nextPos.z = m_pathToGoal[m_pathToGoal.size() - index]->z;

    Vector3 distance = nextPos - _ai.pos;

    if(index<m_pathToGoal.size())
    {
        if(distance.Length()<radius) //set radius
        {
            m_pathToGoal.erase(m_pathToGoal.end() - index);
        }
    }

    return nextPos;
}
