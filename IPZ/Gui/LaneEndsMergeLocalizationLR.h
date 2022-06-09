#pragma once

#include "Localization.h"
#include "../Models/LaneEndsMergeLR.h"

class LaneEndsMergeLocalizationLR : public Localization {
protected:
    LaneEndsMergeLR* laneEndsMergeLR;
    char moveDirection;

public:
    LaneEndsMergeLocalizationLR(int xPosition, int yPosition, LaneEndsMergeLR* laneEndsMergeLR, char moveDirection = 'E');
    void prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes);
};