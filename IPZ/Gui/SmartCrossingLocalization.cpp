#pragma once

# include "SmartCrossingLocalization.h"

SmartCrossingLocalization::SmartCrossingLocalization(int xPosition, int yPosition, SmartCrossing* smartCrossing) : Localization(xPosition, yPosition), smartCrossing(smartCrossing) { ; }

void SmartCrossingLocalization::prepShapes(float cellSize, std::vector<sf::RectangleShape>* shapes) {
    int crossingLength = smartCrossing->getLength();
    int crossingHeigth = smartCrossing->getHeight();

    sf::RectangleShape crossingRectangle(sf::Vector2f(cellSize * (crossingLength + 2), cellSize * (crossingHeigth + 2)));
    crossingRectangle.setPosition(cellSize * xPosition, cellSize * yPosition);
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