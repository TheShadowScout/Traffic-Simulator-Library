#pragma once

#include "LaneEndsMerge.h"
#include "Obstacle.h"

class LaneEndsMergeL : public LaneEndsMerge {
protected:
    std::vector<Cell*> endingLaneL;

public:
    LaneEndsMergeL(int length, int height, int roadMaxSpeed);
    ~LaneEndsMergeL();
    Cell* getEndingLaneLHead();
    int getPassableCellsCnt();
    std::vector<Cell*> getCellsWithVehs();
    void fillWithVehs(double fillingDegree);
    std::string toString();
};