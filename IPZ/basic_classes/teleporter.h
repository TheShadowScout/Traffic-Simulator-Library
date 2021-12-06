#pragma once
#include "Cell.h"
#include <iostream>

class Teleporter : public Cell
{
	std::string name;
	
	public:
	Teleporter() {
		name = "Teleporter";
	}

	//outputTeleporter - teleporter do którego zostanie przeniesiony pojazd
	void teleport(Teleporter* outputTeleporter) {
		Vehicle* vehicle = new Vehicle("pojazd", 4);
		outputTeleporter->setVehicle(vehicle);
		vehicle = NULL;
		std::cout << "Moved car object from tail to newCell" << std::endl;
	}
};