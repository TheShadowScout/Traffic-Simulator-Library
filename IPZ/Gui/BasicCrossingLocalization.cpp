#pragma once

#include "BasicCrossingLocalization.h"

BasicCrossingLocalization::BasicCrossingLocalization(int xPosition, int yPosition, BasicCrossing* basicCrossing) : Localization(xPosition, yPosition), basicCrossing(basicCrossing) { ; }

void BasicCrossingLocalization::prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes) {


    //std::vector<sf::RectangleShape> shapesToDraw;
    // int inputNSize = basicCrossing->inputsN.size();
    // int inputESize = basicCrossing->inputsE.size();
    // int inputWSize = basicCrossing->inputsW.size();
    // int inputSSize = basicCrossing->inputsS.size();


    //g³ówny prostok¹t skrzy¿owania

    sf::RectangleShape crossingRectangle(sf::Vector2f((basicCrossing->getLength()+2)*cellSize, (basicCrossing->getHeight()+2)*cellSize));
    crossingRectangle.setPosition((xPosition)*cellSize, (yPosition)*cellSize);
    crossingRectangle.setFillColor(sf::Color(211, 211, 211));
    shapes->push_back(crossingRectangle);

    //inputy

    // sf::RectangleShape inputNorthRectangle(sf::Vector2f(inputNSize*cellSize, cellSize);
    // crossingRectangle.setPosition(xPosition*cellSize+cellSize, yPosition*cellSize);
    // crossingRectangle.setFillColor(sf::Color(211, 211, 211));

    // sf::RectangleShape inputEastRectangle(sf::Vector2f(cellSize, inputESize*cellSize)));
    // crossingRectangle.setPosition(xPosition*cellSize, (yPosition+basicCrossing->height)*cellSize);
    // crossingRectangle.setFillColor(sf::Color(211, 211, 211));

    // sf::RectangleShape inputWestRectangle(sf::Vector2f(cellSize, inputWSize*cellSize));
    // crossingRectangle.setPosition(xPosition*cellSize, (yPosition-1)*cellSize);
    // crossingRectangle.setFillColor(sf::Color(211, 211, 211));

    // sf::RectangleShape inputSouthRectangle(sf::Vector2f(inputSSize*cellSize, cellSize));
    // crossingRectangle.setPosition((xPosition+basicCrossing->length)*cellSize, yPosition*cellSize);
    // crossingRectangle.setFillColor(sf::Color(211, 211, 211));

    // shapesToDraw.push_back(inputNorthRectangle);
    // shapesToDraw.push_back(inputEastRectangle);
    // shapesToDraw.push_back(inputWestRectangle);
    // shapesToDraw.push_back(inputSouthRectangle);

    //dodatkowe kwadraty

    // sf::RectangleShape NWSquare(sf::Vector2f(cellSize, cellSize));
    // crossingRectangle.setPosition((xPosition-1)*cellSize, (yPosition-1)*cellSize);
    // crossingRectangle.setFillColor(sf::Color(211, 211, 211));

    // sf::RectangleShape NESquare(sf::Vector2f(cellSize, cellSize));
    // crossingRectangle.setPosition((xPosition-1)*cellSize, (yPosition+basicCrossing->height)*cellSize);
    // crossingRectangle.setFillColor(sf::Color(211, 211, 211));

    // sf::RectangleShape SWSquare(sf::Vector2f(cellSize, cellSize));
    // crossingRectangle.setPosition((xPosition+basicCrossing->length)*cellSize, (yPosition-1)*cellSize);
    // crossingRectangle.setFillColor(sf::Color(211, 211, 211));

    // sf::RectangleShape SESquare(sf::Vector2f(cellSize, cellSize));
    // crossingRectangle.setPosition((xPosition+basicCrossing->length)*cellSize, (yPosition+basicCrossing->height)*cellSize);
    // crossingRectangle.setFillColor(sf::Color(211, 211, 211));

    // shapesToDraw.push_back(NWSquare);
    // shapesToDraw.push_back(NESquare);
    // shapesToDraw.push_back(SWSquare);
    // shapesToDraw.push_back(SESquare);



    // for ( sf::RectangleShape shape : shapesToDraw)
    //     window->draw(shape);
}