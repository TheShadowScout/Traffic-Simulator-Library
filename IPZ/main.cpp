
#pragma once

#include "Gui/SimulationWindow.h"
#include "Functionality/StatisticsGenerator.h"

int main() {
	Road* road1 = new Road(76, 1, 5, 'S');
	Road* road2 = new Road(76, 1, 5, 'E');
	Road* road3 = new Road(76, 1, 5, 'N');
	Road* road4 = new Road(76, 1, 5, 'W');
	// Road* road2 = new Road(75, 3, 5, 'E');
	TrafficLights* light1 = new TrafficLights(LightColor(LightColor::red), 20, 7, 7);
	road1->addLights(light1);
	Generator* generator1 = new Generator(0.7);
	//Generator* generator2 = new Generator(0.8);
	//Generator* generator3 = new Generator(0.8);
	//Generator* generator4 = new Generator(0.8);
	Map* map = new Map("test");
	map->addRoad(road1);
	map->addRoad(road2);
	map->addRoad(road3);
	map->addRoad(road4);
	// map->addRoad(road2);
	map->addGenerator(generator1);
	//map->addGenerator(generator2);
	//map->addGenerator(generator3);
	//map->addGenerator(generator4);
	linkCells(generator1, road1->head[0]);
	//linkCells(generator2, road2->head[0]);
	//linkCells(generator3, road2->head[1]);
	//linkCells(generator4, road2->head[2]);

	SimulationWindow test;
	test.createSimulationWindow(map, 0.1);
	/*GenerateDensityPlot();*/
	return 0;
}


#pragma once

///*
//#include "Functionality/DensityPlotGenerator.h"
//#include "Functionality/StatisticsGenerator.h"
//
//int main() {
//	GenerateDensityPlot();
//	return 0;
//}
//*/


//
//#include <iostream>
//
//#include "Basic Classes/Simulation.h"
//#include "Basic Classes/Map.h"
//#include "Basic Classes/Road.h"
//#include "Basic Classes/Vehicle.h"
//#include "Basic Classes/Generator.h"
//#include "Basic Classes/Observer.h"
//
//int main() {
//	Road* road1 = new Road(100, 1, 5);
//
//	//road2->tail[0]->setVehicle(new Vehicle(0, true));
//	TrafficLights* light = new TrafficLights(true, 30, 4);
//	road1->addLights(light);
//	Generator* generator = new Generator(0.1);
//	//linkCells(generator, road->head[0]);
//
//	Map* map = new Map("test");
//	map->addRoad(road1);
//	map->addGenerator(generator);
//
//	//map->fillWithVehs(0.1);
//
//	Simulation simulation(map, 0.2);
//	//Observer* observer = new Observer(road2->tail[0]);
//	//simulation.addObserver(observer);
//
//	simulation.initiateSimulation();
//	for (int i = 0; i < 100; i++) {
//		simulation.transitionFunc();
//		std::cout << simulation.toString() << std::endl;
//	}
//	map->~Map();
//}
