#pragma once

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "Map.h"
#include "Cell.h"

class Simulation {
protected:
	int distToSearch[7] = { 1, 3, 6, 10, 15, 21, 28 };
	int breakingDist[7] = { 0, 1, 3, 6, 10, 15, 21 };
	double randEventProb;
	Map* simMap;

public:
	Simulation(Map* simMap, double randEventProb) : simMap(simMap), randEventProb(randEventProb) {}

	void transitionFunc() {
		std::vector<Cell*> cellsWithVehs = simMap->getCellsWithVehs();
		std::vector<int> newVehsSpeeds;
		std::vector<int> newVehsLanes;
		for (Cell* vehCell : cellsWithVehs) {
			int curVehSpeed = vehCell->getVehicle()->getSpeed();
			int newVehSpeed = 0;
			int newVehLane = 0;
			if (evalVehMove(vehCell, curVehSpeed, newVehSpeed, newVehLane, true) == false) {
				std::cout << "Collision foreseen" << std::endl;
				return;
			}
			newVehsSpeeds.push_back(newVehSpeed);
			newVehsLanes.push_back(newVehLane);
			if (1.0 * std::rand() / RAND_MAX <= randEventProb && newVehsSpeeds.back() > 0 && curVehSpeed <= newVehsSpeeds.back()) {
				newVehsSpeeds.back() -= 1;
			}
		}
		std::vector<Cell*> newCellsWithVehs = moveVehs(cellsWithVehs, newVehsSpeeds, newVehsLanes);
		std::vector<Generator*> generators = simMap->getGenerators();
		for (Generator* generator : generators) {
			if (generator->createVeh() == true) {
				newCellsWithVehs.push_back(generator);
			}
		}
		simMap->setcellsWithVehs(newCellsWithVehs);
	}

	std::string tempToString() {
		std::string simStr = "";
		for (Generator* generator : simMap->getGenerators()) {
			simStr += generator->tempToString();
		}
		for (Road* road : simMap->getRoads()) {
			simStr += road->tempToString();
		}
		return simStr += "\n";
	}

private:
	bool evalVehMove(Cell* vehCell, int curVehSpeed, int& newVehSpeed, int& newVehLane, bool canCallItself) {
		bool canSpeedUp = true;
		int speedLimit = std::numeric_limits<int>::max();
		Cell* tempCell = vehCell;
		for (int i = 1; i <= distToSearch[curVehSpeed]; i++) {
			tempCell = tempCell->getNextCell();
			if (tempCell == nullptr) {
				break;
			}
			if (i <= curVehSpeed && canSpeedUp == true && curVehSpeed >= tempCell->getMaxSpeed()) {
				canSpeedUp = false;
			}
			if (tempCell->getMaxSpeed() < speedLimit) {
				speedLimit = tempCell->getMaxSpeed();
				if ((int)(1.0 * (speedLimit + curVehSpeed + 1) / 2 * (curVehSpeed - speedLimit) + 0.5) > i - 1) {
					newVehSpeed = curVehSpeed - 1;
					newVehLane = 0;
					return true;
				}
				if (canSpeedUp == true && (int)(1.0 * (speedLimit + curVehSpeed + 2) / 2 * (curVehSpeed - speedLimit + 1) + 0.5) > i - 1) {
					canSpeedUp = false;
				}
			}
			if (tempCell->getVehicle() != nullptr) {
				//change road lane start
				if (tempCell->getVehicle()->checkIsObstacle() == true && canCallItself == true) {
					int laneRandomizer = std::rand() % 2;
					for (int j = 1; j <= 2; j++) {
						if ((j + laneRandomizer) % 2 == 0) {
							if (vehCell->getLeftCell() != nullptr && vehCell->getLeftCell()->getVehicle() == nullptr) {
								if (evalChangeLane(vehCell->getLeftCell(), curVehSpeed, newVehSpeed) == true) {
									newVehLane = -1;
									return true;
								}
							}
						}
						else {
							if (vehCell->getRightCell() != nullptr && vehCell->getRightCell()->getVehicle() == nullptr) {
								if (evalChangeLane(vehCell->getRightCell(), curVehSpeed, newVehSpeed) == true) {
									newVehLane = 1;
									return true;
								}
							}
						}
					}
				}
				//change road lane stop
				int nextVehSpeed = tempCell->getVehicle()->getSpeed();
				if (breakingDist[curVehSpeed] - breakingDist[std::max(nextVehSpeed - 1, 0)] > i - 1) {
					if (breakingDist[std::max(curVehSpeed - 1, 0)] - breakingDist[std::max(nextVehSpeed - 1, 0)] > i - 1) {
						return false;
					}
					newVehSpeed = curVehSpeed - 1;
					newVehLane = 0;
					return true;
				}
				if (canSpeedUp == true && breakingDist[curVehSpeed + 1] - breakingDist[std::max(nextVehSpeed - 1, 0)] <= i - 1) {
					newVehSpeed = curVehSpeed + 1;
					newVehLane = 0;
					return true;
				}
				canSpeedUp = false;
				break;
			}
		}
		if (canSpeedUp == true) {
			newVehSpeed = curVehSpeed + 1;
			newVehLane = 0;
		}
		else {
			newVehSpeed = curVehSpeed;
			newVehLane = 0;
		}
		return true;
	}

	bool evalChangeLane(Cell* vehCell, int curVehSpeed, int& newVehSpeed) {
		int speedLimit = std::numeric_limits<int>::max();
		Cell* tempCell = vehCell;
		for (int i = 1; i <= distToSearch[vehCell->getMaxSpeed()]; i++) {
			tempCell = tempCell->getPreviousCell();
			if (tempCell == nullptr) {
				break;
			}
			if (tempCell->getMaxSpeed() < speedLimit) {
				speedLimit = tempCell->getMaxSpeed();
			}
			if (tempCell->getVehicle() != nullptr) {
				int prevVehSpeed = tempCell->getVehicle()->getSpeed();
				if (breakingDist[std::max(curVehSpeed - 1, 0)] + i - 1 < breakingDist[std::min(prevVehSpeed + 1, speedLimit)] - (std::max(curVehSpeed - 1, 0) - std::min(prevVehSpeed + 1, speedLimit))) {
					return false;
				}
			}
		}
		int tempNewVehSpeed = 0;
		int tempNewVehLane = 0;
		if (evalVehMove(vehCell, curVehSpeed, tempNewVehSpeed, tempNewVehLane, false) == false) {
			return false;
		}
		tempNewVehSpeed = std::max(curVehSpeed - 1, tempNewVehSpeed);
		if (tempNewVehSpeed <= 0) {
			return false;
		}
		newVehSpeed = tempNewVehSpeed;
		return true;
	}

	std::vector<Cell*> moveVehs(std::vector<Cell*> cellsWithVehs, std::vector<int> newVehsSpeeds, std::vector<int> newVehsLanes) {
		std::vector<Cell*> newCellsWithVehs;
		std::vector<Vehicle*> vehs;
		std::vector<Cell*> vehsDestCells;
		for (unsigned int i = 0; i < cellsWithVehs.size(); i++) {
			if (newVehsSpeeds[i] == 0) {
				newCellsWithVehs.push_back(cellsWithVehs[i]);
				cellsWithVehs[i]->getVehicle()->setSpeed(0);
				continue;
			}
			bool isVehDeleted = false;
			Cell* tempCell = cellsWithVehs[i];
			if (newVehsLanes[i] == -1) {
				tempCell = tempCell->getLeftCell();
			}
			else if (newVehsLanes[i] == 1) {
				tempCell = tempCell->getRightCell();
			}
			for (int j = 0; j < newVehsSpeeds[i]; j++) {
				tempCell = tempCell->getNextCell();
				if (tempCell == nullptr) {
					cellsWithVehs[i]->getVehicle()->~Vehicle();
					cellsWithVehs[i]->setVehicle(nullptr);
					isVehDeleted = true;
					break;
				}
			}
			if (isVehDeleted == true) {
				continue;
			}
			cellsWithVehs[i]->getVehicle()->setSpeed(newVehsSpeeds[i]);
			vehs.push_back(cellsWithVehs[i]->getVehicle());
			cellsWithVehs[i]->setVehicle(nullptr);
			vehsDestCells.push_back(tempCell);
			newCellsWithVehs.push_back(tempCell);
		}
		for (unsigned int i = 0; i < vehs.size(); i++) {
			vehsDestCells[i]->setVehicle(vehs[i]);
		}
		return newCellsWithVehs;
	}
};