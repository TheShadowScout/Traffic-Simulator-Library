#pragma once

#include "Simulation.h"

Simulation::Simulation(Map* simMap, double randEventProb) : simMap(simMap), randEventProb(randEventProb), simStats(nullptr) {}

Map* Simulation::getSimulationMap() {
	return simMap;
}

Statistics* Simulation::getSimulationStatistics() {
	return simStats;
}

Observer* Simulation::getSimulationObserver()
{
	return observers[0];
}

std::string Simulation::toString() {
	std::string simStr = "";
	for (Generator* generator : simMap->getGenerators()) {
		simStr += generator->toString();
	}
	for (Road* road : simMap->getRoads()) {
		simStr += road->toString();
	}
	return simStr += "\n";
}

void Simulation::addObserver(Observer* observer) {
	observers.push_back(observer);
}

void Simulation::saveStatisticsToFile(std::string outFolder) {
	std::string simInitiationTime = simStats->getSimInitiationTime();
	std::string tempSimInitiationTime = "";
	for (char character : simInitiationTime) {
		if (character >= '0' && character <= '9') {
			tempSimInitiationTime += character;
		}
	}
	std::ofstream file_out;
	file_out.open(outFolder + tempSimInitiationTime + "_simulation_statistics" + ".csv");
	file_out << simStats->toString();
	file_out.close();
	for (Observer* observer : observers) {
		std::ofstream file_out;
		file_out.open(outFolder + tempSimInitiationTime + "_observer_" + observer->getName() + "_statistics" + ".csv");
		file_out << observer->toString();
		file_out.close();
	}
}

void Simulation::initiateSimulation() {
	simStats = new Statistics(randEventProb, simMap->getMapPassableCellsCnt());
	simStats->updateStatistics(simMap->getCellsWithVehs());
	for (Observer* observer : observers) {
		observer->checkVehPassing();
	}
}

void Simulation::transitionFunc() {
	std::vector<Cell*> cellsWithVehs = simMap->getCellsWithVehs();
	std::vector<MovePrediction> vehsMovesData;
	for (Cell* vehCell : cellsWithVehs) {
		int curVehSpeed = vehCell->getVehicle()->getSpeed();
		vehsMovesData.push_back(evalVehMove(vehCell, curVehSpeed));
		//if (vehsMovesData.back().getUtilFlag() == false) {
		//	std::cout << "Collision foreseen" << std::endl;
		//	return;
		//}
		int newVehSpeed = vehsMovesData.back().getNewVehSpeed();
		int newVehLane = vehsMovesData.back().getNewVahLane();
		if (1.0 * std::rand() / RAND_MAX <= randEventProb && newVehSpeed > 0 && curVehSpeed <= newVehSpeed && newVehLane == 0) {
			vehsMovesData.back().setNewVehSpeed(newVehSpeed - 1);
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

MovePrediction Simulation::evalVehMove(Cell* vehCell, int curVehSpeed) {
	int newVehSpeed = curVehSpeed + 1;
	int distToSearch = curVehSpeed + 1;
	int vehCellMaxSpeed = vehCell->getMaxSpeed();
	if (curVehSpeed >= vehCellMaxSpeed) {
		newVehSpeed = vehCellMaxSpeed;
		distToSearch = vehCellMaxSpeed;
	}
	Cell* tempCell = vehCell;
	int tempCellMaxSpeed = NULL;
	for (int i = 1; i <= vehCellMaxSpeed; i++) {
		tempCell = tempCell->getNextCell();
		if (tempCell == nullptr) {
			break;
		}
		tempCellMaxSpeed = tempCell->getMaxSpeed();
		if (curVehSpeed >= tempCellMaxSpeed) {
			newVehSpeed = std::min(newVehSpeed, std::max(tempCellMaxSpeed, i));
		}
		if (tempCell->getVehicle() != nullptr) {
			newVehSpeed = std::min(newVehSpeed, i - 1);
			break;
		}
	}
	return MovePrediction(true, newVehSpeed, 0);
}

std::vector<Cell*> Simulation::moveVehs(std::vector<Cell*> cellsWithVehs, std::vector<MovePrediction> vehMovesData) {
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
		/*
		if (vehMovesData[i].getNewVahLane() == -1) {
			tempCell = tempCell->getLeftCell();
			curVeh->setOriginLane(curVeh->getOriginLane() + 1);
		}
		else if (vehMovesData[i].getNewVahLane() == 1) {
			tempCell = tempCell->getRightCell();
			curVeh->setOriginLane(curVeh->getOriginLane() - 1);
		}
		*/
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
	/*
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
	*/
	return newCellsWithVehs;
}
