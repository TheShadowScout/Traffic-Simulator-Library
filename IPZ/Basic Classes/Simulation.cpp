#pragma once

#include "Simulation.h"

Simulation::Simulation(Map* simMap, double randEventProb, int viewDist, int minSafeSpace, int seed, bool shuffleIfCompetition) : simMap(simMap), randEventProb(randEventProb), viewDist(viewDist), minSafeSpace(minSafeSpace), seed(seed), shuffleIfCompetition(shuffleIfCompetition), simStats(nullptr) {
	if (seed == NULL) {
		randomEngine = std::default_random_engine(seed);
	}
	else {
		randomEngine = std::default_random_engine(std::rand());
	}
	if(randEventProb < 0 || randEventProb > 1)
		throw std::invalid_argument("Random event probability must be in range between 0 and 1");
	if (viewDist < 0)
		throw std::invalid_argument("View distance mustn't be negative");
}

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
	simMap->updateObstacleAheadWarnings(viewDist);
	simStats = new Statistics(randEventProb, simMap->getMapPassableCellsCnt());
	simStats->updateStatistics(simMap->getCellsWithVehs());
	for (Observer* observer : observers) {
		observer->checkVehPassing();
	}
}

void Simulation::transitionFunc() {
	std::vector<Cell*> cellsWithVehs = simMap->getCellsWithVehs();
	std::vector<MoveData> vehsMovesData;
	for (Cell* vehCell : cellsWithVehs) {
		vehsMovesData.push_back(evalVehMove(vehCell)); //wyznacz now� pr�dko�� dla ka�dego pojazdu
		int newVehSpeed = vehsMovesData.back().speedData.newVehSpeed;
		int newVehLane = vehsMovesData.back().newVehLane;
		int curVehSpeed = vehCell->getVehicle()->getSpeed();
		if (1.0 * std::rand() / RAND_MAX <= randEventProb && newVehSpeed > 0 && curVehSpeed <= newVehSpeed && newVehLane == 0 && vehsMovesData.back().speedData.destinationCell != nullptr) { //zdarzenie losowe - obni�enie pr�dko�ci o 1, je�li pojazd nie zmienia
			vehsMovesData.back().speedData.newVehSpeed -= 1;
			vehsMovesData.back().speedData.destinationCell = vehsMovesData.back().speedData.destinationCell->getPreviousCell();	//pasa, jedzie z pr�dko�ci� wi�ksz� od 0 i jedzie co najmniej tak samo
		}                                                                                                                        //szybko jak tur� temu
	}
	std::vector<Cell*> newCellsWithVehs = moveVehs(cellsWithVehs, vehsMovesData); //poryszenie pojazd�w
	std::vector<Generator*> generators = simMap->getGenerators();
	for (Generator* generator : generators) { //aktualizacja generator�w
		if (generator->createVeh() == true) {
			newCellsWithVehs.push_back(generator);
		}
	}
	simMap->setCellsWithVehs(newCellsWithVehs);
	simStats->updateStatistics(simMap->getCellsWithVehs());
	for (Observer* observer : observers) { //aktualizacja obserwator�w
		observer->checkVehPassing();
	}

	for (unsigned int i = 0; i < simMap->getRoads().size(); i++)
	{
		std::vector<TrafficLights*> roadLights = simMap->getRoads()[i]->getLights();
		for (unsigned int j = 0; j < roadLights.size(); j++)
		{
			int tempTimer = roadLights[j]->getTimer();
			if (tempTimer > 0)
				roadLights[j]->setTimer(tempTimer - 1);
			else
			{
				// roadLights[j]->setTimer(roadLights[j]->getChangePeriod());
				// roadLights[j]->setState(!roadLights[j]->getState());
				if (!roadLights[j]->getYellowOn())
				{
					switch (roadLights[j]->getColor())
					{
					case LightColor::red:
						roadLights[j]->setTimer(roadLights[j]->getGreenDuration());
						roadLights[j]->setColor(LightColor::green);
						break;
					case LightColor::green:
						roadLights[j]->setTimer(roadLights[j]->getRedDuration());
						roadLights[j]->setColor(LightColor::red);
						break;
					}
				}
				else
				{
					switch (roadLights[j]->getColor())
					{
					case LightColor::red:
						roadLights[j]->setTimer(roadLights[j]->getRedYellowDuration());
						roadLights[j]->setColor(LightColor::green);
						break;
					case LightColor::redyellow:
						roadLights[j]->setTimer(roadLights[j]->getGreenDuration());
						roadLights[j]->setColor(LightColor::green);
						break;
					case LightColor::green:
						roadLights[j]->setTimer(roadLights[j]->getYellowDuration());
						roadLights[j]->setColor(LightColor::yellow);
						break;
					case LightColor::yellow:
						roadLights[j]->setTimer(roadLights[j]->getRedDuration());
						roadLights[j]->setColor(LightColor::red);
						break;
					}
				}
			}
		}
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
		if (startCellVeh->checkIsObstacle() == true) {
			return SpeedData{ 0, startCell };
		}
	}
	int newVehSpeed = std::min(curVehSpeed + 1, startCell->getMaxSpeed()); //nowa pr�dko�� pojazdu, na pocz�tku ustalana na maksymaln� mo�liw� do uzyskania warto�� - maksymaln� pr�dko�� dla kom�rki w kt�rej si� znajduje, w czasie
											  //dzia�ania funkcji mo�e by� tylko obni�ana
	Cell* tempCell = startCell;
	int tempCellMaxSpeed = NULL;
	for (int i = 1; i <= newVehSpeed; i++) { //przeszukaj ilo�� kolejnych kom�rek zale�n� od pr�dko�ci pojazdu w poszukiwaniu sytuacji obni�aj�cych pr�dko��, maksymalna ich ilo�� mo�e si� zmniejsza�
											 //wraz z dzia�aniem funkcji
		tempCell = tempCell->getNextCell();
		if (tempCell == nullptr) { //napotkana kom�rka nie istniej - nic nie ograniczy ju� pr�dko�ci
			break;
		}
		if (sawObstacle != nullptr && *sawObstacle == false && tempCell->checkObstacleAhead() == true) {
			*sawObstacle = true;
		}
		tempCellMaxSpeed = tempCell->getMaxSpeed();
		if (newVehSpeed > tempCellMaxSpeed) { //napotkana kom�rka ma ograniczenie pr�dko�ci ni�sze ni� aktualnie wyliczana pr�dko�� - ograniczenie pr�dko�ci do zapewniaj�cej mksymaln� mo�liw� pr�dko��
			newVehSpeed = std::min(newVehSpeed, std::max(tempCellMaxSpeed, i));
		}
		Vehicle* tempCellVeh = tempCell->getVehicle();
		if (tempCellVeh != nullptr) { //w napotkanej kom�rce jest pojazd, trzeba zmniejszy� pr�dko�� - dalej nie ma sensu szuka�
			newVehSpeed = i - 1;
			if (sawObstacle != nullptr && tempCellVeh->checkIsObstacle() == true) {
				*sawObstacle = true;
			}
			tempCell = tempCell->getPreviousCell();
			break;
		}
		TrafficLights* tempCellLights = tempCell->getLight();
		if (tempCellLights != nullptr && tempCellLights->getColor() == LightColor::red) {
			newVehSpeed = i - 1;
			tempCell = tempCell->getPreviousCell();
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

/*
std::vector<Cell*> Simulation::moveVehs(std::vector<Cell*> cellsWithVehs, std::vector<MoveData> vehMovesData) { //funkcja poruszaj�ca pojazdami
	std::vector<Cell*> newCellsWithVehs;
	for (unsigned int i = 0; i < cellsWithVehs.size(); i++) { //dla ka�dej kom�rki z list kom�rek z pojazdami
		int newVehSpeed = vehMovesData[i].getNewVehSpeed();
		Vehicle* curVeh = cellsWithVehs[i]->getVehicle();
		if (newVehSpeed == 0) { //je�li pojazd ma pr�dko�� 0, pozostaje w swojej kom�rce, kom�rka ta jest dodawana do nowej listy kom�rek z pojazdami
			newCellsWithVehs.push_back(cellsWithVehs[i]);
			curVeh->setSpeed(0);
			continue;
		}
		bool isVehDeleted = false;
		Cell* tempCell = cellsWithVehs[i];
		if (vehMovesData[i].getNewVahLane() == -1) { //zmie� pas na lewy
			tempCell = tempCell->getLeftCell();
		}
		else if (vehMovesData[i].getNewVahLane() == 1) { //zmie� pas na prawy
			tempCell = tempCell->getRightCell();
		}
		for (int j = 0; j < newVehSpeed; j++) { //znajd� kom�rke docelow� pojazdu zale�n� od jego pr�dko�ci
			tempCell = tempCell->getNextCell();
			if (tempCell == nullptr) { //je�li napotkana kom�rka nie ma kom�rki nast�pnej pojazd jest usuwany
				curVeh->~Vehicle();
				cellsWithVehs[i]->setVehicle(nullptr);
				isVehDeleted = true;
				break;
			}
		}
		if (isVehDeleted == true) {
			continue;
		}
		bool competition = false;
		if (tempCell->getVehicle() != nullptr) { //je�li w kom�rce docelowej jest ju� inny pojazd zrezygnuj ze zmiany pasa i jed� prosto
			competition = true;
			newVehSpeed = evalNewVehSpeed(cellsWithVehs[i], cellsWithVehs[i]->getVehicle()->getSpeed(), nullptr);
			tempCell = cellsWithVehs[i];
			for (int j = 0; j < newVehSpeed; j++) {
				tempCell = tempCell->getNextCell();
				if (tempCell == nullptr) {
					curVeh->~Vehicle();
					cellsWithVehs[i]->setVehicle(nullptr);
					isVehDeleted = true;
					break;
				}
			}
		}
		if (isVehDeleted == true) {
			continue;
		}
		curVeh->setSpeed(newVehSpeed); //nadanie pojazdowi nowej pr�dko�ci
		cellsWithVehs[i]->setVehicle(nullptr); //usu� poruszany pojazd z jego aktualnej kom�rki
		tempCell->setVehicle(curVeh);
		newCellsWithVehs.push_back(tempCell); //dodaj kom�rk� docelow� do listy kom�rek z pojazdami
		if (competition == true && shuffleIfCompetition == true) {
			std::shuffle(newCellsWithVehs.begin(), newCellsWithVehs.end(), randomEngine);
		}
	}
	return newCellsWithVehs; //zwr�� list� nowych kom�rek z pojazdami
}
*/

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
			curVeh->~Vehicle();
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