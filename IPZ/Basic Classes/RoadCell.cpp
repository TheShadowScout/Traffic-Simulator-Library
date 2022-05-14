#pragma once

#include "RoadCell.h"

RoadCell::RoadCell() : Cell(), nextCell(nullptr) {}

RoadCell::RoadCell(int maxSpeed) : Cell(maxSpeed), nextCell(nullptr) {
    if(maxSpeed < 1 || maxSpeed > 6)
        throw std::invalid_argument("Max speed must be in range between 1 and 6");
}

void RoadCell::setNextCell(Cell* nextCell) {
    this->nextCell = nextCell;
}

Cell* RoadCell::getNextCell() {
    return nextCell;
}

