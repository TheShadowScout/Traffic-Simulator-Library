#pragma once

#include "../Basic Classes/LaneEndsMerge.h"
#include "../Basic Classes/Obstacle.h"

class LaneEndsMergeLR : public LaneEndsMerge {
protected:
    std::vector<Cell*> endingLaneL;
    std::vector<Cell*> endingLaneR;

    void create();

public:
    LaneEndsMergeLR(std::string name, int length, int height, int maxSpeed);
    LaneEndsMergeLR(int length, int height, int maxSpeed);
    ~LaneEndsMergeLR();
    Cell* getEndingLaneLHead();
    Cell* getEndingLaneRHead();
    std::vector<std::vector<Cell*>> getEndingLanes();
    int getPassableCellsCnt();
    std::vector<Cell*> getCellsWithVehs();
    void fillWithVehs(double fillingDegree);
    std::string toString();
};