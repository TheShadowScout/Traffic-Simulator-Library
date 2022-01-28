#pragma once

#include "../Basic Classes/Map.h"
#include <iostream>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;


class DataSaving {
	Map* mapa;

public:
	DataSaving(Map* mapa);
	void saveData();
};
