#pragma once

#include "GeneratorLocalization.h"

GeneratorLocalization::GeneratorLocalization(int xPosition, int yPosition, Generator* generator) : Localization(xPosition, yPosition), generator(generator) { ; }

void GeneratorLocalization::draw(float cellSize, sf::RenderWindow* window) {
    sf::RectangleShape generatorRectangle(sf::Vector2f(cellSize, cellSize));
    generatorRectangle.setPosition(xPosition*cellSize, yPosition*cellSize);
    generatorRectangle.setFillColor(sf::Color(211, 211, 211));
    window->draw(generatorRectangle);
    
}