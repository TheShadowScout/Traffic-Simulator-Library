#pragma once

#include "LaneEndsMerge.h"

LaneEndsMerge::LaneEndsMerge(std::string name, int length, int height, int maxSpeed) : name(name), length(length), height(height), maxSpeed(maxSpeed) {
    create();
}

LaneEndsMerge::LaneEndsMerge(int length, int height, int maxSpeed) : length(length), height(height), maxSpeed(maxSpeed) {
    create();
    name = std::to_string(ID);
}

LaneEndsMerge::~LaneEndsMerge() {
    for (std::vector<Cell*> roadLane : lanes) {
        for (Cell* laneCell : roadLane) {
            delete laneCell;
        }
    }
}

int LaneEndsMerge::getID() {
    return ID;
}

std::string LaneEndsMerge::getName() {
    return name;
}

void LaneEndsMerge::create() {
    if (length < 1)
        throw std::invalid_argument("Length must be bigger than 1");
    if (height < 1)
        throw std::invalid_argument("Height must be bigger than 1");
    if (maxSpeed < 1 || maxSpeed > 6)
        throw std::invalid_argument("Max speed must be in range between 1 and 6");
    ID = IDcnt++;
    for (int i = 0; i < height; i++) {
        std::vector<Cell*> newRoadLane;
        for (int j = 0; j < length; j++) {
            RoadCell* newCell = new RoadCell(maxSpeed);
            newCell->setCarHolder(new CarHolder());
            if (j == 0) {
                newRoadLane.push_back(newCell);
            }
            else {
                newCell->setPreviousCell(newRoadLane[j - 1]);
                newRoadLane[j - 1]->setNextCell(newCell);
                newRoadLane.push_back(newCell);
            }
        }
        lanes.push_back(newRoadLane);
        if (i > 0) {
            for (int j = 0; j < length; j++) {
                lanes[i][j]->setLeftCell(lanes[i - 1][j]);
                lanes[i - 1][j]->setRightCell(lanes[i][j]);
            }
        }
    }
}

int LaneEndsMerge::getMaxSpeed() {
    return maxSpeed;
}

int LaneEndsMerge::getLength() {
    return length;
}

int LaneEndsMerge::getHeight() {
    return height;
}

Cell* LaneEndsMerge::getLaneHead(int lane) {
    return lanes[lane].front();
}

Cell* LaneEndsMerge::getLaneTail(int lane) {
    return lanes[lane].back();
}

std::vector<std::vector<Cell*>> LaneEndsMerge::getLanes() {
    return lanes;
}
