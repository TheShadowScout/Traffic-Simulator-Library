#include "../Basic Classes/Simulation.h"
#include "../Models/RGTrafficLights.h"
#include "../Models/SmartCrossing.h"
#include "../Models/BasicCrossing.h"
#include "../Models/LaneEndsMergeL.h"
#include "../Models/LaneEndsMergeLR.h"
#include "../Models/LaneEndsMergeR.h"
#include "../Models/BasicCrossing.h"
#include "../Models/SmartCrossing.h"
#include "../Models/RGTrafficLights.h"
#include "../Models/RGYTrafficLights.h"
#include "../Gui/SimulationWindow.h"
#include "../Gui/RoadLocalization.h"
#include "../Gui/GeneratorLocalization.h"
#include "../Gui/BasicCrossingLocalization.h"
#include "../Gui/LaneEndsMergeLocalizationLR.h"
#include "../Gui/LaneEndsMergeLocalizationL.h"
#include "../Gui/LaneEndsMergeLocalizationR.h"

#define V 1
#if V == 0
int main() {
	std::srand(time(NULL));

	Map* map = new Map("test map");

	Road* road = new Road(150, 3, 5);
	road->fillWithVehs(0.1);
	road->addObstacle(50, 1);
	road->addObstacle(100, 0);
	road->addObstacle(100, 2);

	Generator* generator0 = new Generator(3, 0.2);
	Generator* generator1 = new Generator(3, 0.2);
	Generator* generator2 = new Generator(3, 0.2);

	linkCells(generator0, road->getLaneHead(0));
	linkCells(generator1, road->getLaneHead(1));
	linkCells(generator2, road->getLaneHead(2));

	RGTrafficLights* trafficLights = new RGTrafficLights(LightColor::green, 10, 10);

	road->addTrafficLightsToAllLanes(trafficLights, 25);

	map->addRoad(road);
	map->addGenerator(generator0);
	map->addGenerator(generator1);
	map->addGenerator(generator2);

	BasicCrossing* crossing = new BasicCrossing(4, 8, 4);

	std::vector<Localization*> localizations;
	localizations.push_back(new RoadLocalization(15, 25, road, 'N'));
	localizations.push_back(new GeneratorLocalization(9, 19, generator0));
	//localizations.push_back(new GeneratorLocalization(101, 99, generator1));
	//localizations.push_back(new GeneratorLocalization(101, 99, generator2));
	//localizations.push_back(new BasicCrossingLocalization(10, 10, crossing));

	Simulation simulation = Simulation(map, 0.2, 0);
	simulation.initiateSimulation();

	SimulationWindow simulationWindow;
	simulationWindow.createSimulationWindow(&simulation, localizations);

	/*
	for (int i = 0; i < 100; i++) {
		std::cout << "Iteration: " << i << std::endl;
		std::cout << simulation.toString() << std::endl;
		simulation.transitionFunc();
	}
	*/

	delete map;
}
#elif V == 1
int main() {
	std::srand(time(NULL));

	Map* map = new Map("test map");

	Road* road = new Road(50, 1, 5);

	//Generator* generator0 = new Generator(5, 0.2);
	Generator* generator1 = new Generator(5, 0.2);
	Generator* generator2 = new Generator(5, 0.2);

	LaneEndsMergeR* laneEndsMerge = new LaneEndsMergeR(20, 1, 5);

	//linkCells(generator0, laneEndsMerge->getEndingLaneLHead());
	linkCells(generator1, laneEndsMerge->getLaneHead(0));
	linkCells(generator2, laneEndsMerge->getEndingLaneRHead());

	linkCells(laneEndsMerge->getLaneTail(0), road->getLaneHead(0));

	RGTrafficLights* trafficLights = new RGTrafficLights(LightColor::green, 10, 10);

	road->addTrafficLightsToAllLanes(trafficLights, 25);

	map->addRoad(road);
	//map->addGenerator(generator0);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	map->addLaneEndsMerge(laneEndsMerge);

	std::vector<Localization*> localizations;
	localizations.push_back(new LaneEndsMergeLocalizationR(11, 10, laneEndsMerge, 'N'));
	//localizations.push_back(new GeneratorLocalization(9, 10, generator0));
	localizations.push_back(new GeneratorLocalization(9, 11, generator1));
	localizations.push_back(new GeneratorLocalization(9, 12, generator2));

	Simulation simulation = Simulation(map, 0.2, 0);
	simulation.initiateSimulation();

	SimulationWindow simulationWindow;
	simulationWindow.createSimulationWindow(&simulation, localizations);

	delete map;
}
#elif V == 2
int main() {
	std::srand(time(NULL));

	Map* map = new Map("test map");

	Road* road0 = new Road(10, 1, 4);
	Road* road1 = new Road(10, 1, 4);
	Road* road2 = new Road(10, 1, 4);
	Road* road3 = new Road(10, 1, 4);

	Generator* generator0 = new Generator(4, 0.5);
	Generator* generator1 = new Generator(4, 0.5);
	Generator* generator2 = new Generator(4, 0.5);
	Generator* generator3 = new Generator(4, 0.5);

	linkCells(generator0, road0->getLaneHead(0));
	linkCells(generator1, road1->getLaneHead(0));
	linkCells(generator2, road2->getLaneHead(0));
	linkCells(generator3, road3->getLaneHead(0));

	BasicCrossing* crossing = new BasicCrossing(8, 8, 1);
	crossing->addNewCrossingLane('N', 2, 'S', 2, 1);
	crossing->addNewCrossingLane('N', 2, 'W', 3, 2);
	crossing->addNewCrossingLane('N', 3, 'S', 3, 2);
	crossing->addNewCrossingLane('N', 3, 'E', 4, 1);

	crossing->addNewCrossingLane('S', 4, 'N', 4, 2);
	crossing->addNewCrossingLane('S', 4, 'W', 3, 1);
	crossing->addNewCrossingLane('S', 5, 'N', 5, 1);
	crossing->addNewCrossingLane('S', 5, 'E', 4, 2);

	crossing->linkCellToCrossingInput(road0->getLaneTail(0), 'N', 2);
	crossing->linkCellToCrossingInput(road1->getLaneTail(0), 'N', 3);
	crossing->linkCellToCrossingInput(road2->getLaneTail(0), 'S', 4);
	crossing->linkCellToCrossingInput(road3->getLaneTail(0), 'S', 5);

	RGTrafficLights* trafficLights0 = new RGTrafficLights(LightColor::green, 16, 10);
	RGTrafficLights* trafficLights1 = new RGTrafficLights(LightColor::green, 16, 10);
	RGTrafficLights* trafficLights2 = new RGTrafficLights(LightColor::red, 16, 10, 3);
	RGTrafficLights* trafficLights3 = new RGTrafficLights(LightColor::red, 16, 10, 3);

	crossing->addTrafficLights(trafficLights0, 'N', 2);
	crossing->addTrafficLights(trafficLights1, 'N', 3);
	crossing->addTrafficLights(trafficLights2, 'S', 4);
	crossing->addTrafficLights(trafficLights3, 'S', 5);

	map->addRoad(road0);
	map->addRoad(road1);
	map->addRoad(road2);
	map->addRoad(road3);
	map->addGenerator(generator0);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	map->addGenerator(generator3);
	map->addCrossing(crossing);

	//Simulation simulation(map, 0.2, 0);
	//simulation.initiateSimulation();

	/*for (int i = 0; i < 100; i++) {
		simulation.transitionFunc();
		std::cout << "Iteration: " << i << std::endl;
		std::cout << simulation.toString() << std::endl;
		simulation.transitionFunc();
	}*/

	std::vector<Localization*> localizations;
	localizations.push_back(new BasicCrossingLocalization(15, 25, crossing));
	//localizations.push_back(new GeneratorLocalization(101, 99, generator1));
	//localizations.push_back(new GeneratorLocalization(101, 99, generator2));
	//localizations.push_back(new BasicCrossingLocalization(10, 10, crossing));

	Simulation simulation = Simulation(map, 0.2, 0);
	simulation.initiateSimulation();

	SimulationWindow simulationWindow;
	simulationWindow.createSimulationWindow(&simulation, localizations);

	delete map;
}
#endif