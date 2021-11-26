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

| Variable name|                               Description                                |
| ------------- | ----------------------------------------------------------------- |
| vehicle       | variable that holds a pointer to an object of type [Vehicle](#vehicle)|
| right_cell    | variable that holds a pointer to right object of type [Cell](#cell)       |
| left_cell     | variable that holds a pointer to left object of type [Cell](#cell)       |
| next_cell     | variable that holds a pointer to next object of type [Cell](#cell)       |
| previous_cell | variable that holds a pointer to previous object of type [Cell](#cell)       |

|   Function name   |   Arguments   |   Description  |
|   -------------   |   ---------   |   ----- |
|   void Cell       |   -           |   Class constructor |
|   void set_vehicle | [Vehicle*](#vehicle) vehicle| Function sets in current [cell](#cell) new pointer to [vehicle](#vehicle)
|   void set_right_cell | [Cell*](#cell) new_right_cell| Function sets in current [cell](#cell) new pointer to [cell](#cell) adjacent to the right
|   void set_left_cell | [Cell*](#cell) new_left_cell| Function sets in current [cell](#cell) new pointer to [cell](#cell) adjacent to the left
|   void set_previous_cell | [Cell*](#cell) new_previous_cell| Function sets in current [cell](#cell) new pointer to  [cell](#cell) adjacent to bottom
|   void set_next_cell | [Cell*](#cell) new_next_cell| Function sets in current [cell](#cell) new pointer to [cell](#cell) adjacent to top
|   [Vehicle*](#vehicle)  get_vehicle    |-| Function returns pointer to [vehicle](#vehicle) in current cell
|   [Cell*](#cell)  get_right_cell    |-| Function returns pointer to [cell](#cell) adjacent to right
|   [Cell*](#cell)  get_left_cell    |-| Function returns pointer to [cell](#cell) adjacent to left
|   [Cell*](#cell)  get_previous_cell    |-| Function returns pointer to [cell](#cell) adjacent to bottom
|   [Cell*](#cell)  get_next_cell    |-| Function returns pointer to [cell](#cell) adjacent to top

### Road
Filename with class: **Road.h**
Class name: **Road**

| Variable name|Variable type|                               Description                                |
| ------------- | ------------| ----------------------------------------------------------------- |
| IDRoad       |int| variable that holds a [road](#road) ID|
| maxSpeed    |int| variable that holds max vehicle speed       |
| name     |string| variable that holds a [road](#road) name       |
| road     |list<[Cell](#cell)>| variable that holds a list of [Cells](#cell) creating up the road      |
| head |list<[Cell](#cell)>| variable that holds a list of [Cells](#cell) creating up the head of road       |
| tail |list<[Cell](#cell)>| variable that holds a list of [Cells](#cell) creating up the tail of road    |

|   Function name   |   Arguments   |   Description  |
|   -------------   |   ---------   |   ----- |
|   void Road       |   int maxSpeed, string name           |   Class constructor |
|   void setMaxSpeed | int maxSpeed| Function sets new max speed in current [road](#road)
|   void setName | string name| Function sets name in current [road](#road) |
|   int getMaxSpeed | -| Function returns max speed of current [road](#road) | 
|   string getName | -| Function returns name of current [road](#road) |
|   void createXML| - | Function creates new XML file of current [road](#road) |
### Map
### Vehicle
### Special cells
#### Generator
#### Destructor
#### Teleporter
