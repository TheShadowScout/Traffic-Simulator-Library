#pragma once

#include <cstdlib>
#include <vector>
#include <string>

#include "basic_classes/Map.h"
#include "basic_classes/Cell.h"

class Simulation {
protected:
	int distToSearch[7] = { 1, 3, 6, 10, 15, 21, 28 };
	int ariSeqSum[8] = { 0, 0, 1, 3, 6, 10, 15, 21 };
	double randEventProb;
	Map* simMap;

public:
	Simulation(Map* simMap, double randEventProb) : simMap(simMap), randEventProb(randEventProb) {}

	void transitionFunc() {
		std::vector<Cell*> cellsWithVehs = simMap->getcellsWithVehs();
		std::vector<int> newVehsSpeeds;
		for (Cell* vehCell : cellsWithVehs) {
			newVehsSpeeds.push_back(evalNewVehSpeed(vehCell));
		}
		std::vector<Cell*> newCellsWithVehs = moveVehs(cellsWithVehs, newVehsSpeeds);
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
	int evalNewVehSpeed(Cell* vehCell) {
		int curVehSpeed = vehCell->getVehicle()->getSpeed();
		bool canSpeedUp = true;
		int speedLimit = std::numeric_limits<int>::max();
		Cell* tempCell = vehCell;
		int randEvent = 0;
		if (1.0 * std::rand() / RAND_MAX <= randEventProb) {
			randEvent = -1;
		}
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
					return curVehSpeed - 1;
				}
				if (canSpeedUp == true && (int)(1.0 * (speedLimit + curVehSpeed + 2) / 2 * (curVehSpeed - speedLimit + 1) + 0.5) > i - 1) {
					canSpeedUp = false;
				}
			}
			if (tempCell->getVehicle() != nullptr) {
				int nextVehSpeed = tempCell->getVehicle()->getSpeed();
				if (ariSeqSum[curVehSpeed + 1] - ariSeqSum[nextVehSpeed] > i - 1) {
					return curVehSpeed - 1;
				}
				if (canSpeedUp == true && ariSeqSum[curVehSpeed + 2] - ariSeqSum[nextVehSpeed] <= i - 1) {
					return curVehSpeed + 1 + randEvent;
				}
				if (curVehSpeed > 0) {
					return curVehSpeed + randEvent;
				}
				else {
					return curVehSpeed;
				}		
			}
		}
		if (canSpeedUp == true) {
			return curVehSpeed + 1 + randEvent;
		}
		else {
			if (curVehSpeed > 0) {
				return curVehSpeed + randEvent;
			}
			else {
				return curVehSpeed;
			}
		}
	}

	std::vector<Cell*> moveVehs(std::vector<Cell*> cellsWithVehs, std::vector<int> newVehsSpeeds) {
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