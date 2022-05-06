# Library for creating a traffic simulator 
Student project of a library in C++ used to create a road traffic simulator. 

# Authors
*Kacper Chrzanowski*  
*Weronika Drożdż*  
*Gabor Łukjaniuk*  
*Filip Stodolny*  
*Dominik Dzięgielewski*  
*Andrey Kmet*  

# Table of Contents
1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Test codes for libraries](#test-codes-for-libraries)
4. [Test codes for program](#test-codes-for-program)
5. [Basic classes](#basic-classes)  
5.1. [Cell](#cell)  
5.2. [Road](#road)  
5.3. [Map](#map)  
5.4. [Vehicle](#vehicle)  
5.5. [Generator](#generator)    
5.6. [Simulation](#simulation)  
5.7. [DataSaving](#datasaving)
6. [Models](#models)
6.1 [Traffic Lights](#traffic-lights)  
7. [SimulationWindow](#simulationwindow)  
8. [Percentage of participation in tasks](#percentage-of-participation-in-tasks)  

# Introduction
# Installation
1. Download to selected folder [vcpkg](https://vcpkg.io/en/getting-started.html)  
2. Using Developer Command Prompt, go to vcpkg folder and install vcpkg.exe
```
.\bootstrap-vcpkg.bat
```
2. Install SFML 
```
.\vcpkg install sfml
```
3. Install Boost 
```
.\vcpkg.exe install boost:x64-windows boost:x86-windows
```
4. Install [Gnuplot](http://www.gnuplot.info/download.html) and add it to environment variables / PATH
5. Use command
```
.\vcpkg.exe integrate install
```
6. Change C++ version to C++ 17, Debug/Release and x86 in VS Community
# Test codes for libraries
SFML
```
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
```

Gnuplot

```
#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

int main() {
	Gnuplot gp;
	// Create a script which can be manually fed into gnuplot later:
	//    Gnuplot gp(">script.gp");
	// Create script and also feed to gnuplot:
	//    Gnuplot gp("tee plot.gp | gnuplot -persist");
	// Or choose any of those options at runtime by setting the GNUPLOT_IOSTREAM_CMD
	// environment variable.

	// Gnuplot vectors (i.e. arrows) require four columns: (x,y,dx,dy)
	std::vector<boost::tuple<double, double, double, double> > pts_A;

	// You can also use a separate container for each column, like so:
	std::vector<double> pts_B_x;
	std::vector<double> pts_B_y;
	std::vector<double> pts_B_dx;
	std::vector<double> pts_B_dy;

	// You could also use:
	//   std::vector<std::vector<double> >
	//   boost::tuple of four std::vector's
	//   std::vector of std::tuple (if you have C++11)
	//   arma::mat (with the Armadillo library)
	//   blitz::Array<blitz::TinyVector<double, 4>, 1> (with the Blitz++ library)
	// ... or anything of that sort

	for (double alpha = 0; alpha < 1; alpha += 1.0 / 24.0) {
		double theta = alpha * 2.0 * 3.14159;
		pts_A.push_back(boost::make_tuple(
			cos(theta),
			sin(theta),
			-cos(theta) * 0.1,
			-sin(theta) * 0.1
		));

		pts_B_x.push_back(cos(theta) * 0.8);
		pts_B_y.push_back(sin(theta) * 0.8);
		pts_B_dx.push_back(sin(theta) * 0.1);
		pts_B_dy.push_back(-cos(theta) * 0.1);
	}

	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "plot '-' with vectors title 'pts_A', '-' with vectors title 'pts_B'\n";
	gp.send1d(pts_A);
	gp.send1d(boost::make_tuple(pts_B_x, pts_B_y, pts_B_dx, pts_B_dy));

#ifdef _WIN32
	// For Windows, prompt for a keystroke before the Gnuplot object goes out of scope so that
	// the gnuplot window doesn't get closed.
	std::cout << "Press enter to exit." << std::endl;
	std::cin.get();
#endif
}
```

# Test codes for program
Simulation
```
#include "Basic Classes/Cell.h"
#include "Basic Classes/Road.h"
#include "Basic Classes/Map.h"
#include "Basic Classes/Vehicle.h"
#include "Basic Classes/Generator.h"
#include "Libraries/Simulation.h"

int Road::IDcnt = 0;
int Vehicle::IDcnt = 0;
int Generator::IDcnt = 0;

int main() {
	Road* road1 = new Road(100, 1, 5);
	Road* road2 = new Road(50, 3, 3);
	Generator* generator1 = new Generator(5, 0.9);
	Generator* generator2 = new Generator(5, 0.5);
	Map* map = new Map("test");
	map->addRoad(road1);
	map->addRoad(road2);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	linkCells(generator1, road1->getLaneHead(0));
	linkCells(generator2, road2->getLaneHead(0));
	linkCells(road2->getLaneTail(0), road2->getLaneHead(1));
	linkCells(road2->getLaneTail(1), road2->getLaneHead(2));
	Simulation simulation(map, 0.1);
	for (int i = 0; i < 100; i++) {
		simulation.transitionFunc();
		std::cout << simulation.toString() << std::endl;
	}
}
```

Simulation Window
```
#pragma once
#include "Gui/SimulationWindow.h"
#include "Functionality/StatisticsGenerator.h"
int main() {
	Road* road1 = new Road(100, 1, 5);
	Road* road2 = new Road(50, 3, 3);
	Road* road3 = new Road(75, 2, 3);
	Road* road4 = new Road(100, 1, 5);
	Generator* generator1 = new Generator(6,0.9);
	Generator* generator2 = new Generator(6,0.5);
	Generator* generator3 = new Generator(6,0.7);
	Generator* generator4 = new Generator(6,0.9);
	Map* map = new Map("test");
	map->addRoad(road1);
	map->addRoad(road2);
	map->addRoad(road3);
	map->addRoad(road4);
	map->addGenerator(generator1);
	map->addGenerator(generator2);
	map->addGenerator(generator3);
	map->addGenerator(generator4);
	linkCells(generator1, road1->getLaneHead(0));
	linkCells(generator2, road2->getLaneHead(0));
	linkCells(generator3, road3->getLaneHead(0));
	linkCells(generator4, road4->getLaneHead(0));
	linkCells(road2->getLaneTail(0), road2->getLaneHead(1));
	linkCells(road2->getLaneTail(1), road2->getLaneHead(2));


	linkCells(road3->getLaneTail(0), road3->getLaneHead(1));
	Simulation simulation(map, 0.1);

	SimulationWindow test;
	test.createSimulationWindow(simulation);
}
```
# Basic classes
## Cell
Filename with class: **Cell.h**  
Class name: **Cell**  

| Variable name	| Variable type			        | Description											|
| ------------- |-| ----------------------------------------------------------------- |
| vehicle       |Vehicle*| variable that holds a pointer to [Vehicle](#vehicle)				|
| rightCell		|Cell*| variable that holds a pointer to [Cell](#cell) adjacent to right	|
| leftCell		|Cell*| variable that holds a pointer to [Cell](#cell) adjacent to left	|
| nextCell		|Cell*| variable that holds a pointer to [Cell](#cell) adjacent to bottom |
| previousCell	|Cell*| variable that holds a pointer to [Cell](#cell) adjacent to top	|
| maxSpeed	|int|variable that holds a max speed in [Cell](#cell)	|
| light	|[TrafficLights](#traffic-lights)*|variable that holds a pointer to [TrafficLights](#traffic-lights)|

| Function type and name			| Arguments							| Description																				|
| --------------------------------- | ---------------------------------	| ----------------------------------------------------------------------------------------- |
| void Cell							| ---------------------------------	| Class constructor																			|
| void setVehicle					| [Vehicle*](#vehicle) vehicle		| Function sets in current [Cell](#cell) new pointer to [Vehicle](#vehicle)					|
| void setRightCell					| [Cell*](#cell) newRightCell		| Function sets in current [Cell](#cell) new pointer to [Cell](#cell) adjacent to the right	|
| void setLeftCell					| [Cell*](#cell) newLeftCell		| Function sets in current [Cell](#cell) new pointer to [Cell](#cell) adjacent to the left	|
| void setPreviousCell				| [Cell*](#cell) newPreviousCell	| Function sets in current [Cell](#cell) new pointer to  [Cell](#cell) adjacent to bottom	|
| void setNextCell					| [Cell*](#cell) newNextCell		| Function sets in current [Cell](#cell) new pointer to [Cell](#cell) adjacent to top		|
| [Vehicle*](#vehicle)  getVehicle	| ---------------------------------	| Function returns pointer to [Vehicle](#vehicle) in current cell							|
| [Cell*](#cell)  getRightCell		| ---------------------------------	| Function returns pointer to [Cell](#cell) adjacent to right								|
| [Cell*](#cell)  getLeftCell		| ---------------------------------	| Function returns pointer to [Cell](#cell) adjacent to left								|
| [Cell*](#cell)  getPreviousCell	| ---------------------------------	| Function returns pointer to [Cell](#cell) adjacent to bottom								|
| [Cell*](#cell)  getNextCell		| ---------------------------------	| Function returns pointer to [Cell](#cell) adjacent to top									|
| void setMaxSpeed	| int maxSpeed	| Function sets max speed in [Cell](#cell)							|
| void getMaxSpeed	| ---------------------------------	| Function returns max speed in [Cell](#cell)			|
| void createJSON	| ---------------------------------	|Function creates JSON data tree of current [Cell](#cell)|
| [TrafficLights](#traffic-lights)* getLight	| ---------------------------------	|Function return pointer to  [TrafficLights](#traffic-lights) if present in cell|
| void setLight	| [TrafficLights](#traffic-lights)* newLight	|Function sets pointer to [TrafficLights](#traffic-lights)|
## Road
Filename with class: **Road.h**  
Class name: **Road**  

| Variable name | Variable type			        | Description																|
| ------------- | ----------------------------- | ------------------------------------------------------------------------- |
| ID		| int					        | variable that holds a [Road](#road) ID									|
| maxSpeed		| int					        | variable that holds max vehicle speed										|
| length        | int                           | variable that holds road length                                           |
| height        | int                           | variable that holds road height                                           |
| name			| string				        | variable that holds a [Road](#road) name									|
| road			| vector<vector<[Cell](#cell)>>	| variable that holds vector of [Cells](#cell) creating up the road			|
| head			| vector<[Cell](#cell)>	        | variable that holds vector of [Cells](#cell) creating up the head of road |
| tail			| vector<[Cell](#cell)>	        | variable that holds vector of [Cells](#cell) creating up the tail of road |
| lights			| vector<[TrafficLights]*(#traffic-lights)>	        | variable that holds vector of [Traffic Lights](#traffic-lights) set up on the road |

| Function type and name	| Arguments					                         | Description												              |
| ------------------------- | -------------------------------------------------- | ---------------------------------------------------------------------- | 
| [Road](#Road)				| int maxSpeed, string name, int length, int height  | Class constructor									 	              |
| void CreateRoad           | -------------------------------------------------- | Function creates empty [Road](#Road) from length and height parametrs  |
| void setMaxSpeed			| int maxSpeed				                         | Function sets new max speed in current [Road](#Road)		              |
| void setName				| string name				                         | Function sets name in current [Road](#Road)				              |
| int getMaxSpeed			| -------------------------------------------------- | Function returns max speed of current [Road](#Road)		              | 
| int getID			| -------------------------------------------------- | Function returns ID of current [Road](#Road)	
| string getName			| -------------------------------------------------- | Function returns name of current [Road](#Road)			              |
| int getLength			| -------------------------------------------------- | Function returns length of current [Road](#Road)			              |
| int getHeight		| -------------------------------------------------- | Function returns height of current [Road](#Road)			              |
| void createJSON			| -------------------------------------------------- | Function creates JSON data tree of current [Road](#Road)	              |
| string tempToString			| ------------------------- | Function return road as string|
| void addLights		| [TrafficLights](#traffic-lights)* newLight | Adds light to the road|
| std::vector<[TrafficLights](#traffic-lights)*> getLights		| [TrafficLights](#traffic-lights)* newLight | Returns vector of lights on the road|
Example code
```
#include "Basic Classes/Road.h"
#include "Basic Classes/Map.h"

int main() {
	Road* road = new Road(100, 1, 5);
	Map* map = new Map("example map");
	map->addRoad(road);
	return 0;
}
```
## Map
Filename with class: **Map.h**  
Class name: **Map**  

| Variable name | Variable type							| Description																|
| ------------- | ------------------------------------- | ------------------------------------------------------------------------- |
| name			| string								| variable that holds a [Map](#map) name									|
| roads			| map<[Road](#road), int>				| variable that holds a map of [Roads](#road)								|
| generators	| map<[Generator](#generator), int>		| variable that holds a map of [Generators](#generator)						|
| destructors	| map<[Destructor](#destructor), int>	| variable that holds a map of [Destructors](#destructor)					|
| teleporters	| map<[Teleporter](#teleporter), int>	| variable that holds a map of [Teleporters](#teleporter)					|
| cellsWithCars	| list<[Cell](#cell)>					| variable that holds a list of [Cells](#cell) with [Vehicles](#vehicle)	|

| Function type and name	| Arguments		| Description												|
| ------------------------- | ------------- | --------------------------------------------------------- |
| void Map					| string name	| Class constructor	|
| void addRoad					| Road* road	| Function add road to [Map](#map)	|
| void addGenerator					| Generator* generator	| Function add generator to [Map](#map)	|
| void setcellsWithVehs					| vector<Cell*> cellsWithVehs	| Function set cell with vechicles 	|
| vector<Road*> getRoads				|  -------------------------------------------------- 	| Function returns vector roads	|
| vector<Generator*> getGenerators				|  -------------------------------------------------- 	| Function returns vector generators	|
| vector<Cell*> getcellsWithVehs			|  -------------------------------------------------- 	| Function returns cell with vechicles	|
| vector<Cell*> setCellsWithVehs			|  -------------------------------------------------- 	| Function set new cell with vechicles	|
| string getName			|  -------------------------------------------------- 	| Function returns name of [Map](#map)	|
| void createJSON			| -------------------------------------------------- | Function creates JSON data tree of current [Map](#map)		|

## Vehicle
Filename with class: **Vehicle.h**  
Class name: **Vehicle**  

| Variable name | Variable type	| Description										|
| ------------- | ------------- | ------------------------------------------------- |
| name			| string		| variable that holds a [Vehicle](#vehicle) name	|
| ID			| int			| variable that holds a [Vehicle](#vehicle) ID		|
| speed			| int			| variable that holds a [Vehicle](#vehicle) speed	|
| IDcnt			| int static			| variable that holds a [Vehicle](#vehicle) ID for a new create vehicle	|
| isObstacle			| bool			| variable that holds if [Vehicle](#vehicle) is movement vehicle or obstacle	|

| Function type and name	| Arguments					| Description												|
| ------------------------- | ------------------------- | --------------------------------------------------------- |
| void Vehicle				| string name, int speed, bool isObstacle	| Class constructor											|
| void Vehicle				| int speed, bool isObstacle	| Class constructor											|
| string getName			| ------------------------- | Function returns name of current [Vehicle](#vehicle)		|
| int getID					| ------------------------- | Function returns ID of current [Vehicle](#vehicle)		|
| int getSpeed				| ------------------------- | Function returns speed of current [Vehicle](#vehicle)		|
| void setSpeed				| int speed					| Function sets new speed of current [Vehicle](#vehicle)	|
| bool checkIsObstacle				| -------------------------	| Function returns if [Vehicle](#vehicle) is obstacle	|
| void createJSON		| -------------------------	| Function creates JSON data tree of current [Vehicle](#vehicle)	|

## Generator
Filename with class: **Generator.h**  
Class name: **Generator**  
Inherits from: [Cell](#cell)

| Variable name | Variable type	| Description											|
| ------------- | ------------- | ----------------------------------------------------- |
| name			| string		| variable that holds a [Generator](#generator) name	|

| Function type and name	| Arguments	| Description																		|
| ------------------------- | --------- | --------------------------------------------------------------------------------- |
| void Generator			| --------- | Class constructor																	|
| void create				| --------- | Function creates new [Vehicle](#vehicle) inside current [Generator](#generator)	|

## Simulation
Filename with class: **Simulation.h**  
Class name: **Simulation**  

| Variable name | Variable type	| Description														|
| ------------- | ------------- | ----------------------------------------------------------------- |
| distToSearch	| int			| array that holds a distance to search								|
| ariSeqSum		| int    		| array that holds a distance needed to stop [vehicle](#vehicle) 	|
| randEventProb	| double		| variable that holds random event									|
| simMap		| [Map*](#map)	| object that holds simulation of [map](#map)								|

| Function type and name			| Arguments							| Description												|
| --------------------------------- | --------------------------------- | --------------------------------------------------------- |
| void Simulation					| [Map*](#map) simMap, double randEventProb | Class constructor											|
| void transitionFunc				| --------------------------------- | Function return new position to [vehicle](#vehicle) in next tick|
| string tempToString				| --------------------------------- | Function return simulation move [vehicle](#vehicle) as string|
| int evalNewVehSpeed				| [Cell*](#cell) vehCell 										 | Function return new speed for [vehicle](#vehicle) in next tick| 
| Vector<[Cell*](#cell)> moveVehs	| vector<[Cell*](#cell)> cellsWithVehs, vector<int> newVehsSpeeds | Function move [vehicle](#vehicle) in [cells](#cell)		|

## DataSaving
Filename with class: **DataSaving.h**  
Class name: **DataSaving**

| Variable name | Variable type	| Description														|
| ------------- | ------------- | ------------- |
| mapa	| [Map*](#map) | Map to generate JSON |

| Function type and name			| Arguments							| Description												|
| --------------------------------- | --------------------------------- | --------------------------------------------------------- |
| void DataSaving				| [Map*](#map) mapa | Object constructor |
| void saveData();      | ----------------- | Function generates file with JSON containing map informations

# Models
## Traffic Lights
Filename with class: **TrafficLights.h**  
Class names: **TrafficLights**, **YellowTrafficLights**, **LightColor**

**LightColor**
| Object type			| Possible values							| Description|
| --------------------------------- | --------------------------------- | --------------------------------------------------------- |
| enum class LightColor | red, redyellow, green, yellow | Defines state of traffic lights |

**TrafficLights**
| Variable name			| Variable type							| Description|
| --------------------------------- | --------------------------------- | --------------------------------------------------------- |
| color | LightColor | Stores current state of traffic lights |
| yellowOn | bool | Switch turning on using yellow light |
| redLightDuration | int | Red light duration in seconds |
| greenLightDuration | int | Green light duration in seconds |
| yellowLightDuration | int | Yellow light duration in seconds |
| redYellowLightDuration | int | Red-yellow light duration in seconds |
| timer | int | Seconds left to light state change |

| Function type and name			| Arguments						| Description|
| --------------------------------- | --------------------------------- | --------------------------------------------------------- |
| TrafficLights | LightColor startState, int position, int redDuration, int greenDuration| Traffic Lights constructor |
| int getGreenDuration |-| Returns green light duration time in seconds |
| int getRedDuration |-| Returns red light duration time in seconds |
| LightColor getColor |-| Returns current state of lights |
| int getPosition |-| Returns lights position on the road |
| int getTimer |-| Returns time in seconds left to light state change |
| void setTimer |int newTimer| Sets timer to newTimer |
| void setColor |LightColor newColor| Sets lights state to newColor |
| void setPosition | int newPosition | Sets lights position to newPosition in specified road |
| void setRedLightDuration | int duration | Sets red light duration to duration in seconds |
| void setGreenLightDuration | int duration | Sets green light duration to duration in seconds |

**YellowTrafficLights : public TrafficLights**
| Variable name			| Variable type							| Description|
| --------------------------------- | --------------------------------- | --------------------------------------------------------- |
| yellowLightDuration | int | Yellow light duration in seconds |
| redYellowLightDuration | int | Red-yellow light duration in seconds |

| Function type and name			| Arguments						| Description|
| --------------------------------- | --------------------------------- | --------------------------------------------------------- |
| YellowTrafficLights | LightColor startState, int position, int redDuration, int greenDuration, int redYellowDuration, int yellowDuration| Yellow Traffic Lights constructor |
| int getRedYellowDuration |-| Returns red-yellow light duration time in seconds |
| int getYellowDuration |-| Returns yellow light duration time in seconds |
| void setRedYellowLightDuration | int duration | Sets red-yellow light duration to duration in seconds |
| void setYellowLightDuration | int duration | Sets yellow light duration to duration in seconds |
Example code
```
#include "Basic Classes/Road.h"
#include "Basic Classes/TrafficLights.h"

int main() {
	Road* road = new Road(100, 1, 5);
	TrafficLights* light = new TrafficLights(LightColor(LightColor::red), 50, 7, 7);
	road->addLights(light);
	return 0;
}
```
## SimulationWindow
Filename with class: **SimulationWindow.h**  
Class name: **SimulationWindow**

| Object type | Description	|
| ------------- | ------------- |
| Button	| defines button in GUI |

| Function type and name			| Arguments							| Description												|
| --------------------------------- | --------------------------------- | --------------------------------------------------------- |
| void createSimulationWindow					| [Simulation*](#simulation) s, double randEventProb | Function creating simulation window											|


# Percentage of participation in tasks 

<table>
    <thead>
        <tr>
            <th>Task category</th>
            <th>Author name</th>
            <th>Percentage particiption</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan=2>Project management</td>
            <td>Kacper Chrzanowski</td>
            <td>90%</td>
        </tr>
        <tr>
          <td>Weronika Drożdż</td>
          <td>10%</td>
        </tr>
        <tr>
          <td>Git and libraries support</td>
          <td>Kacper Chrzanowski</td>
          <td>100%</td>
        </tr>
        <tr>
            <td rowspan=3>GUI and connecting modules</td>
            <td>Weronika Drożdż</td>
            <td>47.5%</td>
        </tr>
        <tr>
            <td>Filip Stodolny</td>
            <td>47.5%</td>
        </tr>
        <tr>
          <td>Kacper Chrzanowski</td>
          <td>5%</td>
        </tr>
        <tr>
          <td rowspan=4>Transition function </td>
          <td>Gabor Łukjaniuk</td>
          <td>95%</td>
        </tr>
        <tr>
          <td>Kacper Chrzanowski</td>
          <td>2%</td>
        </tr>
        <tr>
          <td>Weronika Drożdż</td>
          <td>1.5%</td>
        </tr>
        <tr>
          <td>Filip Stodolny</td>
          <td>1.5%</td>
        </tr>
        <tr>
          <td rowspan=6>Basic Classes</td>
          <td>Kacper Chrzanowski</td>
          <td>16.6%</td>
        </tr>
        <tr>
          <td>Weronika Drożdż</td>
          <td>16.6%</td>
        </tr>
        <tr>
          <td>Dominik Dzięgielewski</td>
          <td>16.6%</td>
        </tr>
        <tr>
          <td>Andrey Kmet</td>
          <td>16.6%</td>
        </tr><tr>
          <td>Gabor Łukjaniuk</td>
          <td>16.6%</td>
        </tr>
        <tr>
          <td>Filip Stodolny</td>
          <td>16.6%</td>
        </tr>
        <tr>
          <td rowspan=3>JSON support</td>
          <td>Dominik Dzięgielewski</td>
          <td>47.5%</td>
        </tr>
        <tr>
          <td>Andrey Kmet</td>
          <td>47.5%</td>
        </tr>
        <tr>
          <td>Kacper Chrzanowski</td>
          <td>5%</td>
        </tr>
        <tr>
          <td rowspan=6>Documentation</td>
          <td>Kacper Chrzanowski</td>
          <td>25%</td>
        </tr>
        <tr>
          <td>Dominik Dzięgielewski</td>
          <td>20%</td>
        </tr>
        <tr>
          <td>Andrey Kmet</td>
          <td>20%</td>
        </tr>
        <tr>
          <td>Weronika Drożdż</td>
          <td>11,6%</td>
        </tr>
        <tr>
          <td>Gabor Łukjaniuk</td>
          <td>11,6%</td>
        </tr>
        <tr>
          <td>Filip Stodolny</td>
          <td>11,6%</td>
        </tr>
        <tr>
          <td rowspan=2>Density plot</td>
          <td>Kacper Chrzanowski</td>
          <td>50%</td>
        </tr>
        <tr>
          <td>Gabor Łukjaniuk</td>
          <td>50%</td>
        </tr>
    </tbody>
</table>
