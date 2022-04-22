/*#pragma once

#include "Functionality/DensityPlotGenerator.h"

int main() {
<<<<<<< HEAD
	Road* road1 = new Road(100, 1, 5);
	TrafficLights* light1 = new TrafficLights(LightColor(LightColor::red), 50, 7, 7);
	road1->addLights(light1);
	Generator* generator1 = new Generator(0.9);
=======
	GenerateDensityPlot();
}
*/

#include "Basic Classes/Simulation.h"
#include "Basic Classes/Map.h"
#include "Basic Classes/Road.h"
#include "Basic Classes/Crossing.h"

/*
int main() {
	std::srand(time(NULL));

>>>>>>> tempbranch
	Map* map = new Map("test");

	Road* road1 = new Road(1, 1, 5);

	map->addRoad(road1);

	Generator* generator1 = new Generator(5, 1.0);

	map->addGenerator(generator1);

	linkCells(generator1, road1->head[0]);

	Crossing* crossing1 = new Crossing(11, 11, 5);
	crossing1->addNewCrossingLane('S', 5, 'N', 5, 1);
	crossing1->addNewCrossingLane('S', 5, 'E', 5, 1);
	crossing1->addNewCrossingLane('S', 5, 'W', 5, 1);

	crossing1->linkRoadLaneToCrossing(road1->tail[0], 'S', 5);

	map->addCrossing(crossing1);

	Simulation simulation(map, 0.2, 1, 0);

	simulation.initiateSimulation();

	for (int i = 0; i < 100; i++) {
		simulation.transitionFunc();
		std::cout << simulation.toString() << std::endl;
	}
}
*/


/*
int main() {
	std::srand(time(NULL));

	Map* map = new Map("test");

	Road* road1 = new Road(50, 4, 6);

	Generator* generator1 = new Generator(6, 0.2);
	Generator* generator2 = new Generator(6, 0.2);
	Generator* generator3 = new Generator(6, 0.2);
	Generator* generator4 = new Generator(6, 0.2);

	linkCells(generator1, road1->head[0]);
	linkCells(generator2, road1->head[1]);
	linkCells(generator3, road1->head[2]);
	linkCells(generator4, road1->head[3]);

	map->addRoad(road1);
	map->addGenerator(generator1);
<<<<<<< HEAD
	linkCells(generator1, road1->head[0]);
	Simulation simulation(map, 0.1);
=======
	map->addGenerator(generator2);
	map->addGenerator(generator3);
	map->addGenerator(generator4);

	Cell* tempCell = road1->head[0];
	for (int i = 0; i < 25; i++) {
		tempCell = tempCell->getNextCell();
	}
	tempCell->setVehicle(new Vehicle(0, true));

	tempCell = road1->head[2];
	for (int i = 0; i < 25; i++) {
		tempCell = tempCell->getNextCell();
	}
	tempCell->setVehicle(new Vehicle(0, true));
>>>>>>> tempbranch

	tempCell = road1->head[1];
	for (int i = 0; i < 27; i++) {
		tempCell = tempCell->getNextCell();
	}
	tempCell->setVehicle(new Vehicle(0, true));

	tempCell = road1->head[3];
	for (int i = 0; i < 27; i++) {
		tempCell = tempCell->getNextCell();
	}
	tempCell->setVehicle(new Vehicle(0, true));

	Simulation simulation(map, 0.2, 6, 0);
	simulation.initiateSimulation();

	for (int i = 0; i < 100; i++) {
		simulation.transitionFunc();
		std::cout << simulation.toString() << std::endl;
	}
}
*/

/*
int main() {
	std::srand(time(NULL));

	Map* map = new Map("test");

	Road* road1 = new Road(200, 4, 3);

	Generator* generator1 = new Generator(3, 0.2);
	Generator* generator2 = new Generator(3, 0.2);
	Generator* generator3 = new Generator(3, 0.2);
	Generator* generator4 = new Generator(3, 0.2);

	linkCells(generator1, road1->head[0]);
	linkCells(generator2, road1->head[1]);
	linkCells(generator3, road1->head[2]);
	linkCells(generator4, road1->head[3]);

	map->addRoad(road1);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	map->addGenerator(generator3);
	map->addGenerator(generator4);

	Cell* tempCell = road1->head[1];
	for (int i = 0; i < 100; i++) {
		tempCell = tempCell->getNextCell();
	}
	tempCell->setVehicle(new Vehicle(0, true));

	tempCell = road1->head[2];
	for (int i = 0; i < 100; i++) {
		tempCell = tempCell->getNextCell();
	}
	tempCell->setVehicle(new Vehicle(0, true));

	Simulation simulation(map, 0.2, 1, 1);
	simulation.initiateSimulation();

	for (int i = 0; i < 100; i++) {
		simulation.transitionFunc();
		std::cout << simulation.toString() << std::endl;
	}
}
*/

///*
int main() {
	std::srand(time(NULL));

	Map* map = new Map("test");

	Road* road1 = new Road(150, 3, 3);

	Generator* generator1 = new Generator(3, 0.2);
	Generator* generator2 = new Generator(3, 0.2);
	Generator* generator3 = new Generator(3, 0.2);

	linkCells(generator1, road1->head[0]);
	linkCells(generator2, road1->head[1]);
	linkCells(generator3, road1->head[2]);

	map->addRoad(road1);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	map->addGenerator(generator3);

	Cell* tempCell = road1->head[1];
	for (int i = 0; i < 50; i++) {
		tempCell = tempCell->getNextCell();
	}
	tempCell->setVehicle(new Vehicle(0, true));

	tempCell = road1->head[0];
	for (int i = 0; i < 100; i++) {
		tempCell = tempCell->getNextCell();
	}
	tempCell->setVehicle(new Vehicle(0, true));

	tempCell = road1->head[2];
	for (int i = 0; i < 100; i++) {
		tempCell = tempCell->getNextCell();
	}
	tempCell->setVehicle(new Vehicle(0, true));

	Simulation simulation(map, 0.2, 0, 0, 0);
	simulation.initiateSimulation();

	for (int i = 0; i < 100; i++) {
		std::cout << i << std::endl;
		simulation.transitionFunc();
		std::cout << simulation.toString() << std::endl;
	}
}
//*/
