# Library for creating a traffic simulator 
Student project of a library in C ++ used to create a road traffic simulator. 

# Authors
*Kacper Chrzanowski*  
*Weronika Drożdż*  
*Gabor Łukjaniuk*  
*Filip Stodolny*  
*Dominik Dzięgielewski*  
*Andrey Kmet*  

# Table of Contents
1. [Introduction](#introduction)
2. [Basic classes](#basic-classes)  
2.1. [Cell](#cell)  
2.2. [Road](#road)  
2.3. [Map](#map)  
2.4. [Vehicle](#vehicle)  
2.5. [Special cells](#special-cells)  
2.5.1 [Generator](#generator)  
2.5.2 [Destructor](#destructor)  
2.5.3 [Teleporter](#teleporter)  

# Introduction
# Basic classes
## Cell
Filename with class: **Cell.h**  
Class name: **Cell**  

| Variable name	| Description														|
| ------------- | ----------------------------------------------------------------- |
| vehicle       | variable that holds a pointer to [Vehicle](#vehicle)				|
| rightCell		| variable that holds a pointer to [Cell](#cell) adjacent to right	|
| leftCell		| variable that holds a pointer to [Cell](#cell) adjacent to left	|
| nextCell		| variable that holds a pointer to [Cell](#cell) adjacent to bottom |
| previousCell	| variable that holds a pointer to [Cell](#cell) adjacent to top	|

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

## Road
Filename with class: **Road.h**  
Class name: **Road**  

| Variable name | Variable type			| Description																|
| ------------- | --------------------- | ------------------------------------------------------------------------- |
| IDRoad		| int					| variable that holds a [Road](#road) ID									|
| maxSpeed		| int					| variable that holds max vehicle speed										|
| name			| string				| variable that holds a [Road](#road) name									|
| road			| list<[Cell](#cell)>	| variable that holds a list of [Cells](#cell) creating up the road			|
| head			| list<[Cell](#cell)>	| variable that holds a list of [Cells](#cell) creating up the head of road |
| tail			| list<[Cell](#cell)>	| variable that holds a list of [Cells](#cell) creating up the tail of road |

| Function type and name	| Arguments					| Description												|
| ------------------------- | ------------------------- | --------------------------------------------------------- |
| void Road					| int maxSpeed, string name | Class constructor											|
| void setMaxSpeed			| int maxSpeed				| Function sets new max speed in current [Road](#road)		|
| void setName				| string name				| Function sets name in current [Road](#road)				|
| int getMaxSpeed			| ------------------------- | Function returns max speed of current [Road](#road)		| 
| string getName			| ------------------------- | Function returns name of current [Road](#road)			|
| void createXML			| ------------------------- | Function creates new XML file of current [Road](#road)	|

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
| void Map					| string name	| Class constructor											|
| void createXML			| -------------	| Function creates new XML file of current [Map](#map)		|

## Vehicle
Filename with class: **Vehicle.h**  
Class name: **Vehicle**  

| Variable name | Variable type	| Description										|
| ------------- | ------------- | ------------------------------------------------- |
| name			| string		| variable that holds a [Vehicle](#vehicle) name	|
| ID			| int			| variable that holds a [Vehicle](#vehicle) ID		|
| speed			| int			| variable that holds a [Vehicle](#vehicle) speed	|

| Function type and name	| Arguments					| Description												|
| ------------------------- | ------------------------- | --------------------------------------------------------- |
| void Vehicle				| string name, int speed	| Class constructor											|
| string getName			| ------------------------- | Function returns name of current [Vehicle](#vehicle)		|
| int getID					| ------------------------- | Function returns ID of current [Vehicle](#vehicle)		|
| int getSpeed				| ------------------------- | Function returns speed of current [Vehicle](#vehicle)		|
| void setSpeed				| int speed					| Function sets new speed of current [Vehicle](#vehicle)	|

## Special cells
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

## Destructor
Filename with class: **Destructor.h**  
Class name: **Destructor**  
Inherits from: [Cell](#cell)

| Variable name | Variable type	| Description											|
| ------------- | ------------- | ----------------------------------------------------- |
| name			| string		| variable that holds a [Destructor](#destructor) name	|

| Function type and name	| Arguments	| Description																	|
| ------------------------- | --------- | ----------------------------------------------------------------------------- |
| void Destructor			| --------- | Class constructor																|
| void remove				| --------- | Function removes a [Vehicle](#vehicle) from current [Destructor](#destructor)	|

## Teleporter
Filename with class: **Teleporter.h**  
Class name: **Teleporter**  
Inherits from: [Cell](#cell)

| Variable name | Variable type	| Description											|
| ------------- | ------------- | ----------------------------------------------------- |
| name			| string		| variable that holds a [Teleporter](#teleporter) name	|

| Function type and name	| Arguments										| Description																										|
| ------------------------- | --------------------------------------------- | ----------------------------------------------------------------------------------------------------------------- |
| void Teleporter			| --------------------------------------------- | Class constructor																									|
| void teleport				| [Teleporter*](#teleporter) outputTeleporter	| Function moves [Vehicle](#vehicle) from current [Teleporter](#teleporter) to specified [Teleporter](#teleporter)	|
