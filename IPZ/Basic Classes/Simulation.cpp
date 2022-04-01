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
		vehsMovesData.push_back(evalVehMove(vehCell)); //wyznacz now¹ prêdkoœæ dla ka¿dego pojazdu
		int newVehSpeed = vehsMovesData.back().getNewVehSpeed();
		int newVehLane = vehsMovesData.back().getNewVahLane();
		int curVehSpeed = vehCell->getVehicle()->getSpeed();
		if (1.0 * std::rand() / RAND_MAX <= randEventProb && newVehSpeed > 0 && curVehSpeed <= newVehSpeed && newVehLane == 0) { //zdarzenie losowe - obni¿enie prêdkoœci o 1, jeœli pojazd nie zmienia
			vehsMovesData.back().setNewVehSpeed(newVehSpeed - 1);                                                                //pasa, jedzie z prêdkoœci¹ wiêksz¹ od 0 i jedzie co najmniej tak samo
		}                                                                                                                        //szybko jak turê temu
	}
	std::vector<Cell*> newCellsWithVehs = moveVehs(cellsWithVehs, vehsMovesData); //poryszenie pojazdów
	std::vector<Generator*> generators = simMap->getGenerators();
	for (Generator* generator : generators) { //aktualizacja generatorów
		if (generator->createVeh() == true) {
			newCellsWithVehs.push_back(generator);
		}
	}
	simMap->setCellsWithVehs(newCellsWithVehs);
	simStats->updateStatistics(simMap->getCellsWithVehs());
	for (Observer* observer : observers) { //aktualizacja obserwatorów
		observer->checkVehPassing();
	}
}

MovePrediction Simulation::evalVehMove(Cell* vehCell) { //funkcja wyliczaj¹ca now¹ prêdkoœæ dla pojazdu
	//int curVehSpeed = vehCell->getVehicle()->getSpeed();
	int newVehSpeed = std::min(vehCell->getVehicle()->getSpeed() + 1, vehCell->getMaxSpeed()); //nowa prêdkoœæ pojazdu, na pocz¹tku ustalana na maksymaln¹ mo¿liw¹ do uzyskania wartoœæ - maksymaln¹ prêdkoœæ dla komórki w której siê znajduje, w czasie
	                                          //dzia³ania funkcji mo¿e byæ tylko obni¿ana
	Cell* tempCell = vehCell;
	int tempCellMaxSpeed = NULL;
	for (int i = 1; i <= newVehSpeed; i++) { //przeszukaj iloœæ kolejnych komórek zale¿n¹ od prêdkoœci pojazdu w poszukiwaniu sytuacji obni¿aj¹cych prêdkoœæ, maksymalna ich iloœæ mo¿e siê zmniejszaæ
		                                     //wraz z dzia³aniem funkcji
		tempCell = tempCell->getNextCell();
		if (tempCell == nullptr) { //napotkana komórka nie istniej - nic nie ograniczy ju¿ prêdkoœci
			break;
		}
		tempCellMaxSpeed = tempCell->getMaxSpeed();
		if (newVehSpeed > tempCellMaxSpeed) { //napotkana komórka ma ograniczenie prêdkoœci ni¿sze ni¿ aktualnie wyliczana prêdkoœæ - ograniczenie prêdkoœci do zapewniaj¹cej mksymaln¹ mo¿liw¹ prêdkoœæ
			newVehSpeed = std::min(newVehSpeed, std::max(tempCellMaxSpeed, i));
		}
		if (tempCell->getVehicle() != nullptr) { //w napotkanej komórce jest pojazd, trzeba zmniejszyæ prêdkoœæ - dalej nie ma sensu szukaæ
			newVehSpeed = i - 1;
			//newVehSpeed = std::min(newVehSpeed, i - 1);
			break;
		}
	}
	return MovePrediction(true, newVehSpeed, 0);
}

std::vector<Cell*> Simulation::moveVehs(std::vector<Cell*> cellsWithVehs, std::vector<MovePrediction> vehMovesData) { //funkcja poruszaj¹ca pojazdami
	std::vector<Vehicle*> vehs;
	std::vector<Cell*> vehsDestCells;
	std::vector<Cell*> newCellsWithVehs;
	for (unsigned int i = 0; i < cellsWithVehs.size(); i++) { //dla ka¿dej komórki z list komórek z pojazdami
		int newVehSpeed = vehMovesData[i].getNewVehSpeed();
		Vehicle* curVeh = cellsWithVehs[i]->getVehicle();
		if (newVehSpeed == 0) { //jeœli pojazd ma prêdkoœæ 0, pozostaje w swojej komórce, komórka ta jest dodawana do nowej listy komórek z pojazdami
			newCellsWithVehs.push_back(cellsWithVehs[i]);
			curVeh->setSpeed(0);
			continue;
		}
		bool isVehDeleted = false;
		Cell* tempCell = cellsWithVehs[i];
		if (vehMovesData[i].getNewVahLane() == -1) { //zmieñ pas na lewy
			tempCell = tempCell->getLeftCell();
		}
		else if (vehMovesData[i].getNewVahLane() == 1) { //zmieñ pas na prawy
			tempCell = tempCell->getRightCell();
		}
		for (int j = 0; j < newVehSpeed; j++) { //znajdŸ komórke docelow¹ pojazdu zale¿n¹ od jego prêdkoœci
			tempCell = tempCell->getNextCell();
			if (tempCell == nullptr) { //jeœli napotkana komórka nie ma komórki nastêpnej pojazd jest usuwany
				curVeh->~Vehicle();
				cellsWithVehs[i]->setVehicle(nullptr);
				isVehDeleted = true;
				break;
			}
		}
		if (isVehDeleted == true) {
			continue;
		}
		curVeh->setSpeed(newVehSpeed); //nadanie pojazdowi nowej prêdkoœci
		vehs.push_back(curVeh); //dodaj pojazd do listy poruszanych pojazdów
		cellsWithVehs[i]->setVehicle(nullptr); //usuñ poruszany pojazd z jego aktualnej komórki
		vehsDestCells.push_back(tempCell); //dodaj komórkê docelow¹ do listy tych komórek
		newCellsWithVehs.push_back(tempCell); //dodaj komórkê docelow¹ do listy komórek z pojazdami
	}
	for (unsigned int i = 0; i < vehs.size(); i++) { //umieœæ pojazdy w ich komórkach docelowych
		vehsDestCells[i]->setVehicle(vehs[i]);
	}
	return newCellsWithVehs; //zwróæ listê nowych komórek z pojazdami
}
