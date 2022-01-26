#include "Basic Classes/Cell.h"
#include "Basic Classes/Road.h"
#include "Basic Classes/Map.h"
#include "Basic Classes/Vehicle.h"
#include "Basic Classes/Generator.h"
#include "Basic Classes/Simulation.h"
#include "Basic Classes/DataSaving.h"
#include "boost/json.hpp"

int Road::IDcnt = 0;
int Vehicle::IDcnt = 0;
int Generator::IDcnt = 0;

int main() {
	Road* road1 = new Road(50, 3, 2);
	Road* road2 = new Road(50, 3, 2);

	road1->tail[1]->setVehicle(new Vehicle(0, true));

	Generator* generator1 = new Generator(1.0);
	Generator* generator2 = new Generator(1.0);
	Map* map = new Map("test");
	map->addRoad(road1);
	map->addRoad(road2);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	linkCells(road1->tail[0], road2->head[0]);
	linkCells(road1->tail[1], road2->head[1]);
	linkCells(road1->tail[2], road2->head[2]);
	linkCells(generator1, road1->head[1]);
	linkCells(generator2, road1->head[2]);
	Simulation simulation(map, 0.1);
	for (int i = 0; i < 100; i++) {
		simulation.transitionFunc();
		std::cout << simulation.tempToString() << std::endl;
	}
	//map->createJSON();
	DataSaving JSON(map);
	JSON.saveData();
}