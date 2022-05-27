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
        switch (veh->getSpeed())
        {
            case 0:
                shape.setFillColor(sf::Color(0,0,102));
                break;
            case 1:
                shape.setFillColor(sf::Color(0,0,153));
                break;
            case 2:
                shape.setFillColor(sf::Color(0,0,255));
                break;
            case 3:
                shape.setFillColor(sf::Color(51,51,255));
                break;
            case 4:
                shape.setFillColor(sf::Color(204,0,102));
                break;
            case 5:
                shape.setFillColor(sf::Color(255,0,127));
                break;
            case 6:
                shape.setFillColor(sf::Color(0, 255, 255));
                break;
        }
    }
    else {
        shape.setFillColor(sf::Color(0, 0, 0));
    }
}

void Localization::rotateShape(float cellSize, sf::RectangleShape* shape, int length, int height, int xOffset, int yOffset, char moveDirection) {
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

void Localization::createCellShapes(float cellSize, std::vector<sf::RectangleShape>* shapes, Cell* cell, int parentShapeLength, int parentShapeHeight, int xOffset, int yOffset, char moveDirection) {
    TrafficLights* tempTrafficLights = cell->getTrafficLight();
    if (tempTrafficLights != nullptr) {
        sf::RectangleShape trafficLightsRectangle(sf::Vector2f(cellSize, cellSize));
        rotateShape(cellSize, &trafficLightsRectangle, parentShapeLength, parentShapeHeight, xOffset, yOffset, moveDirection);
        colorTrafficLightsShape(trafficLightsRectangle, tempTrafficLights->getColor());
        shapes->push_back(trafficLightsRectangle);
    }
    Vehicle* tempVeh = cell->getVehicle();
    if (tempVeh != nullptr) {
        sf::RectangleShape vehRectangle(sf::Vector2f(cellSize * 0.8, cellSize * 0.8));
        rotateShape(cellSize, &vehRectangle, parentShapeLength, parentShapeHeight, xOffset, yOffset, moveDirection);
        colorVehShape(vehRectangle, tempVeh);
        shapes->push_back(vehRectangle);
    }
}
