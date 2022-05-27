#pragma once

# include "LaneEndsMergeLocalizationR.h"

LaneEndsMergeLocalizationR::LaneEndsMergeLocalizationR(int xPosition, int yPosition, LaneEndsMergeR* laneEndsMergeR, char moveDirection) : Localization(xPosition, yPosition), laneEndsMergeR(laneEndsMergeR), moveDirection(moveDirection) {
        if (!(moveDirection == 'N' || 
        moveDirection == 'E' || 
        moveDirection == 'S' || 
        moveDirection == 'W')) {
        throw std::invalid_argument("moveDirection is not one of {N, E, S, W}");
    }
}

void LaneEndsMergeLocalizationR::prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes) {
    ;
}