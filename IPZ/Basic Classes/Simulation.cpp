#pragma once

#include "Simulation.h"

Simulation::Simulation(Map* simMap, double randEventProb,  int minSafeSpace, int seed, bool shuffleIfCompetition) : simMap(simMap), randEventProb(randEventProb), minSafeSpace(minSafeSpace), seed(seed), shuffleIfCompetition(shuffleIfCompetition), simStats(nullptr) {
	if (seed == NULL) {
		randomEngine = std::default_random_engine(seed);
	}
	else {
		randomEngine = std::default_random_engine(std::rand());
	}
	if(randEventProb < 0 || randEventProb > 1)
		throw std::invalid_argument("Random event probability must be in range between 0 and 1");
}

Map* Simulation::getSimulationMap() {
	return simMap;
}

Statistics* Simulation::getSimulationStatistics() {
	return simStats;
}

Observer* Simulation::getSimulationObserver() {
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
	for (Crossing* crossing : simMap->getCrossings()) {
		simStr += crossing->toString();
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
	cellsWithVehs = simMap->getCellsWithVehs();
	simMap->updateMap(&cellsWithVehs);
	simStats->updateStatistics(cellsWithVehs);
	for (Observer* observer : observers) {
		observer->checkVehPassing();
	}
}

void Simulation::transitionFunc() {
	std::vector<MoveData> vehsMovesData;
	for (Cell* vehCell : cellsWithVehs) {
		vehsMovesData.push_back(evalVehMove(vehCell)); //wyznacz now� pr�dko�� dla ka�dego pojazdu
		evalRandomEvent(vehCell , &vehsMovesData.back());
	}
	std::vector<Cell*> newCellsWithVehs = moveVehs(cellsWithVehs, vehsMovesData); //poryszenie pojazd�w
	simMap->updateMap(&newCellsWithVehs);
	cellsWithVehs = newCellsWithVehs;
	simStats->updateStatistics(cellsWithVehs);
	for (Observer* observer : observers) { //aktualizacja obserwator�w
		observer->checkVehPassing();
	}
}

MoveData Simulation::evalVehMove(Cell* vehCell) {
	std::vector<MoveData> moves;
	bool sawObstacle = false;
	int curVehSpeed = vehCell->getVehicle()->getSpeed();
	SpeedData speedDataFront = evalNewVehSpeed(vehCell, curVehSpeed, &sawObstacle); //wyliczenie pr�dko�ci przy je�dzie prosto
	if (sawObstacle == true) { //je�li widzia� przeszkod� zmniejsz priorytet jazdy prosto
		moves.push_back(MoveData{ speedDataFront, 0 });
	}
	evalChangeLane(vehCell, &moves); //wylicznie zmiany pasa
	if (sawObstacle == false) { //je�li nie widzia� przeszkody zwi�ksz priorytet jazdy prosto
		moves.push_back(MoveData{ speedDataFront, 0 });
	}
	std::stable_sort(moves.begin(), moves.end(), cmpMoveData); //posortuj mozliwe ruchy rosn�co zachowujac priorytety -> kolejno�� dodania
	//std::cout << moves.size() << std::endl;
	return moves.back(); //wybierz najlepszy ruch
}

SpeedData Simulation::evalNewVehSpeed(Cell* startCell, int curVehSpeed, bool* sawObstacle) { //funkcja wyliczaj�ca now� pr�dko�� dla pojazdu
	Vehicle* startCellVeh = startCell->getVehicle();
	if (startCellVeh != nullptr) {
		if (startCellVeh->getIsObstacle() == true) {
			return SpeedData{ 0, startCell };
		}
	}
	int newVehSpeed = std::min(curVehSpeed + 1, startCell->getMaxSpeed()); //nowa pr�dko�� pojazdu, na pocz�tku ustalana na maksymaln� mo�liw� do uzyskania warto�� - maksymaln� pr�dko�� dla kom�rki w kt�rej si� znajduje, w czasie
											  //dzia�ania funkcji mo�e by� tylko obni�ana
	Cell* tempCell = startCell;
	int tempCellMaxSpeed = NULL;
	TrafficLights* vehCellLights = startCell->getLight();
	if (vehCellLights != nullptr && vehCellLights->getColor() != LightColor::green) 	{
		return SpeedData{ 0, startCell };
	}
	for (int i = 1; i <= newVehSpeed; i++) { //przeszukaj ilo�� kolejnych kom�rek zale�n� od pr�dko�ci pojazdu w poszukiwaniu sytuacji obni�aj�cych pr�dko��, maksymalna ich ilo�� mo�e si� zmniejsza�
											 //wraz z dzia�aniem funkcji
		tempCell = tempCell->getNextCell();
		if (tempCell == nullptr) { //napotkana kom�rka nie istniej - nic nie ograniczy ju� pr�dko�ci
			break;
		}
		if (sawObstacle != nullptr && *sawObstacle == false && tempCell->getObstacleAhead() == true) {
			*sawObstacle = true;
		}
		tempCellMaxSpeed = tempCell->getMaxSpeed();
		if (newVehSpeed > tempCellMaxSpeed) { //napotkana kom�rka ma ograniczenie pr�dko�ci ni�sze ni� aktualnie wyliczana pr�dko�� - ograniczenie pr�dko�ci do zapewniaj�cej mksymaln� mo�liw� pr�dko��
			newVehSpeed = std::min(newVehSpeed, std::max(tempCellMaxSpeed, i));
		}
		Vehicle* tempCellVeh = tempCell->getVehicle();
		if (tempCellVeh != nullptr) { //w napotkanej kom�rce jest pojazd, trzeba zmniejszy� pr�dko�� - dalej nie ma sensu szuka�
			newVehSpeed = i - 1;
			if (sawObstacle != nullptr && tempCellVeh->getIsObstacle() == true) {
				*sawObstacle = true;
			}
			tempCell = tempCell->getPreviousCell();
			break;
		}
		if (tempCell->getLight() != nullptr && tempCell->getLight()->getColor() != LightColor::green) {
			newVehSpeed = i;
			break;
		}
	}
	return SpeedData{ newVehSpeed, tempCell };
}

void Simulation::evalChangeLane(Cell* vehCell, std::vector<MoveData>* moves) { //funkcja wyliczaj�ca zmian� pasa
	int curVehSpeed = vehCell->getVehicle()->getSpeed();
	Cell* tempCell;
	int newLane;
	bool sawObstacle = false;
	int laneRandomizer = std::rand() % 2;
	for (int random_const = 1; random_const <= 2; random_const++) { //losowanie kolejno�ci sprawdzania pasa lewego i prawego
		if ((random_const + laneRandomizer) % 2 == 0) {
			tempCell = vehCell->getLeftCell();
			newLane = -1;
		}
		else {
			tempCell = vehCell->getRightCell();
			newLane = 1;
		}
		if (tempCell != nullptr && tempCell->getVehicle() == nullptr) {
			SpeedData newVehSpeed = evalNewVehSpeed(tempCell, curVehSpeed, &sawObstacle); //ustal pr�dko�� pojazdu po zmianie  pasa
			if (sawObstacle == true) { //je�li na pasie jest przeszkoda zrezygnuj ze zmiany pasa
				continue;
			}
			int prevVehDist = -6;
			for (int i = -1; i >= -6; i--) { //przeszukaj 6 kom�rek w ty� w poszukiwaniu pojazdu poprzedzaj�cego
				tempCell = tempCell->getPreviousCell();
				if (tempCell == nullptr) {
					break;
				}
				Vehicle* tempVeh = tempCell->getVehicle();
				if (tempVeh != nullptr) { //je�li pojazd poprzedzaj�cy zosta� znaleziony oblicz jego przysz�a pr�dko��
					prevVehDist = i + evalNewVehSpeed(tempCell, tempVeh->getSpeed(), nullptr).newVehSpeed; // oblicz odle�o�� w jakiej b�dzie pojazd poprzedzaj�cy po wykonaniu ruchu w stosunku do pojazdu zmieniaj�cego pas
					break;
				}
			}
			if (newVehSpeed.newVehSpeed - prevVehDist - 1 > minSafeSpace) { // jesli odleg�o�� mi�dzy pojazdami jest wi�ksza lub r�wna od minimalnej to dodaj ruch do listy mo�liwych
				moves->push_back(MoveData{ newVehSpeed, newLane });
			}
		}
	}
}

void Simulation::evalRandomEvent(Cell* vehCell, MoveData* vehMoveData) {
	int newVehSpeed = vehMoveData->speedData.newVehSpeed;
	if (1.0 * std::rand() / RAND_MAX <= randEventProb && newVehSpeed != 0 &&vehCell->getVehicle()->getSpeed() <= newVehSpeed && vehMoveData->newVehLane == 0 && vehMoveData->speedData.destinationCell != nullptr) {
		vehMoveData->speedData.newVehSpeed -= 1;
		vehMoveData->speedData.destinationCell = vehMoveData->speedData.destinationCell->getPreviousCell();
	}
}

std::vector<Cell*> Simulation::moveVehs(std::vector<Cell*> cellsWithVehs, std::vector<MoveData> vehMovesData) {
	std::vector<Cell*> newCellsWithVehs;
	bool competition = false;
	for (unsigned int i = 0; i < cellsWithVehs.size(); i++) {
		Vehicle* curVeh = cellsWithVehs[i]->getVehicle();
		int newVehSpeed = vehMovesData[i].speedData.newVehSpeed;
		Cell* destinationCell = vehMovesData[i].speedData.destinationCell;
		if (newVehSpeed == 0) {
			newCellsWithVehs.push_back(cellsWithVehs[i]);
			curVeh->setSpeed(0);
			continue;
		}
		if (destinationCell == nullptr) {
			delete curVeh;
			cellsWithVehs[i]->setVehicle(nullptr);
			continue;
		}
		if (destinationCell->getVehicle() == nullptr) {
			curVeh->setSpeed(newVehSpeed);
			cellsWithVehs[i]->setVehicle(nullptr);
			destinationCell->setVehicle(curVeh);
			newCellsWithVehs.push_back(destinationCell);
		}
		else {
			SpeedData speedData = evalNewVehSpeed(cellsWithVehs[i], curVeh->getSpeed(), nullptr);
			curVeh->setSpeed(speedData.newVehSpeed);
			cellsWithVehs[i]->setVehicle(nullptr);
			speedData.destinationCell->setVehicle(curVeh);
			newCellsWithVehs.push_back(speedData.destinationCell);
			if (competition == false) {
				competition = true;
			}
		}
	}
	if (competition == true && shuffleIfCompetition == true) {
		std::shuffle(newCellsWithVehs.begin(), newCellsWithVehs.end(), randomEngine);
	}
	return newCellsWithVehs;
}



bool cmpMoveData(MoveData lhs, MoveData rhs) {
	return lhs.speedData.newVehSpeed < rhs.speedData.newVehSpeed;
}