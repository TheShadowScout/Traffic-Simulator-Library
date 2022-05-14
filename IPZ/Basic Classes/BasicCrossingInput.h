#pragma once

#include <vector>

#include "Cell.h"

class BasicCrossingInput : public Cell
{
protected:
    std::vector<Cell*> nextCells;
    std::vector<int> weights;
    int weightsSum;
    int drawnLane;

public:
    BasicCrossingInput();
    BasicCrossingInput(int maxSpeed);
    Cell* getNextCell();
    void setNextCell(Cell* nextCell);
    void setNextCell(Cell* nextCell, int weight);
    void drawLane();
};
