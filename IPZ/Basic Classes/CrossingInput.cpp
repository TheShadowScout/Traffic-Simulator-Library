#pragma once

#include "CrossingInput.h"

CrossingInput::CrossingInput() : Cell(), weightsSum(0) {
    this->setCarHolder(new CarHolder());
}

CrossingInput::CrossingInput(int maxSpeed) : Cell(maxSpeed), weightsSum(0) {
    if(maxSpeed > 6 || maxSpeed < 1)
        throw std::invalid_argument("Max speed must be in range between 1 and 6");
    this->setCarHolder(new CarHolder());
}

CrossingInput::~CrossingInput() {}

void CrossingInput::setNextCell(Cell* nextCell) {
    weightsSum += 1;
    weights.push_back(weightsSum);
    nextCells.push_back(nextCell);
}

void CrossingInput::setNextCell(Cell* nextCell, int laneWeight) {
    weightsSum += laneWeight;
    weights.push_back(weightsSum);
    nextCells.push_back(nextCell);
}

Cell* CrossingInput::getNextCell() {
    int crossingLaneRandomizer = std::rand() % weightsSum;
    for (unsigned int i = 0; i < weights.size(); i++) {
        if (crossingLaneRandomizer < weights[i]) {
            return nextCells[i];
        }
    }
    return nullptr;
}



