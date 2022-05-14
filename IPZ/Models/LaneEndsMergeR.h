#pragma once

#include "../Basic Classes/LaneEndsMerge.h"
#include "../Basic Classes/Obstacle.h"

class LaneEndsMergeR : public LaneEndsMerge {
protected:
    std::vector<Cell*> endingLaneR;

    void create();

public:
    LaneEndsMergeR(std::string name, int length, int height, int maxSpeed);
    LaneEndsMergeR(int length, int height, int maxSpeed);
    ~LaneEndsMergeR();
    Cell* getEndingLaneRHead();
    std::vector<std::vector<Cell*>> getEndingLanes();
    int getPassableCellsCnt();
    std::vector<Cell*> getCellsWithVehs();
    void fillWithVehs(double fillingDegree);
    std::string toString();
};