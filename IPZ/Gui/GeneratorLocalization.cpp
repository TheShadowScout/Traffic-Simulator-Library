#pragma once

#include "GeneratorLocalization.h"

GeneratorLocalization::GeneratorLocalization(int xPosition, int yPosition, Generator* generator) : Localization(xPosition, yPosition), generator(generator) { ; }

void GeneratorLocalization::prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes) {
    sf::RectangleShape generatorRectangle(sf::Vector2f(cellSize, cellSize));
    generatorRectangle.setPosition(cellSize * xPosition, cellSize * yPosition);
    generatorRectangle.setFillColor(sf::Color(211, 211, 211));
    shapes->push_back(generatorRectangle);
    createCellShapes(cellSize, shapes, generator, 1, 1, 0, 0);
}