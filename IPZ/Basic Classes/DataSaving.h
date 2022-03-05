#pragma once

#include <iostream>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Map.h"

using boost::property_tree::ptree;

class DataSaving {
	Map* mapa;

public:
	DataSaving(Map* mapa);
	void saveData();
};
