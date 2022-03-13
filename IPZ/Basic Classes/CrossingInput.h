#pragma once

#include <vector>
#include <iostream>

#include "Cell.h"
#include <stdlib.h> 

class CrossingInput : public Cell
{
protected:
    std::vector<Cell*> nextCells;

public:
    CrossingInput();
    CrossingInput(int maxSpeed);
    ~CrossingInput();
    Cell* getNextCell();
    void setNextCell(Cell* nextCell);
};
