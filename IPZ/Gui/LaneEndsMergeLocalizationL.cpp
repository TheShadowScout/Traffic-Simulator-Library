#pragma once

# include "LaneEndsMergeLocalizationL.h"

LaneEndsMergeLocalizationL::LaneEndsMergeLocalizationL(int xPosition, int yPosition, LaneEndsMergeL* laneEndsMergeL, char moveDirection) : Localization(xPosition, yPosition), laneEndsMergeL(laneEndsMergeL), moveDirection(moveDirection) {
        if (!(moveDirection == 'N' || 
        moveDirection == 'E' || 
        moveDirection == 'S' || 
        moveDirection == 'W')) {
        throw std::invalid_argument("moveDirection is not one of {N, E, S, W}");
    }
}

void LaneEndsMergeLocalizationL::draw(double cellWidth, double cellHeight) {
    ;
}