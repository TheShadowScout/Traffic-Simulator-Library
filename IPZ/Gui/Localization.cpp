#pragma once

#include "Localization.h"

Localization::Localization(int xPosition, int yPosition) : xPosition(xPosition), yPosition(yPosition) { ; }

void Localization::colorTrafficLightsShape(sf::RectangleShape& shape, LightColor lightColor) {
    switch (lightColor) {
    case LightColor::red:
        shape.setFillColor(sf::Color(255, 0, 0));
        //shape.setOutlineColor(sf::Color(0, 0, 0));
        //shape.setOutlineThickness(1);
        break;
    case LightColor::green:
        shape.setFillColor(sf::Color(0, 255, 0));
        //shape.setOutlineColor(sf::Color(0, 0, 0));
        //shape.setOutlineThickness(1);
        break;
    case LightColor::yellow:
    case LightColor::redyellow:
        shape.setFillColor(sf::Color(255, 255, 0));
        //shape.setOutlineColor(sf::Color(0, 0, 0));
        //shape.setOutlineThickness(1);
        break;
    }
}

void Localization::colorVehShape(sf::RectangleShape& shape, Vehicle* veh) {
    if (veh->getIsObstacle() != true) {
        shape.setFillColor(sf::Color(255, 0, 0));
    }
    else {
        shape.setFillColor(sf::Color(0, 0, 0));
    }
}

void Localization::rotateShape(float cellSize, sf::RectangleShape* shape, int length, int height, char moveDirection, int xOffset, int yOffset) {
    switch (moveDirection) {
    case 'N':
        shape->setOrigin(-cellSize * (yPosition + xOffset), -cellSize * (xPosition + yOffset));
        shape->setRotation(270.0);
        shape->move(0, cellSize * (length + 2 * yPosition));
        break;
    case 'E':
        shape->setOrigin(-cellSize * (xPosition + xOffset), -cellSize * (yPosition + yOffset));
        break;
    case 'S':
        shape->setOrigin(-cellSize * (yPosition + xOffset), -cellSize * (xPosition + yOffset));
        shape->rotate(90.0);
        shape->move(cellSize * (height + 2 * xPosition), 0);
        break;
    case 'W':
        shape->setOrigin(-cellSize * (xPosition + xOffset), -cellSize * (yPosition + yOffset));
        shape->rotate(180.0);
        shape->move(cellSize * (length + 2 * xPosition), cellSize * (height + 2 * yPosition));
        break;
    }
}

void Localization::createCellShapes(float cellSize, std::vector<sf::RectangleShape>* shapes, Cell* cell, int length, int height, char moveDirection, int xOffset, int yOffset) {
    TrafficLights* tempTrafficLights = cell->getTrafficLight();
    if (tempTrafficLights != nullptr) {
        sf::RectangleShape trafficLightsRectangle(sf::Vector2f(cellSize, cellSize));
        rotateShape(cellSize, &trafficLightsRectangle, length, height, moveDirection, xOffset, yOffset);
        colorTrafficLightsShape(trafficLightsRectangle, tempTrafficLights->getColor());
        shapes->push_back(trafficLightsRectangle);
    }
    Vehicle* tempVeh = cell->getVehicle();
    if (tempVeh != nullptr) {
        sf::RectangleShape vehRectangle(sf::Vector2f(cellSize * 0.8, cellSize * 0.8));
        rotateShape(cellSize, &vehRectangle, length, height, moveDirection, xOffset, yOffset);
        colorVehShape(vehRectangle, tempVeh);
        shapes->push_back(vehRectangle);
    }
}
