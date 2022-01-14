#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>

#include "Map.h"
#include "Cell.h"
#include "Vehicle.h"
#include "MovePrediction.h"
#include "Statistics.h"
#include "Observer.h"

class Simulation {
protected:
	int distToSearch[7] = { 1, 3, 6, 10, 15, 21, 28 };
	int breakingDist[7] = { 0, 1, 3, 6, 10, 15, 21 };
	double randEventProb;
	Map* simMap;
	Statistics* simStats;
	std::vector<Observer*> observers;

public:
	Simulation(Map* simMap, double randEventProb) : simMap(simMap), randEventProb(randEventProb), simStats(nullptr) {}

	void addObserver(Observer* observer) {
		observers.push_back(observer);
	}

	void initiateSimulation() {
		simStats = new Statistics(randEventProb, simMap->getMapPassableCellsCnt());
		simStats->updateStatistics(simMap->getCellsWithVehs());
		for (Observer* observer : observers) {
			observer->checkVehPassing();
		}
	}

	void saveStatisticsToFile(std::string outFolder = "StatisticsHistory/") {
		std::string simInitiationTime = simStats->getSimInitiationTime();
		std::string tempSimInitiationTime = "";
		for (char character : simInitiationTime) {
			if (character >= '0' && character <= '9') {
				tempSimInitiationTime += character;
			}
		}
		std::ofstream file_out;
		file_out.open(outFolder + "simulation_statistics_" + tempSimInitiationTime + ".csv");
		file_out << simStats->toString();
		file_out.close();
		for (Observer* observer : observers) {
			std::ofstream file_out;
			file_out.open(outFolder + "observer_" + observer->getName() + "_statistics_" + tempSimInitiationTime + ".csv");
			file_out << observer->toString();
			file_out.close();
		}
	}

	void transitionFunc() {
		std::vector<Cell*> cellsWithVehs = simMap->getCellsWithVehs();
		std::vector<MovePrediction> vehsMovesData;
		for (Cell* vehCell : cellsWithVehs) {
			int curVehSpeed = vehCell->getVehicle()->getSpeed();
			vehsMovesData.push_back(evalVehMove(vehCell, curVehSpeed, true));
			//if (vehsMovesData.back().getUtilFlag() == false) {
			//	std::cout << "Collision foreseen" << std::endl;
			//	return;
			//}
			int newVehSpeed = vehsMovesData.back().getNewVehSpeed();
			if (1.0 * std::rand() / RAND_MAX <= randEventProb && newVehSpeed > 0 && curVehSpeed <= newVehSpeed) {
				vehsMovesData.back().setNewVehSpeed(newVehSpeed  - 1);
			}
		}
		std::vector<Cell*> newCellsWithVehs = moveVehs(cellsWithVehs, vehsMovesData);
		std::vector<Generator*> generators = simMap->getGenerators();
		for (Generator* generator : generators) {
			if (generator->createVeh() == true) {
				newCellsWithVehs.push_back(generator);
			}
		}
		simMap->setCellsWithVehs(newCellsWithVehs);
		simStats->updateStatistics(simMap->getCellsWithVehs());
		for (Observer* observer : observers) {
			observer->checkVehPassing();
		}
	}

	std::string toString() {
		std::string simStr = "";
		for (Generator* generator : simMap->getGenerators()) {
			simStr += generator->toString();
		}
		for (Road* road : simMap->getRoads()) {
			simStr += road->toString();
		}
		return simStr += "\n";
	}

private:
	MovePrediction evalVehMove(Cell* vehCell, int curVehSpeed, bool canCallItself) {
		bool canSpeedUp = true;
		int speedLimit = std::numeric_limits<int>::max();
		Cell* tempCell = vehCell;
		for (int i = 1; i <= distToSearch[curVehSpeed]; i++) {
			tempCell = tempCell->getNextCell();
			if (tempCell == nullptr) {
				break;
			}
			int tempCellMaxSpeed = tempCell->getMaxSpeed();
			if (i <= curVehSpeed && canSpeedUp == true && curVehSpeed >= tempCellMaxSpeed) {
				canSpeedUp = false;
			}
			if (tempCellMaxSpeed < speedLimit) {
				speedLimit = tempCellMaxSpeed;
				if (((speedLimit + curVehSpeed) * (curVehSpeed - speedLimit) + 1) / 2 > i - 1) {
					return MovePrediction(true, curVehSpeed - 1, 0);
				}
				if (((speedLimit + curVehSpeed + 1) * (curVehSpeed - speedLimit + 1) + 1) / 2 > i - 1) {
					canSpeedUp = false;
				}
			}
			Vehicle* tempCellVeh = tempCell->getVehicle();
			if (tempCellVeh != nullptr) {
				//change road lane start
				if (tempCellVeh->getIsObstacle() == true && canCallItself == true) {
					int laneRandomizer = std::rand() % 2;
					for (int j = 1; j <= 2; j++) {
						if ((j + laneRandomizer) % 2 == 0) {
							Cell* leftCell = vehCell->getLeftCell();
							if (leftCell != nullptr && leftCell->getVehicle() == nullptr) {
								MovePrediction tempMoveData = evalChangeLane(leftCell, curVehSpeed);
								if (tempMoveData.getUtilFlag() == true) {
									return MovePrediction(true, tempMoveData.getNewVehSpeed(), -1);
								}
							}
						}
						else {
							Cell* rightCell = vehCell->getRightCell();
							if (rightCell != nullptr && rightCell->getVehicle() == nullptr) {
								MovePrediction tempMoveData = evalChangeLane(rightCell, curVehSpeed);
								if (tempMoveData.getUtilFlag() == true) {
									return MovePrediction(true, tempMoveData.getNewVehSpeed(), 1);
								}
							}
						}
					}
				}
				//change road lane stop
				int nextVehSpeed = tempCellVeh->getSpeed();
				if (breakingDist[curVehSpeed] - breakingDist[std::max(nextVehSpeed - 1, 0)] > i - 1) {
					if (breakingDist[std::max(curVehSpeed - 1, 0)] - breakingDist[std::max(nextVehSpeed - 1, 0)] > i - 1) {
						return MovePrediction(false, 0, 0);
					}
					return MovePrediction(true, curVehSpeed - 1, 0);
				}
				if (canSpeedUp == true && breakingDist[curVehSpeed + 1] - breakingDist[std::max(nextVehSpeed - 1, 0)] <= i - 1) {
					return MovePrediction(true, curVehSpeed + 1, 0);
				}
				canSpeedUp = false;
				break;
			}
		}
		if (canSpeedUp == true) {
			return MovePrediction(true, curVehSpeed + 1, 0);
		}
		return MovePrediction(true, curVehSpeed, 0);
	}

	MovePrediction evalChangeLane(Cell* vehCellAdjacentCell, int curVehSpeed) {
		int speedLimit = std::numeric_limits<int>::max();
		Cell* tempCell = vehCellAdjacentCell;
		for (int i = 1; i <= distToSearch[vehCellAdjacentCell->getMaxSpeed()]; i++) {
			tempCell = tempCell->getPreviousCell();
			if (tempCell == nullptr) {
				break;
			}
			int tempCellMaxSpeed = tempCell->getMaxSpeed();
			if (tempCellMaxSpeed < speedLimit) {
				speedLimit = tempCellMaxSpeed;
			}
			if (tempCell->getVehicle() != nullptr) {
				int prevVehSpeed = tempCell->getVehicle()->getSpeed();
				if (std::max(curVehSpeed - 1, 0) - std::min(prevVehSpeed + 1, speedLimit) + i - 1 < breakingDist[std::min(prevVehSpeed + 1, speedLimit)] - breakingDist[std::max(curVehSpeed - 1, 0)]) {
					return MovePrediction(false, 0, 0);
				}
			}
		}
		MovePrediction tempMoveData = evalVehMove(vehCellAdjacentCell, curVehSpeed, false);
		if (tempMoveData.getUtilFlag() == false) {
			return MovePrediction(false, 0, 0);
		}
		int newVehSpeed = std::max(curVehSpeed - 1, tempMoveData.getNewVehSpeed());
		if (newVehSpeed <= 0) {
			return MovePrediction(false, 0, 0);
		}
		newVehSpeed = newVehSpeed;
		return MovePrediction(true, newVehSpeed, 0);
	}

	std::vector<Cell*> moveVehs(std::vector<Cell*> cellsWithVehs, std::vector<MovePrediction> vehMovesData) {
		std::vector<Cell*> newCellsWithVehs;
		std::vector<Vehicle*> vehs;
		std::vector<Cell*> vehsDestCells;
		for (unsigned int i = 0; i < cellsWithVehs.size(); i++) {
			int newVehSpeed = vehMovesData[i].getNewVehSpeed();
			Vehicle* curVeh = cellsWithVehs[i]->getVehicle();
			if (newVehSpeed == 0) {
				newCellsWithVehs.push_back(cellsWithVehs[i]);
				curVeh->setSpeed(0);
				continue;
			}
			bool isVehDeleted = false;
			Cell* tempCell = cellsWithVehs[i];
			if (vehMovesData[i].getNewVahLane() == -1) {
				tempCell = tempCell->getLeftCell();
				curVeh->setOriginLane(curVeh->getOriginLane() + 1);
			}
			else if (vehMovesData[i].getNewVahLane() == 1) {
				tempCell = tempCell->getRightCell();
				curVeh->setOriginLane(curVeh->getOriginLane() - 1);
			}
			for (int j = 0; j < newVehSpeed; j++) {
				tempCell = tempCell->getNextCell();
				if (tempCell == nullptr) {
					curVeh->~Vehicle();
					cellsWithVehs[i]->setVehicle(nullptr);
					isVehDeleted = true;
					break;
				}
			}
			if (isVehDeleted == true) {
				continue;
			}
			curVeh->setSpeed(newVehSpeed);
			vehs.push_back(curVeh);
			cellsWithVehs[i]->setVehicle(nullptr);
			vehsDestCells.push_back(tempCell);
			newCellsWithVehs.push_back(tempCell);
		}
		for (unsigned int i = 0; i < vehs.size(); i++) {
			vehsDestCells[i]->setVehicle(vehs[i]);
		}
		for (unsigned int i = 0; i < vehsDestCells.size(); i++) {
			Vehicle* curVeh = vehsDestCells[i]->getVehicle();
			int curVehOriginLane = curVeh->getOriginLane();
			if (curVehOriginLane != 0) {
				if (curVehOriginLane > 0) {
					if (vehsDestCells[i]->getRightCell() == nullptr) {
						curVeh->setOriginLane(0);
					}
				}
				if (curVehOriginLane < 0) {
					if (vehsDestCells[i]->getLeftCell() == nullptr) {
						curVeh->setOriginLane(0);
					}
				}
			}
		}
		return newCellsWithVehs;
	}
};