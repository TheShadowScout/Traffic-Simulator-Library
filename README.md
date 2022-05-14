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
5.7. [TrafficLights](#trafficlights)    
5.8. [CarHolder](#carholder)  
5.9. [Statistics](#statistics)  
5.10. [Observer](#observer)  
5.11. [RoadCell](#roadcell)  
5.12. [BasicCrossingInput](#basiccrossinginput)  
5.13. [Crossing](#crossing)  
5.14. [LaneEndsMerge](#laneendsmerge)  
5.15. [Obstacle](#obstacle)  
5.16. [SmartCrossing](#smartcrossinginput)
6. [Models](#models)  
6.1 [RGTrafficLights](#rgtrafficlights)  
6.2 [RGYTrafficLights](#rgytrafficlights)  
6.2 [BasicCrossing](#basiccrossing)  
6.3 [SmartCrossing](#smartcrossing)  
6.4 [LaneEndsMergeL](#laneendsmergel)  
6.5 [LaneEndsMergeR](#laneendsmerger)  
6.6 [LaneEndsMergeLR](#laneendsmergelr)  
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
4. Install [Gnuplot](http://www.gnuplot.info/download.html) and adds it to environment variables / PATH
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
Demo
```
#include "Basic Classes/Simulation.h"
#include "Basic Classes/RGTrafficLights.h"
#include "Basic Classes/SmartCrossing.h"
#include "Basic Classes/BasicCrossing.h"
#include "Basic Classes/LaneEndsMergeL.h"
#include "Basic Classes/LaneEndsMergeLR.h"
#include "Basic Classes/LaneEndsMergeR.h"

int main() {
	std::srand(time(NULL));

	Map* map = new Map("test");

	Road* road1 = new Road(1, 1, 1);
	Road* road2 = new Road(1, 1, 1);

	//road2->addObstacle(9, 0, 0);

	map->addRoad(road1);
	map->addRoad(road2);

	Generator* generator1 = new Generator(1, 1.0);
	Generator* generator2 = new Generator(1, 1.0);

	map->addGenerator(generator1);
	map->addGenerator(generator2);

	linkCells(generator1, road1->getLaneHead(0));
	linkCells(generator2, road2->getLaneHead(0));

	BasicCrossing* crossing1 = new BasicCrossing(11, 11, 1);
	crossing1->addNewCrossingLane('S', 5, 'E', 5, 1);
	crossing1->addNewCrossingLane('N', 5, 'W', 5, 1);

	crossing1->linkRoadLaneToCrossing(road1->getLaneTail(0), 'S', 5);
	crossing1->linkRoadLaneToCrossing(road2->getLaneTail(0), 'N', 5);

	//RGTrafficLights* lights = new RGTrafficLights(LightColor::green, 10, 10);
	//crossing1->addTrafficLights(lights, 'S', 5);

	map->addCrossing(crossing1);

	Simulation simulation(map, 0, 1, 0);
	simulation.initiateSimulation();

	for (int i = 0; i < 100; i++) {
		simulation.transitionFunc();
		std::cout << simulation.toString() << std::endl;
	}
}
```

# Basic classes
## Cell
Filename with class: **Cell.h**  
Class name: **Cell**  

| Variable name	  | Variable type			              | Description											                                          |
| -------------   |-                                | -----------------------------------------------------------------         |
| carHolder       |[CarHolder](#carholder)*                       | variable that holds a pointer to [CarHolder][#carholder] adjacent to top  |
| rightCell		    |Cell*                            | variable that holds a pointer to [Cell](#cell) adjacent to right	        |
| leftCell		    |Cell*                            | variable that holds a pointer to [Cell](#cell) adjacent to left	          |
| previousCell	  |Cell*                            | variable that holds a pointer to [Cell](#cell) adjacent to top	          |
| maxSpeed	      |int                              |variable that holds a max speed in [Cell](#cell)	                          |
| trafficLight	  |[TrafficLights](#traffic-lights)*|variable that holds a pointer to [TrafficLights](#traffic-lights)          |
| isObstacleAhead | boolean                         | flag that informs is an obstacle ahead of current [Cell](#cell)           |

| Function type and name			                                | Arguments							                      | Description																				                                        |
| ---------------------------------                           | ---------------------------------	          | ----------------------------------------------------------------------------------------- |
| [Cell*](#cell)						                                  | ---------------------------------	          | Class constructor																			                                    |
| [Cell*](#cell)		                                          | int maxSpeed	                              | Class constructor																		                                    	|
| ~[Cell*](#cell)                                             | ---------------------------------           | Class destructor
| void setVehicle					                                    | [Vehicle*](#vehicle) vehicle		            | Function sets in current [Cell](#cell) new pointer to [Vehicle](#vehicle)					        |
| void setRightCell					                                  | [Cell*](#cell) newRightCell		              | Function sets in current [Cell](#cell) new pointer to [Cell](#cell) adjacent to the right	|
| void setLeftCell					                                  | [Cell*](#cell) newLeftCell		              | Function sets in current [Cell](#cell) new pointer to [Cell](#cell) adjacent to the left	|
| void setPreviousCell			      	                          | [Cell*](#cell) newPreviousCell	            | Function sets in current [Cell](#cell) new pointer to  [Cell](#cell) adjacent to bottom	  |
| virtual void setNextCell					                          | [Cell*](#cell) newNextCell		              | Function sets in current [Cell](#cell) new pointer to [Cell](#cell) adjacent to top		    |
| [Vehicle*](#vehicle)  getVehicle	                          | ---------------------------------	          | Function returns pointer to [Vehicle](#vehicle) in current cell							              |
| void setCarHolder                                           | [CarHolder*](#carholder) carHolder          | Function sets in current [Cell](#cell) new pointer to [CarHolder](#carholder)             |
| [Cell*](#cell)  getRightCell		                            | ---------------------------------	          | Function returns pointer to [Cell](#cell) adjacent to right							                	|
| [Cell*](#cell)  getLeftCell		                              | ---------------------------------	          | Function returns pointer to [Cell](#cell) adjacent to left								                |
| [Cell*](#cell)  getPreviousCell	                            | ---------------------------------	          | Function returns pointer to [Cell](#cell) adjacent to bottom								              |
| virtual [Cell*](#cell)  getNextCell		                      | ---------------------------------	          | Function returns pointer to [Cell](#cell) adjacent to top									                |
| void setMaxSpeed	                                          | int maxSpeed	                              | Function sets max speed in [Cell](#cell)							                                    |
| void getMaxSpeed	                                          | ---------------------------------	          | Function returns max speed in [Cell](#cell)			                                          |
| void createJSON	                                            | ---------------------------------	          | Function creates JSON data tree of current [Cell](#cell)                                  |
| [TrafficLights](#traffic-lights)* getTrafficLight	          | ---------------------------------	          | Function return pointer to  [TrafficLights](#traffic-lights) if present in [Cell](#cell)  |
| void setTrafficLight	                                      | [TrafficLights](#traffic-lights)* newLight	| Function sets pointer to [TrafficLights](#traffic-lights)                                 |
| bool getObstacleAhead                                       | ---------------------------------           | Function returns flag which informs about an obstacle ahead of current [Cell](#cell)      |
| void setObstacleAhead                                       | bool isObstacleAhead                        | Function sets flag which informs about an obstacle ahead of current [Cell](#cell)         |


## Road
Filename with class: **Road.h**  
Class name: **Road**  

| Variable name       | Variable type			                                      | Description                               																         |
| -------------       | -----------------------------                           | -------------------------------------------------------------------------          |
| ID		              | int					                                            | variable that holds a [Road](#road) ID		                  							         |
| maxSpeed		        | int					                                            | variable that holds max vehicle speed										                           |
| length              | int                                                     | variable that holds road length                                                    |
| height              | int                                                     | variable that holds road height                                                    |
| name			          | string				                                          | variable that holds a [Road](#road) name									                         |
| lanes			          | vector<vector<[Cell](#cell)>>	                          | variable that holds vector of [Cells](#cell) creating up the road		    	         |
| trafficLights			  | vector<[TrafficLights]*(#traffic-lights)>	              | variable that holds vector of [Traffic Lights](#traffic-lights) set up on the road |
                    
| Function type and name	                                    | Arguments					                                                          | Description												                                                          |
| -------------------------                                   | --------------------------------------------------                          | ----------------------------------------------------------------------                      | 
| [Road](#Road)				                                        | string name, int length, int height, int maxSpeed                           | Class constructor									 	                                                        |
| [Road](#Road)				                                        | int length, int height, int maxSpeed                                        | Class constructor									 	                                                        |
| ~[Road](#Road)                                              | ---                                                                         | Class destructor									 	                                                        |
| [Cell*](#cell) getLaneHead                                  | int lane                                                                    | Function returns pointer to lane head                                                       |
| [Cell*](#cell) getLaneTail                                  | int lane                                                                    | Function returns pointer to lane tail                                                       |
| void setMaxSpeed		                                        | int maxSpeed				                                                        | Function sets new max speed in current [Road](#Road)		                                    |
| void setName				                                        | string name				                                                          | Function sets name in current [Road](#Road)				                                          |
| int getMaxSpeed			                                        | --------------------------------------------------                          | Function returns max speed of current [Road](#Road)		                                      | 
| int getID			                                              | --------------------------------------------------                          | Function returns ID of current [Road](#Road)	                                              |
| string getName			                                        | --------------------------------------------------                          | Function returns name of current [Road](#Road)			                                        |
| vector<[Cell*](#cell)> getCellsWithVehs                     | ---                                                                         | Function returns vector of pointers to [Cells*](#cell) which contains a [Vehicle](#vehicle) |
| int getLength			                                          | --------------------------------------------------                          | Function returns length of current [Road](#Road)			                                      |
| int getHeight		                                            | --------------------------------------------------                          | Function returns height of current [Road](#Road)			                                      |
| vector<vector<[Cell*](#cell)>> getLanes                     | --------------------------------------------------                          | Function returns lanes of current [Road](#road)                                             |
| int getPassableCellsCnt()                                   | --------------------------------------------------                          | Function return number of passable [Cells](#cell) of current [Road](#road)                  |
| void createJSON			                                        | --------------------------------------------------                          | Function creates JSON data tree of current [Road](#Road)	                                  |
| string tempToString			                                    | -------------------------                                                   | Function return [Road](#Road) as string                                                     |
| void addTrafficLightsToOneLane                              | [TrafficLights*](#traffic-lights) newLight, int distanceFromHead, int lane  | Function adds new [TrafficLights] to one selected [Road](#Road)                             |
| void addTrafficLightsToAllLanes                             | [TrafficLights*](#traffic-lights) newLight, int distanceFromHead            | Function adds new [TrafficLights] to all [Roads](#Road)                                     |
| void addObstacle                                            | int distanceFromHead, int lane, int spotDistance = 0                        | Function adds new obstacle in selected [Road](#Road)                                        |
| void fillWithVehs                                           | double fillingDegree                                                        | Function fills [Road](#Road) with given filling degree between 0 and 1                      |
| vector<[TrafficLights*](#traffic-lights)> getTraficLights		| ---                                                                         | Function returns vector of lights on the [Road](#Road)                                      |
| string toString                                             | --------------------------------------------------                          | Function returns string which represents current [Road](#Road)                                      |


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

| Variable name  | Variable type						                	| Description																                                |
| -------------  | -------------------------------------      | ------------------------------------------------------------------------- |
| name			     | string								                      | variable that holds a [Map](#map) name									                  |
| roads			     | map<[Road](#road), int>				            | variable that holds a map of [Roads](#road)								                |
| generators	   | map<[Generator](#generator), int>		      | variable that holds a map of [Generators](#generator)					          	|
| crossings      | vector<[Crossing*](#crossing)>             | vector that holds [Crossings](#crossings)                                 |
| laneEndsMerges | vector<[LaneEndsMerge*](#lane-ends-merge)> | vector that holds [LaneEndsMerge](#lane-ends-merge)                       |

| Function type and name	| Arguments		| Description												|
| ------------------------- | ------------- | --------------------------------------------------------- |
| [Map](#map)					| string name	| Class constructor	|
| ~[Map](#map)    | --- | Class destructor
| void addRoad					| [Road*](#road) road	| Function adds road to [Map](#map)	|
| void addGenerator					| Generator* generator	| Function adds generator to [Map](#map)	|
| void addCrossing | [Crossing*](#crossing) | Function adds [Crossing](#crossing) to [Map](#map) |
| void addLaneEndsMerge | [LaneEndsMerge*](#lane-ends-merge) laneEndsMerge | Function adds [LaneEndsMerge] to [Map](#map)
| void updateMap | vector<[Cell*](#cell)>* cellsWithVehs | Function updates [Map](#map) vector of [Cells](#cell)
| vector<[Crossing*](#crossing) getCrossings | --- | Function returns vector of [Crossings](#crossing)
| vector<[LaneEndsMerge*](#lane-ends-merge)> | --- | Function returns vector of [LaneEndsMerge](#lane-ends-merge) |
| vector<Road*> getRoads				|  -------------------------------------------------- 	| Function returns vector [Roads](#road)	|
| int getMapPassableCellsCnt | --- | Function returns number of passable [Cells](#cell) of current [Map](#map)
| void fillWithVehs                                           | double fillingDegree                                                        | Function fills [Road](#Road) with given filling degree between 0 and 1                      |
| vector<Generator*> getGenerators				|  -------------------------------------------------- 	| Function returns vector [Generators](#generator)	|
| vector<Cell*> getCellsWithVehs			|  -------------------------------------------------- 	| Function returns [Cells](#cell) with [Vechicles](#vehicle)	|
| string getName			|  -------------------------------------------------- 	| Function returns name of [Map](#map)	|
| void createJSON			| -------------------------------------------------- | Function creates JSON data tree of current [Map](#map)		|
| string toString                                             | --------------------------------------------------                          | Function returns string which represents current [Map](#map) 

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
| ID  | int | variable that holds ID of [Generator](#generator) |
| IDcnt			| int static			| variable that holds a [Generator](#generator) ID for a new create vehicle	|
| createVehProb | double | variable that holds a probability of creating [Vehicle](#vehicle) every iteration | 

| Function type and name	| Arguments	| Description																		|
| ------------- | ------------- | ----------------------------------------------------- |
| Generator			| string name, int maxSpeed, double createVehProb | Class constructor																	|
| Generator			| int maxSpeed, double createVehProb | Class constructor	|															|
| int getID | --- | Function returns ID of current [Generator](#generator) |
| string getName			| ------------------------- | Function returns name of current [Generator](#generator)		|
| void createVeh				| --------- | Function creates new [Vehicle](#vehicle) inside current [Generator](#generator)	|
| string toString | --- | Function returns string which represents current [Generator](#generator) |

## Simulation
Filename with class: **Simulation.h**  
Class name: **Simulation**  

| Variable name | Variable type	| Description														|
| ------------- | ------------- | ----------------------------------------------------------------- |
| cellsWithVehs | vector<[Cell*](#cell)> | vector that holds [Cells](#cell) with [Vehicles](#vehicle) |
| randEventProb	| double		| variable that holds random event									|
| simMap		| [Map*](#map)	| object that holds simulation of [map](#map)								|
|	simStats | [Statistics*](#statistics) | object that holds [Statistics](#statistics) of [Simulation](#simulation) |
|	observers | vector<[Observer*](#observer)> | vector that holds [Observers](#observer) | 
|	seed | int | variable that holds seed for randomEngine if given |
|	randomEngine | default_random_engine | variable that holds random engine for shuffling vector of [Vehicles](#vehicle) | 
|	minSafeSpace | int | variable that holds minimal distance between two [Vehicles](#vehicles) while changing lane of [Road](#road) |
|	shuffleIfCompetition | bool | variable that holds a flag for shuffling vector of [Vehicles](#vehicle) |

| Function type and name			| Arguments							| Description												|
| --------------------------------- | --------------------------------- | --------------------------------------------------------- |
| [Simulation](#simulation)					| [Map*](#map) simMap, double randEventProb, int minSafeSpace, int seed = NULL, bool shuffleIfCompetition = true | Class constructor											|
| [Map](#map) getSimulationMap | --- | Function returns [Simulation](#simulation) [Map](#map) |
| [Statistics*](#statistics) getSimulationStatistics | --- | Function returns [Statistics](#statistics) of [Simulation](#simulation) |
| [Observer*](#observer) getSimulationObserver | --- | Function returns [Observer](#observer) of [Simulation](#simulation) |
| void addObserver | [Observer*](#observer) observer | Function sets [Simulation](#simulation) [Observer](#observer) |
| void transitionFunc				| --------------------------------- | Function returns new position to [Vehicle](#vehicle) in next tick|
| void saveStatisticsToFile | string outFolder = "StatisticsHistory/" | Function saves [Statistics*](#statistics) to file in selected folder |
| void initiateSimulation | --- | Function starts [Simulation](#simulation) |
| string toString				| --------------------------------- | Function returns string which represents current [Simulation](#simulation)|

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
# SimulationWindow
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
