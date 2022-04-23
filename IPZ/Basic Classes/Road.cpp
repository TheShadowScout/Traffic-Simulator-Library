#pragma once

#include "Road.h"

Road::Road(std::string name, int length, int height, int maxSpeed) : length(length), height(height), maxSpeed(maxSpeed) {
    if(length < 1)
        throw std::invalid_argument("Length must be bigger than 1");
    if(height < 1)
        throw std::invalid_argument("Height must be bigger than 1");
    if(maxSpeed < 1 || maxSpeed > 6)
        throw std::invalid_argument("Max speed must be in range between 1 and 6");
    this->name = filterName(name);
    ID = IDcnt++;
    createRoad();
}

Road::Road(int length, int height, int maxSpeed) : length(length), height(height), maxSpeed(maxSpeed) {
    if(length < 1)
        throw std::invalid_argument("Length must be bigger than 1");
    if(height < 1)
        throw std::invalid_argument("Height must be bigger than 1");
    if(maxSpeed < 1 || maxSpeed > 6)
        throw std::invalid_argument("Max speed must be in range between 1 and 6");
    ID = IDcnt++;
    name = std::to_string(ID);
    createRoad();
}

Road::~Road() {
    for (std::vector<Cell*> roadLane : road) {
        for (Cell* laneCell : roadLane) {
            delete laneCell;
        }
    }
}

void Road::createRoad() {
    for (int i = 0; i < height; i++) {
        std::vector<Cell*> newRoadLane;
        for (int j = 0; j < length; j++) {
            Cell* newCell = new RoadCell(maxSpeed);
            newCell->setCarHolder(new CarHolder());
            if (j == 0) {
                head.push_back(newCell);
                newRoadLane.push_back(newCell);
                if (length == 1) {
                    tail.push_back(newCell);
                }
            }
            else {
                newCell->setPreviousCell(newRoadLane[j - 1]);
                newRoadLane[j - 1]->setNextCell(newCell);
                newRoadLane.push_back(newCell);
                if (j == length - 1)
                    tail.push_back(newCell);
            }
        }
        road.push_back(newRoadLane);
        if (i > 0) {
            for (int j = 0; j < length; j++) {
                road[i][j]->setLeftCell(road[i - 1][j]);
                road[i - 1][j]->setRightCell(road[i][j]);
            }
        }
    }
}

int Road::getMaxSpeed() {
    return maxSpeed;
}

int Road::getID() {
    return ID;
}

std::string Road::getName() {
    return name;
}

int Road::getLength() {
    return length;
}

int Road::getHeight() {
    return height;
}

std::vector<std::vector<Cell*>> Road::getRoad() {
    return road;
}

void Road::setMaxSpeed(int maxSpeed) {
    this->maxSpeed = maxSpeed;
}

void Road::setName(std::string name) {
    this->name = name;
}

std::string Road::toString() {
    std::string roadStr = "";
    for (std::vector<Cell*> roadLane : road) {
        for (Cell* laneCell : roadLane) {
            if (laneCell->getVehicle() == nullptr) {
                roadStr += ".";
            }
            else {
                if (laneCell->getVehicle()->getIsObstacle() == true) {
                    roadStr += "!";
                }
                else {
                    roadStr += std::to_string(laneCell->getVehicle()->getSpeed());
                }
            }
        }
        roadStr += "\n";
    }
    return roadStr;
}

std::string Road::filterName(std::string rawName) {
    std::string tempName = "";
    for (char character : rawName) {
        if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character >= '0' && character <= '9')) {
            tempName += character;
        }
    }
    return tempName;
}

void Road::fillWithVehs(double fillingDegree) {
    int passableCellsCnt = 0;
    for (std::vector<Cell*> lane : road) {
        for (Cell* roadCell : lane) {
            Vehicle* cellVeh = roadCell->getVehicle();
            if (cellVeh != nullptr && cellVeh->getIsObstacle() == true) {
                continue;
            }
            passableCellsCnt++;
        }
    }
    int vehsToGenerateCnt = std::min((int)(std::round(fillingDegree * passableCellsCnt)), passableCellsCnt);
    int generatedVehsCnt = 0;
    while (generatedVehsCnt < vehsToGenerateCnt) {
        for (std::vector<Cell*> lane : road) {
            for (Cell* roadCell : lane) {
                if (roadCell->getVehicle() == nullptr) {
                    if (1.0 * std::rand() / RAND_MAX <= fillingDegree) {
                        roadCell->setVehicle(new Vehicle(0));
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
    std::string nameTree = "Road" + std::to_string(getID());
    roadTree.put(nameTree + ".Name", getName());
    roadTree.put(nameTree + ".ID", getID());
    roadTree.put(nameTree + ".Length", getLength());
    roadTree.put(nameTree + ".Height", getHeight());
    std::ostringstream oss;
    boost::property_tree::write_json(oss, roadTree);
    std::cout << oss.str();
}

void Road::addLights(TrafficLights* newLight, int distanceFromHead) {
    lights.push_back(newLight);
    for (int i = 0; i < height; i++)
        road[i][distanceFromHead]->setLight(newLight);
}

std::vector<TrafficLights*> Road::getLights() {
    return lights;
}

void Road::addObstacle(int distanceFromHead, int lane, int spotDistance) {
    road[lane][distanceFromHead]->setVehicle(new Obstacle());
    Cell* tempCell = road[lane][distanceFromHead];
    for (int i = 1; i <= spotDistance; i++) {
        tempCell = tempCell->getPreviousCell();
        if (tempCell != nullptr) {
            tempCell->setObstacleAhead(true);
        }
    }
}
