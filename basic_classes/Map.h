#pragma once

#include<iostream>
#include "Generator.h"
#include "Destructor.h"
#include "Teleporter.h"
#include "Road.h"
#include "Cell.h"
#include <map>
#include <list>
using namespace std;


class  Map: public FuncCell 
{
public:
	Map() {
		name = "Mapa";
	}

	void Func() {
		cout << "Generated map object" << endl;
	}

	void CreateXML();

	map<Road, int> roads;
	map<Generator, int> generators;
	map<Destructor, int> destruktors;
	map<Teleporter, int> teleporters;

	list<Cell> cellsWithCars;

};
