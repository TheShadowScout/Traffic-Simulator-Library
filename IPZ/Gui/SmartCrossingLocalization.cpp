#pragma once

# include "SmartCrossingLocalization.h"

SmartCrossingLocalization::SmartCrossingLocalization(int xPosition, int yPosition, SmartCrossing* smartCrossing) : Localization(xPosition, yPosition), smartCrossing(smartCrossing) { ; }

void SmartCrossingLocalization::prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes) {
    // 2 petle dla car holderów
    // 4 dla inputów/outputów
    // mo¿liwa potrzebna tmp komórka

    sf::RectangleShape crossingRectangle(sf::Vector2f((smartCrossing->getLength() + 2) * cellSize, (smartCrossing->getHeight() + 2) * cellSize));
    crossingRectangle.setPosition((xPosition)*cellSize, (yPosition)*cellSize);
    crossingRectangle.setFillColor(sf::Color(211, 211, 211));
    shapes->push_back(crossingRectangle);
    std::vector<std::vector<CarHolder*>> carHolder = smartCrossing->getCarHolderMatrix();

    std::vector<SmartCrossingInput*> inputN = smartCrossing->getInputsN();
    std::vector<RoadCell*> outputN = smartCrossing->getOutputsN();

    std::vector<SmartCrossingInput*> inputS = smartCrossing->getInputsS();
    std::vector<RoadCell*> outputS = smartCrossing->getOutputsS();

    std::vector<SmartCrossingInput*> inputW = smartCrossing->getInputsW();
    std::vector<RoadCell*> outputW = smartCrossing->getOutputsW();

    std::vector<SmartCrossingInput*> inputE = smartCrossing->getInputsE();
    std::vector<RoadCell*> outputE = smartCrossing->getOutputsE();


    for (int i = 0; i < inputN.size(); i++)
    {
        if (inputN[i] != NULL)
            createCellShapes(cellSize, shapes, inputN[i], smartCrossing->getLength() + 2, smartCrossing->getHeight() + 2, i + 1, 0);

        if (outputN[i] != NULL)
            createCellShapes(cellSize, shapes, outputN[i], smartCrossing->getLength() + 2, smartCrossing->getHeight() + 2, i + 1, 0);

        if (inputW[i] != NULL)
            createCellShapes(cellSize, shapes, inputW[i], smartCrossing->getLength() + 2, smartCrossing->getHeight() + 2, 0, i + 1);

        if (outputW[i] != NULL)
            createCellShapes(cellSize, shapes, outputW[i], smartCrossing->getLength() + 2, smartCrossing->getHeight() + 2, 0, i + 1);

        if (inputE[i] != NULL)
            createCellShapes(cellSize, shapes, inputE[i], smartCrossing->getLength() + 2, smartCrossing->getHeight() + 2, smartCrossing->getLength() + 1, i + 1);

        if (outputE[i] != NULL)
            createCellShapes(cellSize, shapes, outputE[i], smartCrossing->getLength() + 2, smartCrossing->getHeight() + 2, smartCrossing->getLength() + 1, i + 1);

        if (inputS[i] != NULL)
            createCellShapes(cellSize, shapes, inputS[i], smartCrossing->getLength() + 2, smartCrossing->getHeight() + 2, i + 1, smartCrossing->getHeight() + 1);

        if (outputS[i] != NULL)
            createCellShapes(cellSize, shapes, outputS[i], smartCrossing->getLength() + 2, smartCrossing->getHeight() + 2, i + 1, smartCrossing->getHeight() + 1);
    }

    for (int i = 0; i < smartCrossing->getHeight(); i++) {
        for (int j = 0; j < smartCrossing->getLength(); j++) {
            RoadCell* tmp = new RoadCell();
            tmp->setCarHolder(carHolder[i][j]);
            if(carHolder[i][j] != NULL)
                createCellShapes(cellSize, shapes, tmp, smartCrossing->getLength() + 2, smartCrossing->getHeight() + 2, j + 1, i + 1);
            tmp->setCarHolder(NULL);
            delete tmp;
        }
    }
}