#pragma once

#include "BasicCrossingLocalization.h"

BasicCrossingLocalization::BasicCrossingLocalization(int xPosition, int yPosition, BasicCrossing* basicCrossing) : Localization(xPosition, yPosition), basicCrossing(basicCrossing) { ; }

void BasicCrossingLocalization::prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes) {
    int crossingLength = basicCrossing->getLength();
    int crossingHeigth = basicCrossing->getHeight();

    sf::RectangleShape crossingRectangle(sf::Vector2f(cellSize * (crossingLength + 2), cellSize * (crossingHeigth + 2)));
    crossingRectangle.setPosition(cellSize * xPosition, cellSize * yPosition);
    crossingRectangle.setFillColor(sf::Color(211, 211, 211));
    shapes->push_back(crossingRectangle);

    std::vector<std::vector<CarHolder*>> carHolder = basicCrossing->getCarHolderMatrix();
    std::vector<BasicCrossingInput*> inputN = basicCrossing->getInputsN();
    std::vector<RoadCell*> outputN = basicCrossing->getOutputsN();

    std::vector<BasicCrossingInput*> inputS = basicCrossing->getInputsS();
    std::vector<RoadCell*> outputS = basicCrossing->getOutputsS();

    std::vector<BasicCrossingInput*> inputW = basicCrossing->getInputsW();
    std::vector<RoadCell*> outputW = basicCrossing->getOutputsW();

    std::vector<BasicCrossingInput*> inputE = basicCrossing->getInputsE();
    std::vector<RoadCell*> outputE = basicCrossing->getOutputsE();

    for (int i = 0; i < crossingLength; i++) {
        if (inputN[i] != NULL)
            createCellShapes(cellSize, shapes, inputN[i], crossingLength + 2, crossingHeigth + 2, i + 1, 0);
        
        if (outputN[i] != NULL)
            createCellShapes(cellSize, shapes, outputN[i], crossingLength + 2, crossingHeigth + 2, i + 1, 0);

        if (inputS[i] != NULL)
            createCellShapes(cellSize, shapes, inputS[i], crossingLength + 2, crossingHeigth + 2, i + 1, crossingHeigth + 1);

        if (outputS[i] != NULL)
            createCellShapes(cellSize, shapes, outputS[i], crossingLength + 2, crossingHeigth + 2, i + 1, crossingHeigth + 1);
    }

    for (int i = 0; i < crossingHeigth; i++) {
        if (inputW[i] != NULL)
            createCellShapes(cellSize, shapes, inputW[i], crossingLength + 2, crossingHeigth + 2, 0, i + 1);

        if (outputW[i] != NULL)
            createCellShapes(cellSize, shapes, outputW[i], crossingLength + 2, crossingHeigth + 2, 0, i + 1);

        if (inputE[i] != NULL)
            createCellShapes(cellSize, shapes, inputE[i], crossingLength + 2, crossingHeigth + 2, crossingLength + 1, i + 1);

        if (outputE[i] != NULL)
            createCellShapes(cellSize, shapes, outputE[i], crossingLength + 2, crossingHeigth + 2, crossingLength + 1, i + 1);
    }

    for (int i = 0; i < crossingHeigth; i++) {
        for (int j = 0; j < crossingLength; j++) {
            RoadCell* tempCell = new RoadCell();
            tempCell->setCarHolder(carHolder[i][j]);
            if (carHolder[i][j] != NULL)
                createCellShapes(cellSize, shapes, tempCell, crossingLength + 2, crossingHeigth + 2, j + 1, i + 1);
            tempCell->setCarHolder(NULL);
            delete tempCell;
        }
    }
}