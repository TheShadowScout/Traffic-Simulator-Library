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

void RoadLocalization::prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes) {
    sf::RectangleShape roadRectangle(sf::Vector2f(cellSize * road->getLength() , cellSize * road->getHeight()));
    rotateShape(cellSize, &roadRectangle, road->getLength(), road->getHeight(), moveDirection);
    roadRectangle.setFillColor(sf::Color(211, 211, 211));
    shapes->push_back(roadRectangle);
    for (int i = 0; i < road->getHeight(); i++) {
        for (int j = 0; j < road->getLength(); j++) {
            createCellShapes(cellSize, shapes, road->getLanes()[i][j], road->getLength(), road->getHeight(), moveDirection, j, i);
        }
    }
}