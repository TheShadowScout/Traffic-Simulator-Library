#pragma once

#include "funccell.h"
#include <iostream>

class Generator : public FuncCell
{
	public:
		Generator() {
			name = "Generator";
		}
		void DTGFunc() {
			std::cout << "Generated car object" << std::endl;
		}
};