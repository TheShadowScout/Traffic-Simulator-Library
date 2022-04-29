#pragma once

#include "SmartCrossingInput.h"

SmartCrossingInput::SmartCrossingInput(int maxSpeed) : BasicCrossingInput(maxSpeed), maxSpeedReminder(maxSpeed), drawnLaneReminder(0) { ; }

void SmartCrossingInput::setNextCell(Cell* nextCell) {
    weightsSum += 1;
    weights.push_back(weightsSum);
    nextCells.push_back(nextCell);
}

void SmartCrossingInput::setNextCell(Cell* nextCell, int laneWeight) {
    weightsSum += laneWeight;
    weights.push_back(weightsSum);
    nextCells.push_back(nextCell);
}

void SmartCrossingInput::addDestinatinCell(Cell* destinationCell) {
    destinationCells.push_back(destinationCell);
}

void SmartCrossingInput::drawLane() {
    if (this->getVehicle() != nullptr) {
        checkCrossingEntryAvailability(drawnLaneReminder);
        drawnLane = drawnLaneReminder;
        return;
    }
    int crossingLaneRandomizer = std::rand() % weightsSum;
    for (unsigned int i = 0; i < weights.size(); i++) {
        if (crossingLaneRandomizer < weights[i]) {
            checkCrossingEntryAvailability(i);
            drawnLane = i;
            drawnLaneReminder = i;
            break;
        }
    }
}

void SmartCrossingInput::checkCrossingEntryAvailability(int laneIndex) {
    int carsInLaneCnt = 0;
    int laneLength = 0;
    Cell* tempCell = nextCells[laneIndex];
    while (tempCell != destinationCells[laneIndex]->getNextCell()) {
        if (tempCell->getVehicle() != nullptr) {
            carsInLaneCnt++;
        }
        tempCell = tempCell->getNextCell();
        laneLength++;
    }
    int freeCells = 0;
    tempCell = destinationCells[laneIndex];
    for (int j = 1; j <= laneLength; j++) {
        tempCell = tempCell->getNextCell();
        if (tempCell == nullptr) {
            break;
        }
        if (tempCell->getVehicle() == nullptr) {
            freeCells++;
        }
    }
    if (carsInLaneCnt + 1 > freeCells && tempCell != nullptr) {
        maxSpeed = 0;
    }
    else {
        maxSpeed = maxSpeedReminder;
    }
}
