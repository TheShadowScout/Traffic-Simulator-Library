#pragma once

#include "RoadCell.h"

RoadCell::RoadCell() : Cell(), nextCell(nullptr) {}

RoadCell::RoadCell(int maxSpeed) : Cell(maxSpeed), nextCell(nullptr) {}

RoadCell::~RoadCell() {}

void RoadCell::setNextCell(Cell* nextCell) {
    this->nextCell = nextCell;
}

Cell* RoadCell::getNextCell() {
    return nextCell;
}

