#include <iostream>
#include <fstream>
#include <string>

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
std::string initializeStatistics()
{
	std::string stringHolder =
		"<!doctype html>"
		"< html lang = 'pl' >"
		"<head>"
		"<meta charset = 'utf-8'>"
		"<meta name = 'viewport' content = 'width=device-width, initial-scale=1'>"

		"<link href = 'https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css' rel = 'stylesheet' integrity = 'sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC' crossorigin = 'anonymous'>"
		"<link rel = 'stylesheet' href = 'page.css'>"
		"<link href = 'fontawesome/css/all.css'>"
		"<script defer src = '/fontawesome/js/all.js'>< / script>"
		"<title>Statystyki< / title>"
		"< / head>'"
		"< body >"
		"<div class = 'container-fluid'>"
		"<div class = 'bg-primary bg-gradient text-center'>"
		"<div class = 'text-white card-header statistics-title'>Statystyki< / div>"
		"< / div>"
		"<div class = 'row'>"
		"<div class = 'col-4'>";
	return stringHolder;
}
std::string addStatistic(std::string statisticName, std::string statisticValue, bool randomColor = false, std::string color = "primary")
{
	srand(time(NULL));
	if (randomColor == true)
		color = colors[rand() % 5];
	std::string stringHolder =
		"< div class = 'text-center text-white bg-" + color + " rounded - 2 mt - 2' >"
		"<i class = 'fas fa-car'>< / i>"
		+ statisticName +
		"<i class = 'fas fa-car'>< / i>"
		"< div class = 'statistic-info text-center'>"
		+ statisticValue +
		"< / div>"
		"< / div>";
	return stringHolder;
}
std::string initializePlots()
{
	std::string stringHolder =
		"< / div>"
		"< div class = 'col-8'>";
	return stringHolder;
}
std::string addPlot(std::string plotPath)
{
	std::string stringHolder;
	if (plotCounter == 0)
	{
		stringHolder =
			"<div class = 'row'>"
			"<div class = 'col-6'>"
			"<div class = 'row'><img src = 'https://www.w3schools.com/images/w3schools_green.jpg' alt = 'W3Schools.com'>< / div>"
			"< / div>";
		plotCounter++;
	}
	else if (plotCounter == 1)
	{
		stringHolder =
			"<div class = 'col-6'>"
			"<div class = 'row'><img src = 'https://www.w3schools.com/images/w3schools_green.jpg' alt = 'W3Schools.com'>< / div>"
			"< / div>"
			"< / div>";
		plotCounter--;
	}
	return stringHolder;
}
std::string endStatistics()
{
	std::string stringHolder =
		"< / div>"
		"< / div>"
		"< / div>"
		"<script src = 'https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js' integrity = 'sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM' crossorigin = 'anonymous'>< / script>"
		"< / body>"
		"< / html>";
	return stringHolder;
}

int main() {

	// Create and open a text file
	std::ofstream MyFile("statystyki.html");

	// Write to the file
	MyFile << initializeStatistics();
	MyFile << addStatistic("statystyka1", "4", true);
	MyFile << addStatistic("statystyka2", "6", true);
	MyFile << addStatistic("statystyka3", "8", true);
	MyFile << addStatistic("statystyka4", "10", true);
	MyFile << initializePlots();
	MyFile << addPlot("tekst");
	MyFile << addPlot("tekst");
	MyFile << endStatistics();
	// Close the file
	MyFile.close();
}

