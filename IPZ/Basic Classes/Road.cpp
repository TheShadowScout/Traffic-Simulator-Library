#pragma once

#include "Road.h"

Road::Road(std::string name, int length, int height, int maxSpeed) : name(name), length(length), height(height), maxSpeed(maxSpeed) {
    create();
}

Road::Road(int length, int height, int maxSpeed) : length(length), height(height), maxSpeed(maxSpeed) {
    create();
    name = std::to_string(ID);
}

Road::~Road() {
    for (std::vector<Cell*> lane : lanes) {
        for (Cell* laneCell : lane) {
            delete laneCell;
        }
    }
}

void Road::create() {
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

Cell* Road::getLaneHead(int lane) {
    return lanes[lane].front();
}

Cell* Road::getLaneTail(int lane) {
    return lanes[lane].back();
}

int Road::getMaxSpeed() {
    return maxSpeed;
}

std::string Road::getName() {
    return name;
}

int Road::getID() {
    return ID;
}

int Road::getLength() {
    return length;
}

int Road::getHeight() {
    return height;
}

std::vector<std::vector<Cell*>> Road::getLanes() {
    return lanes;
}

int Road::getPassableCellsCnt() {
    int passableCellsCnt = 0;
    Vehicle* cellVeh = nullptr;
    for (std::vector<Cell*> lane : lanes) {
        for (Cell* laneCell : lane) {
            cellVeh = laneCell->getVehicle();
            if (cellVeh != nullptr && cellVeh->getIsObstacle() == true) {
                continue;
            }
            passableCellsCnt++;
        }
    }
    return passableCellsCnt;
}

std::vector<Cell*> Road::getCellsWithVehs() {
    std::vector<Cell*> cellsWithVehs;
    for (std::vector<Cell*> lane : lanes) {
        for (Cell* laneCell : lane) {
            Vehicle* cellVeh = laneCell->getVehicle();
            if (cellVeh != nullptr && cellVeh->getIsObstacle() == false) {
                cellsWithVehs.push_back(laneCell);
            }
        }
    }
    return cellsWithVehs;
}

std::vector<TrafficLights*> Road::getTrafficLights() {
    return trafficLights;
}

void Road::addTrafficLightsToOneLane(TrafficLights* newLight, int distanceFromHead, int lane) {
    trafficLights.push_back(newLight);
    lanes[lane][distanceFromHead]->setTrafficLight(newLight);
}

void Road::addTrafficLightsToAllLanes(TrafficLights* newLight, int distanceFromHead) {
    trafficLights.push_back(newLight);
    for (int i = 0; i < height; i++)
        lanes[i][distanceFromHead]->setTrafficLight(newLight);
}

void Road::addObstacle(int distanceFromHead, int lane, int spotDistance) {
    lanes[lane][distanceFromHead]->setVehicle(new Obstacle());
    Cell* tempCell = lanes[lane][distanceFromHead];
    for (int i = 1; i <= spotDistance; i++) {
        tempCell = tempCell->getPreviousCell();
        if (tempCell != nullptr) {
            tempCell->setObstacleAhead(true);
        }
    }
}

void Road::fillWithVehs(double fillingDegree) {
    int passableCellsCnt = getPassableCellsCnt();
    int vehsToGenerateCnt = std::min((int)(std::round(fillingDegree * passableCellsCnt)), passableCellsCnt);
    int generatedVehsCnt = 0;
    while (generatedVehsCnt < vehsToGenerateCnt) {
        for (std::vector<Cell*> lane : lanes) {
            for (Cell* laneCell : lane) {
                if (laneCell->getVehicle() == nullptr) {
                    if (1.0 * std::rand() / RAND_MAX <= fillingDegree) {
                        laneCell->setVehicle(new Vehicle(0));
                        generatedVehsCnt++;
                        if (generatedVehsCnt >= vehsToGenerateCnt) {
                            return;
                        }
                    }
                }
            }
        }
    }
}

void Road::createJSON() {
    ptree roadTree;
    std::string nameTree = "Road" + std::to_string(ID);
    roadTree.put(nameTree + ".Name", name);
    roadTree.put(nameTree + ".ID", ID);
    roadTree.put(nameTree + ".Length", length);
    roadTree.put(nameTree + ".Height", height);
    std::ostringstream oss;
    boost::property_tree::write_json(oss, roadTree);
    std::cout << oss.str();
}

std::string Road::toString() {
    std::string repStr = "Road: ";
    repStr += name;
    repStr += "\n";
    for (std::vector<Cell*> lane : lanes) {
        for (Cell* laneCell : lane) {
            if (laneCell->getVehicle() == nullptr) {
                repStr += ".";
            }
            else {
                if (laneCell->getVehicle()->getIsObstacle() == true) {
                    repStr += "!";
                }
                else {
                    repStr += std::to_string(laneCell->getVehicle()->getSpeed());
                }
            }
        }
        repStr += "\n";
    }
    return repStr;
}
