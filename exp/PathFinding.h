#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "Vector3.h"
#include "SearchCell.h"
#include <vector>


class PathFinding
{
    public:
        PathFinding();
        ~PathFinding();

        void FindPath(Vector3 currentPos, Vector3 targetPos);
        Vector3 NextPathPos();
        void ClearOpenList() {m_openList.clear();}
        void ClearVisitedList() { m_visitedList.clear();}
        void ClearPathToGoal() {m_pathToGoal.clear (); }
        bool m_initliazedStartGoal;
        bool m_foundGoal;

    private:
        void SetStartAndGoal(SearchCell start, SearchCell goal);
        void PathOpened(int x, int z, float newCost, SearchCell *parent); //is SeachCell open?
        SearchCell *GetNextCell(); //get the next available cell
        void ContinuePath();

        SearchCell *m_startCell;
        SearchCell *m_goalCell;
        std::vector<SearchCell*> m_openList;//a vector of searchcell pointers
        std::vector<SearchCell*> m_visitedList;
        std::vector<Vector3*> m_pathToGoal;
    protected:
    private:
};

#endif // PATHFINDING_H
