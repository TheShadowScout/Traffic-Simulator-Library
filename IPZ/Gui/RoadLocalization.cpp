#pragma once

# include "RoadLocalization.h"

RoadLocalization::RoadLocalization(int xPosition, int yPosition, Road* road, char moveDirection) : Localization(xPosition, yPosition), road(road), moveDirection(moveDirection) {
        if (!(moveDirection == 'N' || 
        moveDirection == 'E' || 
        moveDirection == 'S' || 
        moveDirection == 'W')) {
        throw std::invalid_argument("moveDirection is not one of {N, E, S, W}");
    }
}

void RoadLocalization::draw(double cellWidth, double cellHeight) {
    ;
}