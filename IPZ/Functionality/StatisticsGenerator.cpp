#pragma once
#include "StatisticsGenerator.h"

namespace fs = std::filesystem;

//	W razie koniecznoœci dostosowania generatora, nale¿y edytowaæ WY£¥CZNIE funkcjê generateStatistics()
//	Na statystyki sk³ada siê:
//		- inicjalizacja HTML'a
//		- dodawanie statystyk
//		- inicjalizacja wykresów
//		- dodawanie wykresów
//		- zamykanie HTML'a

class StatisticsGenerator
{
private:
	const char* colors[8] = {
			"primary",
			"secondary",
			"success",
			"danger",
			"warning",
			"info",
			"light",
			"dark"
	};
	int plotCounter = 0;
	std::string path = "Statistics/page.html";
	LPCWSTR filename = L"page.html";
	std::string initializeStatistics()
	{
		std::string stringHolder =
			"<!doctype html>\n"
			"<html lang = 'pl'>\n"
			"<head>\n"
			"<meta charset = 'utf-8'>\n"
			"<meta name = 'viewport' content = 'width=device-width, initial-scale=1'>\n"
			"<link href = 'https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css' rel = 'stylesheet' integrity = 'sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC' crossorigin = 'anonymous'>\n"
			"<link rel = 'stylesheet' href = 'page.css'>\n"
			"<link href = 'fontawesome/css/all.css'>\n"
			"<script defer src = 'fontawesome/js/all.js'></script>\n"
			"<title>Statistics</title>\n"
			"</head>\n"
			"<body>\n"
			"<div class = 'container-fluid'>\n"
			"<div class = 'bg-primary bg-gradient text-center'>\n"
			"<div class = 'text-white card-header statistics-title'>Statistics</div>\n"
			"</div>\n"
			"<div class = 'row'>\n"
			"<div class = 'col-4'>\n";
		return stringHolder;
	}
	std::string addStatistic(std::string statisticName, std::string statisticValue, bool randomColor=false, std::string color="primary")
	{
		if (randomColor == true)
		{
			color = colors[rand() % 5];
		}
		std::string stringHolder =
			"<div class = 'text-center text-white bg-" + color + " rounded-2 mt-2'>\n"
			"<i class = 'fas fa-car'></i> "
			+ statisticName +
			" <i class = 'fas fa-car'></i>\n"
			"<div class = 'statistic-info text-center'>"
			+ statisticValue +
			"</div>\n"
			"</div>\n";
		return stringHolder;
	}
	std::string initializePlots()
	{
		std::string stringHolder =
			"</div>\n"
			"<div class = 'col-8'>\n";
		return stringHolder;
	}
	std::string addPlot(std::string plotPath)
	{
		std::string stringHolder;
		if (plotCounter == 0)
		{
			stringHolder =
				"<div class = 'row'>\n"
				"<div class = 'col-6'>\n"
				"<div class = 'row'><img src='"+plotPath+"'></div>\n"
				"</div>\n";
			plotCounter++;
		}
		else if (plotCounter == 1)
		{
			stringHolder =
				"<div class = 'col-6'>\n"
				"<div class = 'row'><img src='" +plotPath+ "'></div>\n"
				"</div>\n"
				"</div>\n";
			plotCounter--;
		}
		return stringHolder;
	}
	std::string endStatistics()
	{
		std::string stringHolder =
			"</div>\n"
			"</div>\n"
			"</div>\n"
			"<script src = 'https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js' integrity = 'sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM' crossorigin = 'anonymous'></script>\n"
			"</body>\n"
			"</html\n>";
		return stringHolder;
	}
	std::vector<std::vector<std::string>>loadCSV(std::string path) {

		std::ifstream in(path);

		std::string line, field;

		std::vector<std::vector<std::string> > array;  // the 2D array
		std::vector<std::string> v;                // array of values for one line only

		while (getline(in, line))    // get next line in file
		{
			v.clear();
			std::stringstream ss(line);

			while (getline(ss, field, ';'))  // break line into comma delimitted fields
			{
				v.push_back(field);  // add each field to the 1D array
			}

			array.push_back(v);  // add the 1D array to the 2D array
		}

		return array;
	}
public:
	int generateStatistics() {
		srand(time(NULL));
		std::string path = "StatisticsHistory/";
		std::vector<std::vector<std::string>> observer;
		std::vector<std::vector<std::string>> simulation_statistic;
		int fileNumber = 0;
		for (const auto& entry : fs::directory_iterator(path))
		{
			if(entry.path().u8string().find(".gitignore") == std::string::npos)
			{
				if (fileNumber == 0)
				{
					observer = loadCSV(entry.path().string());
					fileNumber++;
				}
				else if (fileNumber == 1)
				{
					simulation_statistic = loadCSV(entry.path().string());
					
				}
				// potrzebuje kolumny pojazdów co przejecha³y z obserwatora
				// meanmapfilling z symulacji
			}
		}





		std::ofstream MyFile(path);
		MyFile << initializeStatistics();
		MyFile << addStatistic("Average speed", "4", true);
		MyFile << addStatistic("Average size", "0.23", true);
		MyFile << addStatistic("Average vehicles count per second", "3.14", true);
		MyFile << addStatistic("Most common vehicle color", "Red", true);
		MyFile << initializePlots();
		MyFile << addPlot("Plots/plot1.png");
		MyFile << addPlot("Plots/plot2.png");
		MyFile << addPlot("Plots/plot3.png");
		MyFile << addPlot("Plots/plot4.png");
		MyFile << addPlot("Plots/plot5.png");
		MyFile << addPlot("Plots/plot6.png");
		MyFile << endStatistics();
		MyFile.close();
		return 0;
	}
};