#pragma once

#include "Localization.h"
#include "../Models/SmartCrossing.h"

class SmartCrossingLocalization : public Localization {
    protected:
        SmartCrossing* smartCrossing;

    public:
        SmartCrossingLocalization(int xPosition, int yPosition, SmartCrossing* smartCrossing);
        void prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes);
};