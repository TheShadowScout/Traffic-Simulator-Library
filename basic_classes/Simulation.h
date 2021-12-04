#pragma once

#include <list>
#include <limits>
#include <cstdlib>

#include "Map.h"
#include "Cell.h"

class Simulation {
protected:
	int distToSearch[7] = { 1, 3, 6, 10, 15, 21, 28 };
	int ariSeqSum[8] = { 0, 0, 1, 3, 6, 10, 15, 21 };
	Map* simulationMap = nullptr;

	Simulation(Map* simulationMap) : simulationMap(simulationMap) {}

	void transitionFunc() {
		vector<Cell*> cellsWithCars = simulationMap->getCellsWithCars();
		vector<int> newCarSpeeds;
		for (Cell* carCell : cellsWithCars) {
			newCarSpeeds.push_back(evalNewCarSpeed(carCell));
		}
		simulationMap->setCellsWithCars(moveCars(cellsWithCars, newCarSpeeds));
	}

private:
	int evalNewCarSpeed(Cell* carCell) {
		int curCarSpeed = carCell->getVehicle()->getSpeed();
		bool canSpeedUp = true;
		int speedLimit = std::numeric_limits<int>::max();
		Cell* tempCell = carCell;
		int randEvent = 0;
		if (std::rand() % 100 + 1 <= 20) {
			randEvent = -1;
		}
		for (int i = 1; i <= distToSearch[curCarSpeed]; i++) {
			tempCell = tempCell->getNextCell();
			if (tempCell == nullptr) {
				break;
			}
			if (i <= curCarSpeed && canSpeedUp == true && curCarSpeed >= tempCell->getMaxSpeed()) {
				canSpeedUp = false;
			}
			if (tempCell->getMaxSpeed() < speedLimit) {
				speedLimit = tempCell->getMaxSpeed();
				if ((int)(1.0 * (speedLimit + curCarSpeed + 1) / 2 * (curCarSpeed - speedLimit) + 0.5) > i - 1) {
					return curCarSpeed - 1;
				}
				if (canSpeedUp == true && (int)(1.0 * (speedLimit + curCarSpeed + 2) / 2 * (curCarSpeed - speedLimit + 1) + 0.5) > i - 1) {
					canSpeedUp = false;
				}
			}
			if (tempCell->getVehicle() != nullptr) {
				int nextCarSpeed = tempCell->getVehicle()->getSpeed();
				if (ariSeqSum[curCarSpeed + 1] - ariSeqSum[nextCarSpeed] > i - 1) {
					return curCarSpeed - 1;
				}
				if (canSpeedUp == true && ariSeqSum[curCarSpeed + 2] - ariSeqSum[nextCarSpeed] <= i - 1) {
					return curCarSpeed + 1 + randEvent;
				}
				if (curCarSpeed > 0) {
					return curCarSpeed + randEvent;
				}
				else {
					return curCarSpeed;
				}		
			}
		}
		if (canSpeedUp == true) {
			return curCarSpeed + 1 + randEvent;
		}
		else {
			if (curCarSpeed > 0) {
				return curCarSpeed + randEvent;
			}
			else {
				return curCarSpeed;
			}
		}
	}

	vector<Cell*> moveCars(vector<Cell*> cellsWithCars, vector<int> newCarSpeeds) {
		vector<Cell*> newCellsWithCars;
		vector<Vehicle*> cars;
		vector<Cell*> carsDestCells;
		for (unsigned int i = 0; i < cellsWithCars.size(); i++) {
			if (newCarSpeeds[i] == 0) {
				newCellsWithCars.push_back(cellsWithCars[i]);
				cellsWithCars[i]->getVehicle()->setSpeed(0);
				continue;
			}
			bool carDeleted = false;
			Cell* tempCell = cellsWithCars[i];
			for (int j = 0; j < newCarSpeeds[i]; j++) {
				tempCell = tempCell->getNextCell();
				if (tempCell == nullptr) {
					cellsWithCars[i]->getVehicle()->~Vehicle();
					cellsWithCars[i]->setVehicle(nullptr);
					carDeleted = true;
					break;
				}
			}
			if (carDeleted == true) {
				continue;
			}
			cellsWithCars[i]->getVehicle()->setSpeed(newCarSpeeds[i]);
			cars.push_back(cellsWithCars[i]->getVehicle());
			cellsWithCars[i]->setVehicle(nullptr);
			carsDestCells.push_back(tempCell);
			newCellsWithCars.push_back(tempCell);
		}
		for (unsigned int i = 0; i < cars.size(); i++) {
			carsDestCells[i]->setVehicle(cars[i]);
		}
		return newCellsWithCars;
	}
};