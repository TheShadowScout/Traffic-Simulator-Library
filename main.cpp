#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "generator.h"
#include "destructor.h"
#include "teleporter.h"
using namespace std;

int main()
{
    Generator g1;
    Destructor d1;
    Teleporter t1;

    g1.Func();
    d1.Func();
    t1.Func();
    return 0;
}