#pragma once

#include "Crossing.h"

Crossing::Crossing(std::string name, int crossingHeight, int crossingLength, int crossingMaxSpeed) : name(name), crossingHeight(crossingHeight), crossingMaxSpeed(crossingMaxSpeed), crossingLength(crossingLength) {
    create();
    ID = IDcnt++;
}

Crossing::Crossing(int crossingHeight, int crossingLength, int crossingMaxSpeed) : crossingHeight(crossingHeight), crossingMaxSpeed(crossingMaxSpeed), crossingLength(crossingLength) {
    create();
    ID = IDcnt++;
    name = std::to_string(ID);
}

void Crossing::create() {
    if (crossingHeight < 1)
        throw std::invalid_argument("Crossing height must be higher than 1");
    if (crossingLength < 1)
        throw std::invalid_argument("Crossing length must be higher than 1");
    if (crossingMaxSpeed < 1 || crossingMaxSpeed > 6)
        throw std::invalid_argument("Crossing max speed must be in range between 1 and 6");
    for (int i = 0; i < crossingHeight; i++) {
        std::vector<CarHolder*> carHolderRow;
        for (int j = 0; j < crossingLength; j++) {
            carHolderRow.push_back(new CarHolder());
        }
        carHolderMatrix.push_back(carHolderRow);
    }
    for (int i = 0; i < crossingLength; i++) {
        outputN.push_back(nullptr);
        outputS.push_back(nullptr);
    }
    for (int i = 0; i < crossingHeight; i++) {
        outputW.push_back(nullptr);
        outputE.push_back(nullptr);
    }
}

Crossing::~Crossing() {
    for (std::vector<RoadCell*> crossingLane : crossingLanes) {
        for (RoadCell* crossingCell : crossingLane) {
            delete crossingCell;
        }
    }
    for(int i = 0; i < crossingHeight; i++) {
        for(int j = 0; j < crossingLength; j++) {
            delete carHolderMatrix[i][j];
        }
    }
    for(int i = 0; i < crossingLength; i++) {
        delete outputN[i];
        delete outputS[i];
    }
    for(int i = 0; i < crossingHeight; i++) {
        delete outputE[i];
        delete outputW[i];
    }
}

std::vector<TrafficLights*> Crossing::getTrafficLights() {
    return trafficLights;
}

void Crossing::linkRoadLaneToCrossing(char outputSide, int outputIndex, Cell* nextCell) {
    switch(outputSide) {   
        case 'N':
            outputN[outputIndex]->setNextCell(nextCell);
            nextCell->setPreviousCell(outputN[outputIndex]);
            break;
        case 'E':
            outputE[outputIndex]->setNextCell(nextCell);
            nextCell->setPreviousCell(outputE[outputIndex]);
            break;
        case 'S':
            outputS[outputIndex]->setNextCell(nextCell);
            nextCell->setPreviousCell(outputS[outputIndex]);
            break;
        case 'W':
            outputW[outputIndex]->setNextCell(nextCell);
            nextCell->setPreviousCell(outputW[outputIndex]);
            break;
    }
}

std::string Crossing::toString() {
    std::string crossingStr = "";
    for (std::vector<CarHolder*> carHolderRow : carHolderMatrix) {
        for (CarHolder* carHolder : carHolderRow) {
            if (carHolder->getVehicle() == nullptr) {
                crossingStr += ".";
            }
            else {
                crossingStr += std::to_string(carHolder->getVehicle()->getSpeed());
            }
        }
        crossingStr += "\n";
    }
    return crossingStr;
}
