#pragma once

#include "Simulation.h"

Simulation::Simulation(Map* simMap, double randEventProb,  int minSafeSpace, bool shuffleIfCompetition) : simMap(simMap), randEventProb(randEventProb), minSafeSpace(minSafeSpace), shuffleIfCompetition(shuffleIfCompetition), simStats(nullptr), randomEngine(std::default_random_engine(0)) {
	if (randEventProb < 0.0 || randEventProb > 1.0) {
		throw std::invalid_argument("Random event probability must be in range between 0 and 1");
	}
}

Map* Simulation::getSimulationMap() {
	return simMap;
}

Statistics* Simulation::getSimulationStatistics() {
	return simStats;
}

std::vector<Observer*> Simulation::getSimulationObservers() {
	return observers;
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
	simStats = new Statistics(randEventProb, minSafeSpace, simMap->getMapPassableCellsCnt());
	cellsWithVehs = simMap->getCellsWithVehs();
	simMap->updateMap(&cellsWithVehs);
	simStats->updateStatistics(cellsWithVehs);
	for (Observer* observer : observers) {
		observer->checkVehPassing();
	}
}

void Simulation::transitionFunc() {
	std::vector<Cell*> newCellsWithVehs;
	simMap->updateMap(&newCellsWithVehs);
	std::vector<MoveData> vehsMovesData;
	for (Cell* vehCell : cellsWithVehs) {
		vehsMovesData.push_back(evalVehMove(vehCell)); //wyznacz now¹ prêdkoœæ dla ka¿dego pojazdu
		evalRandomEvent(vehCell , &vehsMovesData.back());
	}
	std::vector<Cell*> tempNewCellsWithVehs = moveVehs(cellsWithVehs, vehsMovesData); //poryszenie pojazdów
	newCellsWithVehs.insert(newCellsWithVehs.end(), tempNewCellsWithVehs.begin(), tempNewCellsWithVehs.end());
	cellsWithVehs = newCellsWithVehs;
	simStats->updateStatistics(cellsWithVehs);
	for (Observer* observer : observers) { //aktualizacja obserwatorów
		observer->checkVehPassing();
	}
}

MoveData Simulation::evalVehMove(Cell* vehCell) {
	std::vector<MoveData> moves;
	bool sawObstacle = false;
	int curVehSpeed = vehCell->getVehicle()->getSpeed();
	SpeedData speedDataFront = evalNewVehSpeed(vehCell, curVehSpeed, &sawObstacle); //wyliczenie prêdkoœci przy jeŸdzie prosto
	if (sawObstacle == true) { //jeœli widzia³ przeszkodê zmniejsz priorytet jazdy prosto
		moves.push_back(MoveData{ speedDataFront, 0 });
	}
	evalChangeLane(vehCell, &moves); //wylicznie zmiany pasa
	if (sawObstacle == false) { //jeœli nie widzia³ przeszkody zwiêksz priorytet jazdy prosto
		moves.push_back(MoveData{ speedDataFront, 0 });
	}
	std::stable_sort(moves.begin(), moves.end(), cmpMoveData); //posortuj mozliwe ruchy rosn¹co zachowujac priorytety -> kolejnoœæ dodania
	//std::cout << moves.size() << std::endl;
	return moves.back(); //wybierz najlepszy ruch
}

SpeedData Simulation::evalNewVehSpeed(Cell* startCell, int curVehSpeed, bool* sawObstacle) { //funkcja wyliczaj¹ca now¹ prêdkoœæ dla pojazdu
	Vehicle* startCellVeh = startCell->getVehicle();
	if (startCellVeh != nullptr) {
		if (startCellVeh->getIsObstacle() == true) {
			return SpeedData{ 0, startCell };
		}
	}
	int newVehSpeed = std::min(curVehSpeed + 1, startCell->getMaxSpeed()); //nowa prêdkoœæ pojazdu, na pocz¹tku ustalana na maksymaln¹ mo¿liw¹ do uzyskania wartoœæ - maksymaln¹ prêdkoœæ dla komórki w której siê znajduje, w czasie
											  //dzia³ania funkcji mo¿e byæ tylko obni¿ana
	Cell* tempCell = startCell;
	int tempCellMaxSpeed = NULL;
	TrafficLights* vehCellLights = startCell->getTrafficLight();
	if (vehCellLights != nullptr && vehCellLights->getColor() != LightColor::green) 	{
		return SpeedData{ 0, startCell };
	}
	for (int i = 1; i <= newVehSpeed; i++) { //przeszukaj iloœæ kolejnych komórek zale¿n¹ od prêdkoœci pojazdu w poszukiwaniu sytuacji obni¿aj¹cych prêdkoœæ, maksymalna ich iloœæ mo¿e siê zmniejszaæ
											 //wraz z dzia³aniem funkcji
		tempCell = tempCell->getNextCell();
		if (tempCell == nullptr) { //napotkana komórka nie istniej - nic nie ograniczy ju¿ prêdkoœci
			break;
		}
		if (sawObstacle != nullptr && *sawObstacle == false && tempCell->getObstacleAhead() == true) {
			*sawObstacle = true;
		}
		tempCellMaxSpeed = tempCell->getMaxSpeed();
		if (newVehSpeed > tempCellMaxSpeed) { //napotkana komórka ma ograniczenie prêdkoœci ni¿sze ni¿ aktualnie wyliczana prêdkoœæ - ograniczenie prêdkoœci do zapewniaj¹cej mksymaln¹ mo¿liw¹ prêdkoœæ
			newVehSpeed = std::min(newVehSpeed, std::max(tempCellMaxSpeed, i));
		}
		Vehicle* tempCellVeh = tempCell->getVehicle();
		if (tempCellVeh != nullptr) { //w napotkanej komórce jest pojazd, trzeba zmniejszyæ prêdkoœæ - dalej nie ma sensu szukaæ
			newVehSpeed = i - 1;
			if (sawObstacle != nullptr && tempCellVeh->getIsObstacle() == true) {
				*sawObstacle = true;
			}
			tempCell = tempCell->getPreviousCell();
			break;
		}
		if (tempCell->getTrafficLight() != nullptr && tempCell->getTrafficLight()->getColor() != LightColor::green) {
			newVehSpeed = i;
			break;
		}
	}
	return SpeedData{ newVehSpeed, tempCell };
}

void Simulation::evalChangeLane(Cell* vehCell, std::vector<MoveData>* moves) { //funkcja wyliczaj¹ca zmianê pasa
	int curVehSpeed = vehCell->getVehicle()->getSpeed();
	Cell* tempCell;
	int newLane;
	bool sawObstacle = false;
	int laneRandomizer = std::rand() % 2;
	for (int random_const = 1; random_const <= 2; random_const++) { //losowanie kolejnoœci sprawdzania pasa lewego i prawego
		if ((random_const + laneRandomizer) % 2 == 0) {
			tempCell = vehCell->getLeftCell();
			newLane = -1;
		}
		else {
			tempCell = vehCell->getRightCell();
			newLane = 1;
		}
		if (tempCell != nullptr && tempCell->getVehicle() == nullptr) {
			SpeedData newVehSpeed = evalNewVehSpeed(tempCell, curVehSpeed, &sawObstacle); //ustal prêdkoœæ pojazdu po zmianie  pasa
			if (sawObstacle == true) { //jeœli na pasie jest przeszkoda zrezygnuj ze zmiany pasa
				continue;
			}
			int prevVehDist = -6;
			for (int i = -1; i >= -6; i--) { //przeszukaj 6 komórek w ty³ w poszukiwaniu pojazdu poprzedzaj¹cego
				tempCell = tempCell->getPreviousCell();
				if (tempCell == nullptr) {
					break;
				}
				Vehicle* tempVeh = tempCell->getVehicle();
				if (tempVeh != nullptr) { //jeœli pojazd poprzedzaj¹cy zosta³ znaleziony oblicz jego przysz³a prêdkoœæ
					prevVehDist = i + evalNewVehSpeed(tempCell, tempVeh->getSpeed(), nullptr).newVehSpeed; // oblicz odle³oœæ w jakiej bêdzie pojazd poprzedzaj¹cy po wykonaniu ruchu w stosunku do pojazdu zmieniaj¹cego pas
					break;
				}
			}
			if (newVehSpeed.newVehSpeed - prevVehDist - 1 > minSafeSpace) { // jesli odleg³oœæ miêdzy pojazdami jest wiêksza lub równa od minimalnej to dodaj ruch do listy mo¿liwych
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

std::string Simulation::toString() {
	return simMap->toString();
}



bool cmpMoveData(MoveData lhs, MoveData rhs) {
	return lhs.speedData.newVehSpeed < rhs.speedData.newVehSpeed;
}