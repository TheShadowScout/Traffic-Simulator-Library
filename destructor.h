#pragma once

#include "funccell.h"
#include <iostream>

class Destructor : public FuncCell
{
	public:
		Destructor() {
			name = "Destructor";
		}
		void Func() {
			std::cout << "Deleted car object" << std::endl;
		}
};