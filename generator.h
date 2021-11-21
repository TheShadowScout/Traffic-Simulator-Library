#pragma once

#include "funccell.h"
#include <iostream>

class Generator : public FuncCell
{
	public:
		Generator() {
			name = "Generator";
		}
		void Func() {
			std::cout << "Generated car object" << std::endl;
		}
};