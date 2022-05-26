#pragma once

#include "Localization.h"
#include "../Basic Classes/Road.h"

class RoadLocalization : public Localization {
protected:
    Road* road;
    char moveDirection;

public:
    RoadLocalization(int xPosition, int yPosition, Road* road, char moveDirection = 'E');
    void draw(float cellSize, sf::RenderWindow* window);
};