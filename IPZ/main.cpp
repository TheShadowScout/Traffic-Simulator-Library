#include <ctime>
#include <cstdlib>

#include "Basic Classes/Cell.h"
#include "Basic Classes/Road.h"
#include "Basic Classes/Map.h"
#include "Basic Classes/Vehicle.h"
#include "Basic Classes/Generator.h"
#include "Basic Classes/Simulation.h"
#include "Basic Classes/Observer.h"
#include "boost/json.hpp"

#include "Basic Classes/Statistics.h"

int Road::IDcnt = 0;
int Vehicle::IDcnt = 0;
int Generator::IDcnt = 0;
int Observer::IDcnt = 0;

int main() {
	std::srand(std::time(NULL));

	///*
	Road* road1 = new Road(50, 2, 5);
	Road* road2 = new Road(50, 2, 5);

	//road2->tail[0]->setVehicle(new Vehicle(0, true));

	Generator* generator1 = new Generator(0.2);
	Generator* generator2 = new Generator(0.2);
	Map* map = new Map("test");
	map->addRoad(road1);
	map->addRoad(road2);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	linkCells(road1->tail[0], road2->head[0]);
	linkCells(road1->tail[1], road2->head[1]);
	linkCells(generator1, road1->head[0]);
	linkCells(generator2, road1->head[1]);

	Observer* observer1 = new Observer(road1->tail[0]);

	map->fillWithVehs(0.1);
	Simulation simulation(map, 0.1);

	simulation.addObserver(observer1);

	simulation.initiateSimulation();
	for (int i = 0; i < 1000; i++) {
		simulation.transitionFunc();
		std::cout << simulation.toString() << std::endl;
	}
	simulation.saveStatisticsToFile();
	//map->createJSON();
	//*/
	/*
	Road* road1 = new Road(100, 1, 5);
	Road* road2 = new Road(50, 1, 5);

	Map* map = new Map("test");
	map->addRoad(road1);
	map->fillWithVehs(0.2);
	linkCells(road1->tail[0], road2->head[0]);
	map->addRoad(road2);
	Observer* observer1 = new Observer(road1->tail[0]);
	Simulation simulation(map, 0.1);
	for (int i = 0; i < 1000; i++) {
		observer1->checkVehPassing();
		std::cout << observer1->getObservedPassingVehsCnt() << std::endl;
		simulation.transitionFunc();
		std::cout << simulation.tempToString();
	}
	*/
}