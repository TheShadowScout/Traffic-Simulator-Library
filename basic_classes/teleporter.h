#pragma once

#include "funccell.h"
#include <iostream>

class Teleporter : public FuncCell
{
	public:
		Teleporter() {
			name = "Teleporter";
		}
		void DTGFunc() {
			std::cout << "Moved car object from tail to head" << std::endl;
		}
};