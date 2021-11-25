#pragma once

#include "Cell.h"
#include <iostream>

class Generator : public FuncCell
{
	public:
		Generator() {
			name = "Generator";
		}
		void DTGFunc() {
			this.vehicle = new Vehicle();
			std::cout << "Generated car object" << std::endl;
		}
};