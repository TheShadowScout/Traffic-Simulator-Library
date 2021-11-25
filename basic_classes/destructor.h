#pragma once

#include "Cell.h"
#include <iostream>

class Destructor : public Cell
{
	public:
		Destructor() {
			name = "Destructor";
		}
		void DeleteVehicle() {
			delete this.vehicle;
			std::cout << "Deleted car object" << std::endl;
		}
};