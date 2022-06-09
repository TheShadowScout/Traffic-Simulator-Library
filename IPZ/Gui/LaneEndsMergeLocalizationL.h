#pragma once

#include "Localization.h"
#include "../Models/LaneEndsMergeL.h"

class LaneEndsMergeLocalizationL : public Localization {
protected:
    LaneEndsMergeL* laneEndsMergeL;
    char moveDirection;

public:
    LaneEndsMergeLocalizationL(int xPosition, int yPosition, LaneEndsMergeL* laneEndsMergeL, char moveDirection = 'E');
    void prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes);
};