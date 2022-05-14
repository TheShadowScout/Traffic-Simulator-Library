#pragma once

# include "LaneEndsMergeLocalizationLR.h"

LaneEndsMergeLocalizationLR::LaneEndsMergeLocalizationLR(int xPosition, int yPosition, LaneEndsMergeLR* laneEndsMergeLR, char moveDirection) : Localization(xPosition, yPosition), laneEndsMergeLR(laneEndsMergeLR), moveDirection(moveDirection) {
        if (!(moveDirection == 'N' || 
        moveDirection == 'E' || 
        moveDirection == 'S' || 
        moveDirection == 'W')) {
        throw std::invalid_argument("moveDirection is not one of {N, E, S, W}");
    }
}

void LaneEndsMergeLocalizationLR::draw(double cellWidth, double cellHeight) {
    ;
}