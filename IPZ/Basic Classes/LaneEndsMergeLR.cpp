#pragma once

#include "LaneEndsMergeLR.h"

LaneEndsMergeLR::LaneEndsMergeLR(std::string name, int length, int height, int maxSpeed) : LaneEndsMerge(name, length, height, maxSpeed) {
    create();
}

LaneEndsMergeLR::LaneEndsMergeLR(int length, int height, int maxSpeed) : LaneEndsMerge(length, height, maxSpeed) {
    create();
}

LaneEndsMergeLR::~LaneEndsMergeLR() {
    delete endingLaneL.back()->getNextCell();
    delete endingLaneR.back()->getNextCell();
    for (Cell* endingLaneCell : endingLaneL) {
        delete endingLaneCell;
    }
    for (Cell* endingLaneCell : endingLaneR) {
        delete endingLaneCell;
    }
}

void LaneEndsMergeLR::create() {
    for (int i = 0; i < length; i++) {
        RoadCell* newCellL = new RoadCell(maxSpeed);
        newCellL->setCarHolder(new CarHolder());
        newCellL->setObstacleAhead(true);
        RoadCell* newCellR = new RoadCell(maxSpeed);
        newCellR->setCarHolder(new CarHolder());
        newCellR->setObstacleAhead(true);
        if (i == 0) {
            endingLaneL.push_back(newCellL);
            endingLaneR.push_back(newCellR);
        }
        else {
            newCellL->setPreviousCell(endingLaneL[i - 1]);
            endingLaneL[i - 1]->setNextCell(newCellL);
            endingLaneL.push_back(newCellL);
            newCellR->setPreviousCell(endingLaneR[i - 1]);
            endingLaneR[i - 1]->setNextCell(newCellR);
            endingLaneR.push_back(newCellR);
        }
        newCellL->setRightCell(lanes[0][i]);
        newCellR->setLeftCell(lanes[height - 1][i]);
    }
    RoadCell* newCellL = new RoadCell(maxSpeed);
    newCellL->setCarHolder(new CarHolder());
    newCellL->setVehicle(new Obstacle());
    newCellL->setObstacleAhead(true);
    endingLaneL.back()->setNextCell(newCellL);
    newCellL->setPreviousCell(endingLaneL.back());
    RoadCell* newCellR = new RoadCell(maxSpeed);
    newCellR->setCarHolder(new CarHolder());
    newCellR->setVehicle(new Obstacle());
    newCellR->setObstacleAhead(true);
    endingLaneR.back()->setNextCell(newCellR);
    newCellR->setPreviousCell(endingLaneR.back());
}

Cell* LaneEndsMergeLR::getEndingLaneLHead() {
    return endingLaneL.front();
}

Cell* LaneEndsMergeLR::getEndingLaneRHead() {
    return endingLaneR.front();
}

std::vector<std::vector<Cell*>> LaneEndsMergeLR::getEndingLanes() {
    std::vector<std::vector<Cell*>> endingLanes;
    endingLanes.push_back(endingLaneL);
    endingLanes.push_back(endingLaneR);
    return endingLanes;
}

int LaneEndsMergeLR::getPassableCellsCnt() {
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
    for (Cell* endingLaneCell : endingLaneR) {
        cellVeh = endingLaneCell->getVehicle();
        if (cellVeh != nullptr && cellVeh->getIsObstacle() == true) {
            continue;
        }
        passableCellsCnt++;
    }
    return passableCellsCnt;
}

std::vector<Cell*> LaneEndsMergeLR::getCellsWithVehs() {
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
    for (Cell* laneCell : endingLaneR) {
        Vehicle* cellVeh = laneCell->getVehicle();
        if (cellVeh != nullptr && cellVeh->getIsObstacle() == false) {
            cellsWithVehs.push_back(laneCell);
        }
    }
    return cellsWithVehs;
}

void LaneEndsMergeLR::fillWithVehs(double fillingDegree) {
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

std::string LaneEndsMergeLR::toString() {
    std::string repStr = "LaneEndsMergeLR: ";
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
