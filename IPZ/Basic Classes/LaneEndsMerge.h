#pragma once

#include <vector>

#include "RoadCell.h"

class LaneEndsMerge {
public:
    int static IDcnt;

protected:
    int ID;
    int maxSpeed;
    int length;
    int height;
    std::string name;
    std::vector<std::vector<Cell*>> lanes;

    void create();

public:
    LaneEndsMerge(std::string name, int length, int height, int roadMaxSpeed);
    LaneEndsMerge(int length, int height, int roadMaxSpeed);
    ~LaneEndsMerge();
    int getID();
    std::string getName();
    int getMaxSpeed();
    int getLength();
    int getHeight();
    Cell* getLaneHead(int lane);
    Cell* getLaneTail(int lane);
    std::vector<std::vector<Cell*>> getLanes();
    virtual std::vector<std::vector<Cell*>> getEndingLanes() = 0;
    virtual int getPassableCellsCnt() = 0;
    virtual std::vector<Cell*> getCellsWithVehs() = 0;
    virtual void fillWithVehs(double fillingDegree) = 0;
    virtual std::string toString() = 0;
};