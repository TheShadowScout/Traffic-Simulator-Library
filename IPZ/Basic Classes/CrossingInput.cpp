#pragma once

#include "CrossingInput.h"

CrossingInput::CrossingInput() : Cell() {
    this->setCarHolder(new CarHolder());
}

CrossingInput::CrossingInput(int maxSpeed) : Cell(maxSpeed) {
    this->setCarHolder(new CarHolder());
}

CrossingInput::~CrossingInput() {}

void CrossingInput::setNextCell(Cell* nextCell)
{
    //this->nextCell = nextCell;
    this->nextCells.push_back(nextCell);
}

Cell* CrossingInput::getNextCell()
{
    //return nextCell;
    int x = std::rand() % nextCells.size();
    //std::cout << x << std::endl;
    return nextCells[x];
}

