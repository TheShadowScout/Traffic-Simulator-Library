#include "../TrafficSimulationLib.h"

#define V 0
#if V == 0
int main() {
	std::srand(time(NULL));

	Map* map = new Map("test map");

	//Road* road = new Road(150, 3, 6);
	//road->fillWithVehs(0.1);
	//road->addObstacle(50, 1);
	//road->addObstacle(100, 0);
	//road->addObstacle(100, 2);

	Road* road = new Road(50, 3, 6);
	road->fillWithVehs(0.1);
	road->addObstacle(20, 1);
	road->addObstacle(40, 0);
	road->addObstacle(40, 2);

	Generator* generator0 = new Generator(6, 0.2);
	Generator* generator1 = new Generator(6, 0.2);
	Generator* generator2 = new Generator(6, 0.2);

	linkCells(generator0, road->getLaneHead(0));
	linkCells(generator1, road->getLaneHead(1));
	linkCells(generator2, road->getLaneHead(2));

	map->addRoad(road);
	map->addGenerator(generator0);
	map->addGenerator(generator1);
	map->addGenerator(generator2);

	std::vector<Localization*> localizations;
	//localizations.push_back(new RoadLocalization(76, 75, road, 'N'));
	//localizations.push_back(new GeneratorLocalization(75, 75, generator0));
	//localizations.push_back(new GeneratorLocalization(75, 76, generator1));
	//localizations.push_back(new GeneratorLocalization(75, 77, generator2));

	Observer* observer0 = new Observer(road->getLanes()[0][49]);
	Observer* observer1 = new Observer(road->getLanes()[1][49]);
	Observer* observer2 = new Observer(road->getLanes()[2][49]);

	localizations.push_back(new RoadLocalization(10, 10, road, 'N'));
	localizations.push_back(new GeneratorLocalization(10, 60, generator0));
	localizations.push_back(new GeneratorLocalization(11, 60, generator1));
	localizations.push_back(new GeneratorLocalization(12, 60, generator2));

	Simulation simulation = Simulation(map, 0.2, 0);

	simulation.addObserver(observer0);
	simulation.addObserver(observer1);
	simulation.addObserver(observer2);

	simulation.initiateSimulation();

	SimulationWindow simulationWindow;
	simulationWindow.createSimulationWindow(&simulation, localizations, 0.01);

	simulation.saveStatisticsToFile();

	delete map;
}
#elif V == 1
int main() {
	std::srand(time(NULL));

	Map* map = new Map("test map");

	Road* road = new Road(130, 1, 3);

	Generator* generator0 = new Generator(1, 0.2);
	Generator* generator1 = new Generator(1, 0.2);
	Generator* generator2 = new Generator(1, 0.2);

	LaneEndsMergeLR* laneEndsMerge = new LaneEndsMergeLR(20, 1, 3);

	linkCells(generator0, laneEndsMerge->getEndingLaneLHead());
	linkCells(generator1, laneEndsMerge->getLaneHead(0));
	linkCells(generator2, laneEndsMerge->getEndingLaneRHead());

	linkCells(laneEndsMerge->getLaneTail(0), road->getLaneHead(0));

	RGTrafficLights* trafficLights1 = new RGTrafficLights(LightColor::green, 10, 10);
	RGTrafficLights* trafficLights2 = new RGTrafficLights(LightColor::green, 10, 10, 5);

	road->addTrafficLightsToAllLanes(trafficLights1, 50);
	road->addTrafficLightsToAllLanes(trafficLights2, 100);

	map->addRoad(road);
	map->addGenerator(generator0);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	map->addLaneEndsMerge(laneEndsMerge);

	std::vector<Localization*> localizations;
	localizations.push_back(new RoadLocalization(151, 20, road, 'N'));
	localizations.push_back(new LaneEndsMergeLocalizationLR(150, 150, laneEndsMerge, 'N'));
	localizations.push_back(new GeneratorLocalization(150, 170, generator0));
	localizations.push_back(new GeneratorLocalization(151, 170, generator1));
	localizations.push_back(new GeneratorLocalization(152, 170, generator2));

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
	simulationWindow.createSimulationWindow(&simulation, localizations, 0.01);

	delete map;
}
#endif