#pragma once

#include "Crossing.h"

Crossing::Crossing(std::string name, int height, int length, int maxSpeed) : name(name), height(height), length(length), maxSpeed(maxSpeed) {
    create();
}

Crossing::Crossing(int height, int length, int maxSpeed) : height(height), length(length), maxSpeed(maxSpeed) {
    create();
    name = std::to_string(ID);
}

Crossing::~Crossing() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < length; j++) {
            delete carHolderMatrix[i][j];
        }
    }
    for (std::vector<RoadCell*> crossingLane : lanes) {
        for (RoadCell* crossingCell : crossingLane) {
            crossingCell->setCarHolder(nullptr);
            delete crossingCell;
        }
    }
    for (int i = 0; i < length; i++) {
        delete outputsN[i];
        delete outputsS[i];
    }
    for (int i = 0; i < height; i++) {
        delete outputsE[i];
        delete outputsW[i];
    }
}

void Crossing::create() {
    if (height < 1)
        throw std::invalid_argument("Crossing height must be higher than 1");
    if (length < 1)
        throw std::invalid_argument("Crossing length must be higher than 1");
    if (maxSpeed < 1 || maxSpeed > 6)
        throw std::invalid_argument("Crossing max speed must be in range between 1 and 6");
    ID = IDcnt++;
    for (int i = 0; i < height; i++) {
        carHolderMatrix.push_back(std::vector<CarHolder*>(length));
    }
    outputsN = std::vector<RoadCell*>(length);
    outputsE = std::vector<RoadCell*>(height);
    outputsS = std::vector<RoadCell*>(length);
    outputsW = std::vector<RoadCell*>(height);
}

int Crossing::getID() {
    return ID;
}
int Crossing::getHeight() {
    return height;
}

int Crossing::getLength() {
    return length;
}
std::vector<RoadCell*> Crossing::getOutputsN(){
    return outputsN;
}

std::vector<RoadCell*> Crossing::getOutputsW(){
    return outputsW;
}

std::vector<RoadCell*> Crossing::getOutputsE(){
    return outputsE;
}

std::vector<RoadCell*> Crossing::getOutputsS(){
    return outputsS;
}


std::string Crossing::getName() {
    return name;
}

std::vector<TrafficLights*> Crossing::getTrafficLights() {
    return trafficLights;
}

std::vector<std::vector<CarHolder*>> Crossing::getCarHolderMatrix()
{
    return carHolderMatrix;
}

void Crossing::linkCellToCrossingOutput(char outputSide, int outputIndex, Cell* nextCell) {
    switch (outputSide) {
    case 'N':
        outputsN[outputIndex]->setNextCell(nextCell);
        nextCell->setPreviousCell(outputsN[outputIndex]);
        break;
    case 'E':
        outputsE[outputIndex]->setNextCell(nextCell);
        nextCell->setPreviousCell(outputsE[outputIndex]);
        break;
    case 'S':
        outputsS[outputIndex]->setNextCell(nextCell);
        nextCell->setPreviousCell(outputsS[outputIndex]);
        break;
    case 'W':
        outputsW[outputIndex]->setNextCell(nextCell);
        nextCell->setPreviousCell(outputsW[outputIndex]);
        break;
    }
}

