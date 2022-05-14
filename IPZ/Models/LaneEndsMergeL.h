#pragma once

#include "../Basic Classes/LaneEndsMerge.h"
#include "../Basic Classes/Obstacle.h"

class LaneEndsMergeL : public LaneEndsMerge {
protected:
    std::vector<Cell*> endingLaneL;

    void create();

public:
    LaneEndsMergeL(std::string name, int length, int height, int maxSpeed);
    LaneEndsMergeL(int length, int height, int maxSpeed);
    ~LaneEndsMergeL();
    Cell* getEndingLaneLHead();
    std::vector<std::vector<Cell*>> getEndingLanes();
    int getPassableCellsCnt();
    std::vector<Cell*> getCellsWithVehs();
    void fillWithVehs(double fillingDegree);
    std::string toString();
};