#pragma once

#include "LaneEndsMergeR.h"

LaneEndsMergeR::LaneEndsMergeR(std::string name, int length, int height, int maxSpeed) : LaneEndsMerge(name, length, height, maxSpeed) {
    create();
}

LaneEndsMergeR::LaneEndsMergeR(int length, int height, int maxSpeed) : LaneEndsMerge(length, height, maxSpeed) {
    create();
}

LaneEndsMergeR::~LaneEndsMergeR() {
    delete endingLaneR.back()->getNextCell();
    for (Cell* endingLaneCell : endingLaneR) {
        delete endingLaneCell;
    }
}

void LaneEndsMergeR::create() {
    for (int i = 0; i < length; i++) {
        RoadCell* newCell = new RoadCell(maxSpeed);
        newCell->setCarHolder(new CarHolder());
        newCell->setObstacleAhead(true);
        if (i == 0) {
            endingLaneR.push_back(newCell);
        }
        else {
            newCell->setPreviousCell(endingLaneR[i - 1]);
            endingLaneR[i - 1]->setNextCell(newCell);
            endingLaneR.push_back(newCell);
        }
        newCell->setLeftCell(lanes[height - 1][i]);
    }
    RoadCell* newCell = new RoadCell(maxSpeed);
    newCell->setCarHolder(new CarHolder());
    newCell->setVehicle(new Obstacle());
    newCell->setObstacleAhead(true);
    endingLaneR.back()->setNextCell(newCell);
    newCell->setPreviousCell(endingLaneR.back());
}

Cell* LaneEndsMergeR::getEndingLaneRHead() {
    return endingLaneR.front();
}

std::vector<std::vector<Cell*>> LaneEndsMergeR::getEndingLanes() {
    std::vector<std::vector<Cell*>> endingLanes;
    endingLanes.push_back(std::vector<Cell*>());
    endingLanes.push_back(endingLaneR);
    return endingLanes;
}

int LaneEndsMergeR::getPassableCellsCnt() {
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
    for (Cell* endingLaneCell : endingLaneR) {
        cellVeh = endingLaneCell->getVehicle();
        if (cellVeh != nullptr && cellVeh->getIsObstacle() == true) {
            continue;
        }
        passableCellsCnt++;
    }
    return passableCellsCnt;
}

std::vector<Cell*> LaneEndsMergeR::getCellsWithVehs() {
    std::vector<Cell*> cellsWithVehs;
    for (std::vector<Cell*> lane : lanes) {
        for (Cell* laneCell : lane) {
            Vehicle* cellVeh = laneCell->getVehicle();
            if (cellVeh != nullptr && cellVeh->getIsObstacle() == false) {
                cellsWithVehs.push_back(laneCell);
            }
        }
    }
    for (Cell* laneCell : endingLaneR) {
        Vehicle* cellVeh = laneCell->getVehicle();
        if (cellVeh != nullptr && cellVeh->getIsObstacle() == false) {
            cellsWithVehs.push_back(laneCell);
        }
    }
    return cellsWithVehs;
}

void LaneEndsMergeR::fillWithVehs(double fillingDegree) {
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
        for (Cell* endingLaneCell : endingLaneR) {
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
            for (Cell* endingLaneCell : endingLaneR) {
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

std::string LaneEndsMergeR::toString() {
    std::string repStr = "LaneEndsMergeR: ";
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
    for (Cell* laneCell : endingLaneR) {
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
    return repStr;
}
