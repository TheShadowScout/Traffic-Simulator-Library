#pragma once

#include "CrossingInput.h"

CrossingInput::CrossingInput() : Cell(), lanesWeightsSum(0) {
    this->setCarHolder(new CarHolder());
}

CrossingInput::CrossingInput(int maxSpeed) : Cell(maxSpeed), lanesWeightsSum(0) {
    if(maxSpeed > 6 || maxSpeed < 1)
        throw std::invalid_argument("Max speed must be in range between 1 and 6");
    this->setCarHolder(new CarHolder());
}

CrossingInput::~CrossingInput() {}

void CrossingInput::setNextCell(Cell* nextCell, int laneWeight) {
    lanesWeightsSum += laneWeight;
    lanesWeights.push_back(lanesWeightsSum);
    nextCells.push_back(nextCell);
}

Cell* CrossingInput::getNextCell() {
    int crossingLaneRandomizer = std::rand() % lanesWeightsSum;
    for (int i = 0; i < lanesWeights.size(); i++) {
        if (crossingLaneRandomizer < lanesWeights[i]) {
            return nextCells[i];
        }
    }
    return nullptr;
}

void CrossingInput::setNextCell(Cell* nextCell) {}

