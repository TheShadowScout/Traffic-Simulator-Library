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
    void rotateShape(float cellSize, sf::RectangleShape* shape, int length, int height, char moveDirection = 'E', int xOffset = 0, int yOffset = 0);
    void createCellShapes(float cellSize, std::vector<sf::RectangleShape>* shapes, Cell* cell, int length = 0, int height = 0, char moveDirection = 'E', int xOffset = 0, int yOffset = 0);
};

