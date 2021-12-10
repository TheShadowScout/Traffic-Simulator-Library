#pragma once

#include <cstdlib>

#include "Map.h"
#include "Cell.h"

class Simulation {
protected:
	int distToSearch[7] = { 1, 3, 6, 10, 15, 21, 28 };
	int ariSeqSum[8] = { 0, 0, 1, 3, 6, 10, 15, 21 };
	Map* simMap = nullptr;

public:
	Simulation(Map* simulationMap) : simMap(simulationMap) {}

	void transitionFunc() {
		vector<Cell*> cellsWithVehs = simMap->getCellsWithVehs();
		vector<int> newVehsSpeeds;
		for (Cell* vehCell : cellsWithVehs) {
			newVehsSpeeds.push_back(evalNewVehSpeed(vehCell));
		}
		simMap->setCellsWithVehs(moveVehs(cellsWithVehs, newVehsSpeeds));
	}

private:
	int evalNewVehSpeed(Cell* vehCell) {
		int curVehSpeed = vehCell->getVehicle()->getSpeed();
		bool canSpeedUp = true;
		int speedLimit = std::numeric_limits<int>::max();
		Cell* tempCell = vehCell;
		int randEvent = 0;
		if (std::rand() % 100 + 1 <= 20) {
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

	vector<Cell*> moveVehs(vector<Cell*> cellsWithVehs, vector<int> newVehsSpeeds) {
		vector<Cell*> newCellsWithVehs;
		vector<Vehicle*> vehs;
		vector<Cell*> vehsDestCells;
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