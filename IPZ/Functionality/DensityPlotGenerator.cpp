#pragma once

#include "DensityPlotGenerator.h"

int Road::IDcnt = 0;
int Vehicle::IDcnt = 0;
int Generator::IDcnt = 0;
int Observer::IDcnt = 0;
int Crossing::IDcnt = 0;
int LaneEndsMerge::IDcnt = 0;
int TrafficLights::IDcnt = 0;

int GenerateDensityPlot() {

	// dokoñczyæ usuwanie obiektów (zostaj¹ artefakty)
	std::cout << "Stage 1: Generating CSV file" << std::endl;
	std::srand(std::time(NULL));
	std::string outFolder = "StatisticsHistory/";
	std::ofstream file_out;
	file_out.open(outFolder + "data" + ".csv");
	file_out << "density;v_m_a_x = 1;v_m_a_x = 2;v_m_a_x = 3;v_m_a_x = 4;v_m_a_x = 5;v_m_a_x = 6;" << std::endl;
	for (double density = 0; density <= 1; density += 0.01)
	{
		file_out << density * 100 << ";";
		for (int speed = 1; speed <= 6; speed++)
		{
			double data = 0;
			for (int sim = 0; sim < 50; sim++)
			{
				Road* road = new Road(1000, 1, speed);
				linkCells(road->getLaneTail(0), road->getLaneHead(0));
				Map* map = new Map("test");
				map->addRoad(road);
				map->fillWithVehs(density);

				Simulation simulation(map, 0.1, 0, 0);
				Observer* observer = new Observer(road->getLaneTail(0));
				simulation.addObserver(observer);

				simulation.initiateSimulation();
				for (int i = 0; i < 1000; i++) {
					simulation.transitionFunc();
				}
				for (Observer* tempObserver : simulation.getSimulationObservers()) {
					data += tempObserver->getObservedPassingVehsCnt();
				}				
				map->~Map();

			}
			std::string line = "";
			std::string newLine = "";
			line += std::to_string(data / 50);
			line += ";";
			file_out << line;
		}
		file_out << "\n";
		std::cout << "Done " << std::ceil(((density * 10) + 1) / 11 * 100) << "%" << std::endl;
	}
	file_out.close();
	std::cout << "Stage 2: Generating plot" << std::endl;
	Gnuplot gp;
	std::ifstream t("Functionality/DensityPlot.gnuplot");
	gp << t.rdbuf();
	std::wcout << "Plot generated in StatisticsHistory folder!";
	return 0;
}