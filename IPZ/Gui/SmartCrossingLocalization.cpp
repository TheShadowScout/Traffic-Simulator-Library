#pragma once

# include "SmartCrossingLocalization.h"

SmartCrossingLocalization::SmartCrossingLocalization(int xPosition, int yPosition, SmartCrossing* smartCrossing) : Localization(xPosition, yPosition), smartCrossing(smartCrossing) { ; }

void SmartCrossingLocalization::prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes) {
    ;
}