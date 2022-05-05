#pragma once

#include "LaneEndsMergeL.h"

LaneEndsMergeL::LaneEndsMergeL(int length, int height, int roadMaxSpeed) : LaneEndsMerge(length, height, roadMaxSpeed) {
	std::vector<Cell*> endingLaneL;
	for (int i = 0; i < length; i++) {
        RoadCell* newCell = new RoadCell(roadMaxSpeed);
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
    RoadCell* newCell = new RoadCell(roadMaxSpeed);
    newCell->setCarHolder(new CarHolder());
    newCell->setVehicle(new Obstacle());
    newCell->setObstacleAhead(true);
    endingLaneL.back()->setNextCell(newCell);
    newCell->setPreviousCell(endingLaneL.back());
}

LaneEndsMergeL::~LaneEndsMergeL() {
    delete endingLaneL.back()->getNextCell();
    for (Cell* endingLaneCell : endingLaneL) {
        delete endingLaneCell;
    }
}

Cell* LaneEndsMergeL::getEndingLaneLHead() {
    return endingLaneL.back();
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
    ;
    return std::string();
}
