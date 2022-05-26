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

void RoadLocalization::draw(float cellSize, sf::RenderWindow* window) {
    sf::RectangleShape roadRectangle(sf::Vector2f(cellSize * road->getLength() , cellSize * road->getHeight()));
    roadRectangle.setPosition(sf::Vector2f(cellSize * xPosition, cellSize * yPosition));
    switch (moveDirection) {
    case 'N':
        roadRectangle.setRotation(270.0);
        roadRectangle.move(sf::Vector2f(0, cellSize * road->getLength()));
        break;
    case 'S':
        roadRectangle.setRotation(90.0);
        roadRectangle.move(sf::Vector2f(cellSize * road->getHeight(), 0));
        break;
    case 'W':
        roadRectangle.setRotation(180.0);
        roadRectangle.move(sf::Vector2f(cellSize * road->getLength(), cellSize * road->getHeight()));
        break;
    }
    std::vector<sf::RectangleShape> vehsRectangles;
    roadRectangle.setFillColor(sf::Color(211, 211, 211));
    for (int i = 0; i < road->getHeight(); i++) {
        for (int j = 0; j < road->getLength(); j++) {
            Vehicle* tempVeh = road->getLanes()[i][j]->getVehicle();
            if (tempVeh != nullptr) {
                sf::RectangleShape vehRectangle(sf::Vector2f(cellSize, cellSize));   
                switch (moveDirection) {
                case 'N':
                    roadRectangle.setRotation(270.0);
                    break;
                case 'E':
                    vehRectangle.setOrigin(sf::Vector2f(-cellSize * (xPosition + j), -cellSize * (yPosition + i)));
                    break;
                case 'S':
                    vehRectangle.setOrigin(sf::Vector2f(-cellSize * (yPosition + j), -cellSize * (xPosition + i)));
                    vehRectangle.rotate(90.0);
                    vehRectangle.move(sf::Vector2f(cellSize * (road->getHeight() + 2 * xPosition), 0));
                    break;
                case 'W':
                    roadRectangle.setRotation(180.0);
                    break;
                }
                if (tempVeh->getIsObstacle() != true) {
                    vehRectangle.setFillColor(sf::Color(255, 0, 0));
                }
                else {
                    vehRectangle.setFillColor(sf::Color(0, 0, 0));
                }
                vehsRectangles.push_back(vehRectangle);
            }
        }
    }
    sf::RectangleShape x(sf::Vector2f(100.0, 100.0));
    x.setFillColor(sf::Color(0, 0, 0));
    x.setOrigin(sf::Vector2f(-200.0, -200.0));
    x.rotate(-45.0);
    x.move(sf::Vector2f(10.0, 100.0));
    window->draw(x);
    window->draw(roadRectangle);
    for (auto v : vehsRectangles) {
        window->draw(v);
    }
}