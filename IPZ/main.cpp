#include "basic_classes/Cell.h"
#include "basic_classes/Road.h"
#include "basic_classes/Map.h"
#include "basic_classes/Vehicle.h"
#include "basic_classes/Generator.h"
#include "basic_classes/Simulation.h"

int Road::IDcnt = 0;
int Vehicle::IDcnt = 0;
int Generator::IDcnt = 0;

int main() {
	Road* road1 = new Road(100, 1, 5);
	Road* road2 = new Road(50, 3, 3);
	Generator* generator1 = new Generator(0.9);
	Generator* generator2 = new Generator(0.5);
	Map* map = new Map("test");
	map->addRoad(road1);
	map->addRoad(road2);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	linkCells(generator1, road1->head[0]);
	linkCells(generator2, road2->head[0]);
	linkCells(road2->tail[0], road2->head[1]);
	linkCells(road2->tail[1], road2->head[2]);
	Simulation simulation(map, 0.1);
	for (int i = 0; i < 100; i++) {
		simulation.transitionFunc();
		std::cout << simulation.tempToString() << std::endl;
	}
}