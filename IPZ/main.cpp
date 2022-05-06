/*#pragma once

#include "Functionality/DensityPlotGenerator.h"

int main() {
	GenerateDensityPlot();
}
*/

#include "Basic Classes/Simulation.h"
#include "Basic Classes/Map.h"
#include "Basic Classes/Road.h"
#include "Basic Classes/Crossing.h"
#include "Basic Classes/Obstacle.h"
#include "Basic Classes/RGTrafficLights.h"
#include "Basic Classes/SmartCrossing.h"
#include "Basic Classes/BasicCrossing.h"
#include "Basic Classes/LaneEndsMergeL.h"

///*
int main() {
	//std::srand(time(NULL));

	//LaneEndsMergeL* x = new LaneEndsMergeL(10, 2, 3);

	///*
	std::srand(time(NULL));

	Map* map = new Map("test");

	Road* road1 = new Road(1, 1, 1);
	Road* road2 = new Road(1, 1, 1);

	//road2->addObstacle(9, 0, 0);

	map->addRoad(road1);
	map->addRoad(road2);

	Generator* generator1 = new Generator(1, 1.0);
	Generator* generator2 = new Generator(1, 1.0);

	map->addGenerator(generator1);
	map->addGenerator(generator2);

	linkCells(generator1, road1->getLaneHead(0));
	linkCells(generator2, road2->getLaneHead(0));

	BasicCrossing* crossing1 = new BasicCrossing(11, 11, 1);
	crossing1->addNewCrossingLane('S', 5, 'E', 5, 1);
	crossing1->addNewCrossingLane('N', 5, 'W', 5, 1);

	crossing1->linkRoadLaneToCrossing(road1->getLaneTail(0), 'S', 5);
	crossing1->linkRoadLaneToCrossing(road2->getLaneTail(0), 'N', 5);

	//RGTrafficLights* lights = new RGTrafficLights(LightColor::green, 10, 10);
	//crossing1->addTrafficLights(lights, 'S', 5);

	map->addCrossing(crossing1);

	Simulation simulation(map, 0, 1, 0);
	simulation.initiateSimulation();

	for (int i = 0; i < 100; i++) {
		simulation.transitionFunc();
		std::cout << simulation.toString() << std::endl;
	}
	//*/
}
//*/


/*
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

	road1->addObstacle(50, 1, 0);
	road1->addObstacle(100, 0, 0);
	road1->addObstacle(100, 2, 0);

	Simulation simulation(map, 0.2, 0);
	simulation.initiateSimulation();

	for (int i = 0; i < 100; i++) {
		std::cout << i << std::endl;
		simulation.transitionFunc();
		std::cout << simulation.toString() << std::endl;
	}
}
*/
