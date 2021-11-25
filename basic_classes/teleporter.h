#pragma once

#include "funccell.h"
#include <iostream>

class Teleporter : public FuncCell
{
	public:
		Teleporter() {
			name = "Teleporter";
		}
		void Teleport(Cell newCell) {
			newCell.vehicle = this.vehicle;
			this.vehicle = NULL;
			std::cout << "Moved car object from tail to head" << std::endl;
		}
};