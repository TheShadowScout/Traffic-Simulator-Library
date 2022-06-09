#include "../TrafficSimulationLib.h"

#define V 3
#if V == 0
int main() {
	std::srand(time(NULL));

	Map* map = new Map("test map");

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
	Road* road4 = new Road(10, 1, 4);
	Road* road5 = new Road(10, 1, 4);
	Road* road6 = new Road(10, 1, 4);
	Road* road7 = new Road(10, 1, 4);
	Road* road8 = new Road(10, 1, 4);
	Road* road9 = new Road(10, 1, 4);
	Road* road10 = new Road(10, 1, 4);
	Road* road11 = new Road(10, 1, 4);

	Generator* generator0 = new Generator(4, 0.1);
	Generator* generator1 = new Generator(4, 0.1);
	Generator* generator2 = new Generator(4, 0.2);
	Generator* generator3 = new Generator(4, 0.2);

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
	crossing->addNewCrossingLane('S', 4, 'W', 2, 1);
	crossing->addNewCrossingLane('S', 5, 'N', 5, 1);
	crossing->addNewCrossingLane('S', 5, 'E', 5, 2);

	crossing->linkCellToCrossingInput(road0->getLaneTail(0), 'N', 2);
	crossing->linkCellToCrossingInput(road1->getLaneTail(0), 'N', 3);
	crossing->linkCellToCrossingInput(road2->getLaneTail(0), 'S', 4);
	crossing->linkCellToCrossingInput(road3->getLaneTail(0), 'S', 5);

	crossing->linkCellToCrossingOutput('S', 2, road4->getLaneHead(0));
	crossing->linkCellToCrossingOutput('S', 3, road5->getLaneHead(0));
	crossing->linkCellToCrossingOutput('W', 3, road6->getLaneHead(0));
	crossing->linkCellToCrossingOutput('E', 4, road7->getLaneHead(0));

	crossing->linkCellToCrossingOutput('N', 4, road8->getLaneHead(0));
	crossing->linkCellToCrossingOutput('N', 5, road9->getLaneHead(0));
	crossing->linkCellToCrossingOutput('W', 2, road10->getLaneHead(0));
	crossing->linkCellToCrossingOutput('E', 5, road11->getLaneHead(0));

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
	map->addRoad(road4);
	map->addRoad(road5);
	map->addRoad(road6);
	map->addRoad(road7);
	map->addRoad(road8);
	map->addRoad(road9);
	map->addRoad(road10);
	map->addRoad(road11);
	map->addGenerator(generator0);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	map->addGenerator(generator3);
	map->addCrossing(crossing);

	std::vector<Localization*> localizations;
	localizations.push_back(new BasicCrossingLocalization(15, 25, crossing));
	localizations.push_back(new RoadLocalization(18, 15, road0, 'S'));
	localizations.push_back(new RoadLocalization(19, 15, road1, 'S'));
	localizations.push_back(new RoadLocalization(20, 35, road2, 'N'));
	localizations.push_back(new RoadLocalization(21, 35, road3, 'N'));
	localizations.push_back(new RoadLocalization(18, 35, road4, 'S'));
	localizations.push_back(new RoadLocalization(19, 35, road5, 'S'));
	localizations.push_back(new RoadLocalization(5, 29, road6, 'W'));
	localizations.push_back(new RoadLocalization(25, 30, road7, 'E'));

	localizations.push_back(new RoadLocalization(20, 15, road8, 'N'));
	localizations.push_back(new RoadLocalization(21, 15, road9, 'N'));
	localizations.push_back(new RoadLocalization(5, 28, road10, 'W'));
	localizations.push_back(new RoadLocalization(25, 31, road11, 'E'));

	Simulation simulation = Simulation(map, 0.2, 0);
	simulation.initiateSimulation();

	SimulationWindow simulationWindow;
	simulationWindow.createSimulationWindow(&simulation, localizations, 0.02);

	delete map;
}
#elif V == 3
// Ruch zgodnie z kierunkiem wskazówek zegara
int main() {
	std::srand(time(NULL));

	Map* map = new Map("test map");

	Road* road0 = new Road(50, 1, 6);
	Road* road1 = new Road(30, 1, 6);
	Road* road2 = new Road(50, 1, 6);
	Road* road3 = new Road(30, 1, 6);

	linkCells(road0->getLaneTail(0), road1->getLaneHead(0));
	linkCells(road1->getLaneTail(0), road2->getLaneHead(0));
	linkCells(road2->getLaneTail(0), road3->getLaneHead(0));
	linkCells(road3->getLaneTail(0), road0->getLaneHead(0));

	map->addRoad(road0);
	map->addRoad(road1);
	map->addRoad(road2);
	map->addRoad(road3);

	map->fillWithVehs(0.2);

	std::vector<Localization*> localizations;
	localizations.push_back(new RoadLocalization(10, 5, road0, 'E'));
	localizations.push_back(new RoadLocalization(60, 5, road1, 'S'));
	localizations.push_back(new RoadLocalization(11, 35, road2, 'W'));
	localizations.push_back(new RoadLocalization(10, 6, road3, 'N'));

	Simulation simulation = Simulation(map, 0.2, 0);
	simulation.initiateSimulation();

	SimulationWindow simulationWindow;
	simulationWindow.createSimulationWindow(&simulation, localizations, 0.02);

	delete map;
}
#elif V == 4

#endif

/*
#include "Gui/SimulationWindow.h"


int demoRoad1() {
	Road* road1 = new Road(100, 1, 5);
	Generator* generator1 = new Generator(1, 0.9);

	Map* map = new Map("demo-road-1");
	map->addRoad(road1);
	map->addGenerator(generator1);
	linkCells(generator1, road1->getLaneHead(0));

	Simulation simulation(map, 0.1, 1);
	SimulationWindow test;
	test.createSimulationWindow(simulation);

	delete map;
	return 0;
}

int demoRoad2() {
	std::srand(time(NULL));
	Map* map = new Map("test map");
	Road* road = new Road(150, 3, 3);
	road->addObstacle(75, 1);

	Generator* generator0 = new Generator(3, 0.2);
	Generator* generator1 = new Generator(3, 0.2);
	Generator* generator2 = new Generator(3, 0.2);

	linkCells(generator0, road->getLaneHead(0));
	linkCells(generator1, road->getLaneHead(1));
	linkCells(generator2, road->getLaneHead(2));

	map->addRoad(road);
	map->addGenerator(generator0);
	map->addGenerator(generator1);
	map->addGenerator(generator2);

	Simulation simulation(map, 0.2, 0);
	SimulationWindow test;
	test.createSimulationWindow(simulation);

	delete map;
	return 0;
}

int demoRoad3() {
	std::srand(time(NULL));
	Map* map = new Map("test map");
	Road* road = new Road(150, 3, 3);  
	//road->fillWithVehs(0.2);
	road->addObstacle(50, 1);
	road->addObstacle(100, 0);
	road->addObstacle(100, 2);

	Generator* generator0 = new Generator(3, 0.2);
	Generator* generator1 = new Generator(3, 0.2);
	Generator* generator2 = new Generator(3, 0.2);

	linkCells(generator0, road->getLaneHead(0));
	linkCells(generator1, road->getLaneHead(1));
	linkCells(generator2, road->getLaneHead(2));

	map->addRoad(road);
	map->addGenerator(generator0);
	map->addGenerator(generator1);
	map->addGenerator(generator2);

	Simulation simulation(map, 0.2, 0);
	SimulationWindow test;
	test.createSimulationWindow(simulation);

	delete map;
	return 0;
}

int demoRoad4() {
	std::srand(time(NULL));

	Map* map = new Map("test map");

	Road* road = new Road(50, 1, 5);

	Generator* generator0 = new Generator(5, 0.2);
	Generator* generator1 = new Generator(5, 0.2);
	Generator* generator2 = new Generator(5, 0.2);

	LaneEndsMergeLR* laneEndsMerge = new LaneEndsMergeLR(20, 1, 5);

	linkCells(generator0, laneEndsMerge->getEndingLaneLHead());
	linkCells(generator1, laneEndsMerge->getLaneHead(0));
	linkCells(generator2, laneEndsMerge->getEndingLaneRHead());

	linkCells(laneEndsMerge->getLaneTail(0), road->getLaneHead(0));

	RGTrafficLights* trafficLights = new RGTrafficLights(LightColor::green, 10, 10);

	road->addTrafficLightsToAllLanes(trafficLights, 25);

	map->addRoad(road);
	map->addGenerator(generator0);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	map->addLaneEndsMerge(laneEndsMerge);

	Simulation simulation(map, 0.2, 0);
	SimulationWindow test;
	test.createSimulationWindow(simulation);

	delete map;
	return 0;
}

int demoRoad5() {
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

	BasicCrossing* crossing = new BasicCrossing(8, 8, 4);
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

	Simulation simulation(map, 0.2, 0);
	simulation.initiateSimulation();

	for (int i = 0; i < 100; i++) {
		simulation.transitionFunc();
		std::cout << "Iteration: " << i << std::endl;
		std::cout << simulation.toString() << std::endl;
		simulation.transitionFunc();
	}

	delete map;	std::srand(time(NULL));

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

	BasicCrossing* crossing = new BasicCrossing(8, 8, 4);
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

	Simulation simulation(map, 0.2, 0);
	SimulationWindow test;
	test.createSimulationWindow(simulation);

	delete map;
	return 0;
}


int main() {
	int choice = 2;
	switch (choice) 
	{
	case 1: // Droga jednopasmowa
		demoRoad1();
		break;
	case 2: // Droga trzypasmowa z jedną przeszkodą
		demoRoad2();
		break;
	case 3: // Droga trzypasmowa z trzema przeszkodami
		demoRoad3();
		break;
	case 4:
		demoRoad4();
		break;
	case 5:
		demoRoad5();
		break;
	}
	return 0;
}
*/