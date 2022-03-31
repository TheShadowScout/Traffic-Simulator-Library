#pragma once

#include "CrossingInput.h"

CrossingInput::CrossingInput() : Cell() {
    this->setCarHolder(new CarHolder());
}

CrossingInput::CrossingInput(int maxSpeed) : Cell(maxSpeed) {
    this->setCarHolder(new CarHolder());
}

CrossingInput::~CrossingInput() {}

void CrossingInput::setNextCell(Cell* nextCell) {
    this->nextCells.push_back(nextCell);
}

Cell* CrossingInput::getNextCell() {
    int randomNextCellIndex = std::rand() % nextCells.size();
    return nextCells[randomNextCellIndex];
}

