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

void LaneEndsMergeLocalizationLR::prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes) {
    int laneEndsMergeLength = laneEndsMergeLR->getLength();
    int laneEndsMergeHeight = laneEndsMergeLR->getHeight();
    sf::RectangleShape roadRectangle(sf::Vector2f(cellSize * laneEndsMergeLength, cellSize * (laneEndsMergeHeight + 2)));
    rotateShape(cellSize, &roadRectangle, laneEndsMergeLength, laneEndsMergeHeight + 2, 0, 0, false, moveDirection);
    roadRectangle.setFillColor(sf::Color(211, 211, 211));
    shapes->push_back(roadRectangle);
    for (int i = 0; i < laneEndsMergeHeight; i++) {
        for (int j = 0; j < laneEndsMergeLength; j++) {
            createCellShapes(cellSize, shapes, laneEndsMergeLR->getLanes()[i][j], laneEndsMergeLength, laneEndsMergeHeight + 2, j, i + 1, moveDirection);
        }
    }
    for (int i = 0; i < laneEndsMergeLength; i++) {
        createCellShapes(cellSize, shapes, laneEndsMergeLR->getEndingLanes()[0][i], laneEndsMergeLength, laneEndsMergeHeight + 2, i, 0, moveDirection);
    }
    for (int i = 0; i < laneEndsMergeLength; i++) {
        createCellShapes(cellSize, shapes, laneEndsMergeLR->getEndingLanes()[1][i], laneEndsMergeLength, laneEndsMergeHeight + 2, i, laneEndsMergeHeight + 1, moveDirection);
    }
}