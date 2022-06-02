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

void LaneEndsMergeLocalizationL::prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes) {
    int laneEndsMergeLength = laneEndsMergeL->getLength();
    int laneEndsMergeHeight = laneEndsMergeL->getHeight();
    sf::RectangleShape roadRectangle(sf::Vector2f(cellSize * laneEndsMergeLength, cellSize * (laneEndsMergeHeight + 1)));
    rotateShape(cellSize, &roadRectangle, laneEndsMergeLength, laneEndsMergeHeight + 1, 0, 0, false, moveDirection);
    roadRectangle.setFillColor(sf::Color(211, 211, 211));
    shapes->push_back(roadRectangle);
    for (int i = 0; i < laneEndsMergeHeight; i++) {
        for (int j = 0; j < laneEndsMergeLength; j++) {
            createCellShapes(cellSize, shapes, laneEndsMergeL->getLanes()[i][j], laneEndsMergeLength, laneEndsMergeHeight + 1, j, i + 1, moveDirection);
        }
    }
    for (int i = 0; i < laneEndsMergeLength; i++) {
        createCellShapes(cellSize, shapes, laneEndsMergeL->getEndingLanes()[0][i], laneEndsMergeLength, laneEndsMergeHeight + 1, i, 0, moveDirection);
    }
}