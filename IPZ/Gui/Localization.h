#pragma once

#include <SFML/Graphics.hpp>

#include "../Basic Classes/Cell.h"

class Localization {
protected:
    int xPosition;
    int yPosition;
        
public:
    Localization(int xPosition, int yPosition);
    virtual void prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes) = 0;
    void colorTrafficLightsShape(sf::RectangleShape& shape, LightColor lightColor);
    void colorVehShape(sf::RectangleShape& shape, Vehicle* veh);
    void rotateShape(float cellSize, sf::RectangleShape* shape, int length, int height, int xOffset, int yOffset, bool center, char moveDirection = 'E');
    void createCellShapes(float cellSize, std::vector<sf::RectangleShape>* shapes, Cell* cell, int parentShapeLength, int parentShapeHeight, int xOffset, int yOffset, char moveDirection = 'E');
};

