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
    int laneEndsMergeLength = laneEndsMergeR->getLength();
    int laneEndsMergeHeight = laneEndsMergeR->getHeight();
    sf::RectangleShape roadRectangle(sf::Vector2f(cellSize * laneEndsMergeLength, cellSize * (laneEndsMergeHeight + 1)));
    rotateShape(cellSize, &roadRectangle, laneEndsMergeLength, laneEndsMergeHeight + 1, 0, 0, false, moveDirection);
    roadRectangle.setFillColor(sf::Color(211, 211, 211));
    shapes->push_back(roadRectangle);
    for (int i = 0; i < laneEndsMergeHeight; i++) {
        for (int j = 0; j < laneEndsMergeLength; j++) {
            createCellShapes(cellSize, shapes, laneEndsMergeR->getLanes()[i][j], laneEndsMergeLength, laneEndsMergeHeight + 1, j, i, moveDirection);
        }
    }
    for (int i = 0; i < laneEndsMergeLength; i++) {
        createCellShapes(cellSize, shapes, laneEndsMergeR->getEndingLanes()[1][i], laneEndsMergeLength, laneEndsMergeHeight + 1, i, laneEndsMergeHeight, moveDirection);
    }
}