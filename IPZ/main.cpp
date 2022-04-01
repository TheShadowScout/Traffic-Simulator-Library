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

int main() {
	std::srand(time(NULL));

	Map* map = new Map("test");

	Road* road1 = new Road(1, 1, 1);

	map->addRoad(road1);

	Generator* generator1 = new Generator(1, 1.0);

	map->addGenerator(generator1);

	linkCells(generator1, road1->head[0]);

	Crossing* crossing1 = new Crossing(11, 11, 1);
	crossing1->addX('S', 5, 'N', 5, 1);
	crossing1->addX('S', 5, 'E', 5, 1);
	crossing1->addX('S', 5, 'W', 5, 1);

	crossing1->linkRoad(road1->tail[0], 'S', 5);

	Simulation simulation(map, 0.0);

	simulation.initiateSimulation();

	for (int i = 0; i < 100; i++) {
		simulation.transitionFunc();
		std::cout << simulation.toString() << std::endl;
		std::cout << crossing1->toString() << std::endl;
	}
}