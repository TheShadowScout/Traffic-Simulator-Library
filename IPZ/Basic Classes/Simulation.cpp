#pragma once

#include "Simulation.h"

Simulation::Simulation(Map* simMap, double randEventProb, int viewDist) : simMap(simMap), randEventProb(randEventProb), viewDist(viewDist), simStats(nullptr) {
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
	std::vector<MovePrediction> vehsMovesData;
	for (Cell* vehCell : cellsWithVehs) {
		vehsMovesData.push_back(evalVehMove(vehCell)); //wyznacz now� pr�dko�� dla ka�dego pojazdu
		int newVehSpeed = vehsMovesData.back().getNewVehSpeed();
		int newVehLane = vehsMovesData.back().getNewVahLane();
		int curVehSpeed = vehCell->getVehicle()->getSpeed();
		if (1.0 * std::rand() / RAND_MAX <= randEventProb && newVehSpeed > 0 && curVehSpeed <= newVehSpeed && newVehLane == 0) { //zdarzenie losowe - obni�enie pr�dko�ci o 1, je�li pojazd nie zmienia
			vehsMovesData.back().setNewVehSpeed(newVehSpeed - 1);                                                                //pasa, jedzie z pr�dko�ci� wi�ksz� od 0 i jedzie co najmniej tak samo
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
}

MovePrediction Simulation::evalVehMove(Cell* vehCell) { //funkcja wyliczaj�ca now� pr�dko�� dla pojazdu
	//int curVehSpeed = vehCell->getVehicle()->getSpeed();
	int newVehSpeed = std::min(vehCell->getVehicle()->getSpeed() + 1, vehCell->getMaxSpeed()); //nowa pr�dko�� pojazdu, na pocz�tku ustalana na maksymaln� mo�liw� do uzyskania warto�� - maksymaln� pr�dko�� dla kom�rki w kt�rej si� znajduje, w czasie
	                                          //dzia�ania funkcji mo�e by� tylko obni�ana
	Cell* tempCell = vehCell;
	int tempCellMaxSpeed = NULL;
	for (int i = 1; i <= newVehSpeed; i++) { //przeszukaj ilo�� kolejnych kom�rek zale�n� od pr�dko�ci pojazdu w poszukiwaniu sytuacji obni�aj�cych pr�dko��, maksymalna ich ilo�� mo�e si� zmniejsza�
		                                     //wraz z dzia�aniem funkcji
		tempCell = tempCell->getNextCell();
		if (tempCell == nullptr) { //napotkana kom�rka nie istniej - nic nie ograniczy ju� pr�dko�ci
			break;
		}
		tempCellMaxSpeed = tempCell->getMaxSpeed();
		if (newVehSpeed > tempCellMaxSpeed) { //napotkana kom�rka ma ograniczenie pr�dko�ci ni�sze ni� aktualnie wyliczana pr�dko�� - ograniczenie pr�dko�ci do zapewniaj�cej mksymaln� mo�liw� pr�dko��
			newVehSpeed = std::min(newVehSpeed, std::max(tempCellMaxSpeed, i));
		}
		if (tempCell->getVehicle() != nullptr) { //w napotkanej kom�rce jest pojazd, trzeba zmniejszy� pr�dko�� - dalej nie ma sensu szuka�
			newVehSpeed = i - 1;
			//newVehSpeed = std::min(newVehSpeed, i - 1);
			break;
		}
	}
	return MovePrediction(true, newVehSpeed, 0);
}

std::vector<Cell*> Simulation::moveVehs(std::vector<Cell*> cellsWithVehs, std::vector<MovePrediction> vehMovesData) { //funkcja poruszaj�ca pojazdami
	std::vector<Vehicle*> vehs;
	std::vector<Cell*> vehsDestCells;
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
		curVeh->setSpeed(newVehSpeed); //nadanie pojazdowi nowej pr�dko�ci
		vehs.push_back(curVeh); //dodaj pojazd do listy poruszanych pojazd�w
		cellsWithVehs[i]->setVehicle(nullptr); //usu� poruszany pojazd z jego aktualnej kom�rki
		vehsDestCells.push_back(tempCell); //dodaj kom�rk� docelow� do listy tych kom�rek
		newCellsWithVehs.push_back(tempCell); //dodaj kom�rk� docelow� do listy kom�rek z pojazdami
	}
	for (unsigned int i = 0; i < vehs.size(); i++) { //umie�� pojazdy w ich kom�rkach docelowych
		vehsDestCells[i]->setVehicle(vehs[i]);
	}
	return newCellsWithVehs; //zwr�� list� nowych kom�rek z pojazdami
}
