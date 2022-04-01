
#pragma once

#include "Gui/SimulationWindow.h"
#include "Functionality/StatisticsGenerator.h"

int main() {
	Road* road1 = new Road(100, 1, 5);
	// czrwone/zielone, nr komórki, czas trwania cyklu
	TrafficLights* light1 = new TrafficLights(LightColor(LightColor::red), 50, 7, 7);
	// TrafficLights* light2 = new TrafficLights(false, 20, 4);
	// TrafficLights* light3 = new TrafficLights(false, 60, 5);
	// TrafficLights* light4 = new TrafficLights(false, 50, 2);
	Road* road2 = new Road(50, 3, 3);
	Road* road3 = new Road(75, 2, 3);
	Road* road4 = new Road(100, 1, 5);
	road1->addLights(light1);
	// road2->addLights(light2);
	// road3->addLights(light3);
	// road4->addLights(light4);
	Generator* generator1 = new Generator(0.9);
	Generator* generator2 = new Generator(0.5);
	Generator* generator3 = new Generator(0.7);
	Generator* generator4 = new Generator(0.9);
	Map* map = new Map("test");
	map->addRoad(road1);
	map->addRoad(road2);
	map->addRoad(road3);
	map->addRoad(road4);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	map->addGenerator(generator3);
	map->addGenerator(generator4);
	linkCells(generator1, road1->head[0]);
	linkCells(generator2, road2->head[0]);
	linkCells(generator3, road3->head[0]);
	linkCells(generator4, road4->head[0]);
	linkCells(road2->tail[0], road2->head[1]);
	linkCells(road2->tail[1], road2->head[2]);


	linkCells(road3->tail[0], road3->head[1]);
	Simulation simulation(map, 0.1);

	SimulationWindow test;
	test.createSimulationWindow(simulation);
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
