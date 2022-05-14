#pragma once

#include "Localization.h"
#include "../Basic Classes/Generator.h"

class GeneratorLocalization : public Localization {
protected:
    Generator* generator;

public:
    GeneratorLocalization(int xPosition, int yPosition, Generator* generator);
    void draw(double cellWidth, double cellHeight);
};