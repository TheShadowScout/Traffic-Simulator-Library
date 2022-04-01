#pragma once

#include <vector>
#include <iostream>

#include "Cell.h"

class CrossingInput : public Cell
{
protected:
    std::vector<Cell*> nextCells;
    std::vector<int> lanesWeights;
    int lanesWeightsSum;

public:
    CrossingInput();
    CrossingInput(int maxSpeed);
    ~CrossingInput();
    Cell* getNextCell();
    void setNextCell(Cell* nextCell);
    void setNextCell(Cell* nextCell, int laneWeight);
};
