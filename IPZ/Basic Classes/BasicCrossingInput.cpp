#pragma once

#include "BasicCrossingInput.h"

BasicCrossingInput::BasicCrossingInput() : Cell(), weightsSum(0), drawnLane(0) {
    this->setCarHolder(new CarHolder());
}

BasicCrossingInput::BasicCrossingInput(int maxSpeed) : Cell(maxSpeed), weightsSum(0), drawnLane(0) {
    if(maxSpeed > 6 || maxSpeed < 1)
        throw std::invalid_argument("Max speed must be in range between 1 and 6");
    this->setCarHolder(new CarHolder());
}

Cell* BasicCrossingInput::getNextCell() {
    return nextCells[drawnLane];
}

void BasicCrossingInput::setNextCell(Cell* nextCell) {
    weightsSum += 1;
    weights.push_back(weightsSum);
    nextCells.push_back(nextCell);
}

void BasicCrossingInput::setNextCell(Cell* nextCell, int laneWeight) {
    weightsSum += laneWeight;
    weights.push_back(weightsSum);
    nextCells.push_back(nextCell);
}

void BasicCrossingInput::drawLane() {
    int crossingLaneRandomizer = std::rand() % weightsSum;
    for (unsigned int i = 0; i < weights.size(); i++) {
        if (crossingLaneRandomizer < weights[i]) {
            drawnLane = i;
            break;
        }
    }
}
