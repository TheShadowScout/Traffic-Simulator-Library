#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

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
	const char* statistics[10] = {
		"Œrednia prêdkoœæ pojazdu",
		"Œrdnia masa pojazdu",
		"Œrednia liczba pojazdów na sekundê" };
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
			"<link href = '/fontawesome/css/all.css'>\n"
			"<script defer src = '/fontawesome/js/all.js'></script>\n"
			"<title>Statystyki</title>\n"
			"</head>\n"
			"<body>\n"
			"<div class = 'container-fluid'>\n"
			"<div class = 'bg-primary bg-gradient text-center'>\n"
			"<div class = 'text-white card-header statistics-title'>Statystyki</div>\n"
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
			"<i class = 'fas fa-car'></i>"
			+ statisticName +
			"<i class = 'fas fa-car'></i>\n"
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
				"<div class = 'row'><img src = 'https://www.w3schools.com/images/w3schools_green.jpg' alt = 'W3Schools.com'></div>\n"
				"</div>\n";
			plotCounter++;
		}
		else if (plotCounter == 1)
		{
			stringHolder =
				"<div class = 'col-6'>\n"
				"<div class = 'row'><img src = 'https://www.w3schools.com/images/w3schools_green.jpg' alt = 'W3Schools.com'></div>\n"
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
public:
	int generateStatistics() {
		srand(time(NULL));
		std::ofstream MyFile(path);
		MyFile << initializeStatistics();
		MyFile << addStatistic("statystyka1", "4", true);
		MyFile << addStatistic("statystyka2", "6", true);
		MyFile << addStatistic("statystyka3", "8", true);
		MyFile << addStatistic("statystyka4", "10", true);
		MyFile << initializePlots();
		MyFile << addPlot("tekst");
		MyFile << addPlot("tekst");
		MyFile << endStatistics();
		MyFile.close();
		return 0;
	}
};