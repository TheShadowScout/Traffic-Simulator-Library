#pragma once

#include "Map.h"

using boost::property_tree::ptree;

class DataSaving {
	Map* mapa;

public:
	DataSaving(Map* mapa);
	void saveData();
};
