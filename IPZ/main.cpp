/*#pragma once

#include "Functionality/DensityPlotGenerator.h"

int main() {
	GenerateDensityPlot();
}
*/

/*
#include "Basic Classes/Simulation.h"
#include "Basic Classes/Map.h"
#include "Basic Classes/Road.h"
#include "Basic Classes/Vehicle.h"

int main() {
	Map* map = new Map("test");

	Road* road1 = new Road(20, 1, 5);
	Road* road2 = new Road(1, 1, 5);
	Road* road3 = new Road(100, 1, 5);

	linkCells(road1->tail[0], road2->head[0]);
	linkCells(road2->tail[0], road3->head[0]);
	linkCells(road3->tail[0], road1->head[0]);

	map->addRoad(road1);
	map->addRoad(road2);
	map->addRoad(road3);

	map->addCellsWithVehs(road1->fillWithVehs(1.0));

	Simulation simulation(map, 0.2);

	simulation.initiateSimulation();

	for (int i = 0; i < 100; i++) {
		if (i % 20 < 10) {
			road2->head[0]->setMaxSpeed(0);
		}
		else {
			road2->head[0]->setMaxSpeed(5);
		}
		simulation.transitionFunc();
		std::cout << simulation.toString() << std::endl;
	}
	map->~Map();
}
*/

#include "Basic Classes/Simulation.h"
#include "Basic Classes/Map.h"
#include "Basic Classes/Road.h"
#include "Basic Classes/Vehicle.h"
#include "Basic Classes/CrossingInput.h"
#include "Basic Classes/CarHolder.h"
#include "Basic Classes/RoadCell.h"

int main() {
	Map* map = new Map("test");

	Road* road1 = new Road(1, 1, 1);

	map->addRoad(road1);

	CrossingInput* crossingInput1 = new CrossingInput(1);

	std::vector<std::vector<CarHolder*>> carHolderMatrix =
	{
		{new CarHolder(), new CarHolder(), new CarHolder()},
		{new CarHolder(), new CarHolder(), new CarHolder()},
		{new CarHolder(), new CarHolder(), new CarHolder()}
	};
	
	//      [^]
	//   [ ][o][ ]
	//[>][o][o][o][>]
	//   [ ][o][ ]
	//      [v]

	Generator* generator1 = new Generator(0.5);

	map->addGenerator(generator1);

	linkCells(generator1, road1->head[0]);
	linkCells(road1->tail[0], crossingInput1);

	RoadCell* roadCell_1_1 = new RoadCell(1);
	RoadCell* roadCell_2_1 = new RoadCell(1);
	RoadCell* roadCell_3_1 = new RoadCell(1);
	RoadCell* roadCell_1_2 = new RoadCell(1);
	RoadCell* roadCell_2_2 = new RoadCell(1);
	RoadCell* roadCell_3_2 = new RoadCell(1);
	RoadCell* roadCell_1_3 = new RoadCell(1);
	RoadCell* roadCell_2_3 = new RoadCell(1);
	RoadCell* roadCell_3_3 = new RoadCell(1);

	// ³¹czenie RoadCellów
	linkCells(roadCell_1_1, roadCell_1_2);
	linkCells(roadCell_1_2, roadCell_1_3);

	linkCells(roadCell_2_1, roadCell_2_2);
	linkCells(roadCell_2_2, roadCell_2_3);
	
	linkCells(roadCell_3_1, roadCell_3_2);
	linkCells(roadCell_3_2, roadCell_3_3);

	roadCell_1_1->setCarHolder(carHolderMatrix[1][0]);
	roadCell_1_2->setCarHolder(carHolderMatrix[1][1]);
	roadCell_1_3->setCarHolder(carHolderMatrix[0][1]);
	roadCell_2_1->setCarHolder(carHolderMatrix[1][0]);
	roadCell_2_2->setCarHolder(carHolderMatrix[1][1]);
	roadCell_2_3->setCarHolder(carHolderMatrix[1][2]);
	roadCell_3_1->setCarHolder(carHolderMatrix[1][0]);
	roadCell_3_2->setCarHolder(carHolderMatrix[1][1]);
	roadCell_3_3->setCarHolder(carHolderMatrix[2][1]);

	crossingInput1->setNextCell(roadCell_1_1);
	crossingInput1->setNextCell(roadCell_2_1);
	crossingInput1->setNextCell(roadCell_3_1);

	Simulation simulation(map, 0.0);

	simulation.initiateSimulation();

	for (int i = 0; i < 100; i++) {
		simulation.transitionFunc();
		//std::cout << simulation.toString() << std::endl;
		std::string crossing = "";
		for (std::vector <CarHolder*> carHolderVector : carHolderMatrix)
		{
			for (CarHolder* carHolder : carHolderVector)
			{
				if(carHolder->getVehicle() == nullptr)
					crossing += "[ ]";
				else
					crossing += "[x]";
			}
			crossing += "\n";
		}
		std::cout << crossing << std::endl;
	}

}