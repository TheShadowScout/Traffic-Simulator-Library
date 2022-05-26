#pragma once

#include "Localization.h"
#include "../Models/BasicCrossing.h"

class BasicCrossingLocalization : public Localization {
protected:
    BasicCrossing* basicCrossing;

public:
    BasicCrossingLocalization(int xPosition, int yPosition, BasicCrossing* basicCrossing);
    void draw(float cellSize, sf::RenderWindow * window);
};