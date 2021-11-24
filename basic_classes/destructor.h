#pragma once

#include "funccell.h"
#include <iostream>

class Destructor : public FuncCell
{
	public:
		Destructor() {
			name = "Destructor";
		}
		void DTGFunc() {
			std::cout << "Deleted car object" << std::endl;
		}
};