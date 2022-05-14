#pragma once

#include "LaneEndsMergeL.h"

LaneEndsMergeL::LaneEndsMergeL(std::string name, int length, int height, int maxSpeed) : LaneEndsMerge(name, length, height, maxSpeed) {
    create();
}

LaneEndsMergeL::LaneEndsMergeL(int length, int height, int maxSpeed) : LaneEndsMerge(length, height, maxSpeed) {
    create();
}

LaneEndsMergeL::~LaneEndsMergeL() {
    delete endingLaneL.back()->getNextCell();
    for (Cell* endingLaneCell : endingLaneL) {
        delete endingLaneCell;
    }
}

void LaneEndsMergeL::create() {
    for (int i = 0; i < length; i++) {
        RoadCell* newCell = new RoadCell(maxSpeed);
        newCell->setCarHolder(new CarHolder());
        newCell->setObstacleAhead(true);
        if (i == 0) {
            endingLaneL.push_back(newCell);
        }
        else {
            newCell->setPreviousCell(endingLaneL[i - 1]);
            endingLaneL[i - 1]->setNextCell(newCell);
            endingLaneL.push_back(newCell);
        }
        newCell->setRightCell(lanes[0][i]);
    }
    RoadCell* newCell = new RoadCell(maxSpeed);
    newCell->setCarHolder(new CarHolder());
    newCell->setVehicle(new Obstacle());
    newCell->setObstacleAhead(true);
    endingLaneL.back()->setNextCell(newCell);
    newCell->setPreviousCell(endingLaneL.back());
}

Cell* LaneEndsMergeL::getEndingLaneLHead() {
    return endingLaneL.front();
}

std::vector<std::vector<Cell*>> LaneEndsMergeL::getEndingLanes() {
    std::vector<std::vector<Cell*>> endingLanes;
    endingLanes.push_back(endingLaneL);
    endingLanes.push_back(std::vector<Cell*>());
    return endingLanes;
}

int LaneEndsMergeL::getPassableCellsCnt() {
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
    for (Cell* endingLaneCell : endingLaneL) {
        cellVeh = endingLaneCell->getVehicle();
        if (cellVeh != nullptr && cellVeh->getIsObstacle() == true) {
            continue;
        }
        passableCellsCnt++;
    }
    return passableCellsCnt;
}

std::vector<Cell*> LaneEndsMergeL::getCellsWithVehs() {
    std::vector<Cell*> cellsWithVehs;
    for (std::vector<Cell*> lane : lanes) {
        for (Cell* laneCell : lane) {
            Vehicle* cellVeh = laneCell->getVehicle();
            if (cellVeh != nullptr && cellVeh->getIsObstacle() == false) {
                cellsWithVehs.push_back(laneCell);
            }
        }
    }
    for (Cell* laneCell : endingLaneL) {
        Vehicle* cellVeh = laneCell->getVehicle();
        if (cellVeh != nullptr && cellVeh->getIsObstacle() == false) {
            cellsWithVehs.push_back(laneCell);
        }
    }
    return cellsWithVehs;
}

void LaneEndsMergeL::fillWithVehs(double fillingDegree) {
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
        for (Cell* endingLaneCell : endingLaneL) {
            cellVeh = endingLaneCell->getVehicle();
            if (cellVeh != nullptr && cellVeh->getIsObstacle() == true) {
                continue;
            }
            passableCellsCnt++;
        }
    }
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
            for (Cell* endingLaneCell : endingLaneL) {
                if (endingLaneCell->getVehicle() == nullptr) {
                    if (1.0 * std::rand() / RAND_MAX <= fillingDegree) {
                        endingLaneCell->setVehicle(new Vehicle(0));
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

std::string LaneEndsMergeL::toString() {
    std::string repStr = "LaneEndsMergeL: ";
    repStr += name;
    repStr += "\n";
    for (Cell* laneCell : endingLaneL) {
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
