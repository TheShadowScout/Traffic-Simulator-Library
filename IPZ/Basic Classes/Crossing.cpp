#pragma once

#include "Crossing.h"

Crossing::Crossing(int crossingHeight, int crossingLength, int crossingMaxSpeed) : crossingHeight(crossingHeight), crossingMaxSpeed(crossingMaxSpeed), crossingLength(crossingLength) {
    if(crossingHeight < 1)
        throw std::invalid_argument("Crossing height must be higher than 1");
    if(crossingLength < 1)
        throw std::invalid_argument("Crossing length must be higher than 1");
    if(crossingMaxSpeed < 1 || crossingMaxSpeed > 6)
        throw std::invalid_argument("Crossing max speed must be in range between 1 and 6");
    for(int i = 0; i < crossingHeight; i++) {
        std::vector<CarHolder*> carHolderRow;   
        for(int j = 0; j < crossingLength; j++) {
            carHolderRow.push_back(new CarHolder());
        }
        carHolderMatrix.push_back(carHolderRow);
    } 
    for(int i = 0; i < crossingLength; i++) {
        inputN.push_back(nullptr);
        inputS.push_back(nullptr);
        outputN.push_back(nullptr);
        outputS.push_back(nullptr);
    }
    for(int i = 0; i < crossingHeight; i++) {
        inputW.push_back(nullptr);
        inputE.push_back(nullptr);
        outputW.push_back(nullptr);
        outputE.push_back(nullptr);
    }
}

Crossing::~Crossing() {
    for(int i = 0; i < crossingHeight; i++) {
        for(int j = 0; j < crossingLength; j++) {
            delete carHolderMatrix[i][j];
        }
    }
    for(int i = 0; i < crossingLength; i++) {
        delete inputN[i];
        delete inputS[i];
        delete outputN[i];
        delete outputS[i];
    }
    for(int i = 0; i < crossingHeight; i++) {
        delete inputE[i];
        delete inputW[i];
        delete outputE[i];
        delete outputW[i];
    }
}

void Crossing::addNewCrossingLane(char inputSide, int inputIndex, char outputSide, int outputIndex, int laneWeight) {
    try {
        checkParametersAreCorrect(inputSide, inputIndex, outputSide, outputIndex);
    }
    catch (const std::exception &exception) {
        std::cout << exception.what() << std::endl;
        return;
    }
    int row1 = 0;
    int col1 = 0;
    int row2 = 0;
    int col2 = 0;
    switch (inputSide) {
    case 'N':
        row1 = 0;
        col1 = inputIndex;
        if (inputN[inputIndex] == nullptr) {
            inputN[inputIndex] = new CrossingInput(crossingMaxSpeed);
        }
        break;
    case 'E':
        row1 = inputIndex;
        col1 = crossingLength - 1;
        if (inputE[inputIndex] == nullptr) {
            inputE[inputIndex] = new CrossingInput(crossingMaxSpeed);
        }
        break;
    case 'S':
        row1 = crossingHeight - 1;
        col1 = inputIndex;
        if (inputS[inputIndex] == nullptr) {
            inputS[inputIndex] = new CrossingInput(crossingMaxSpeed);
        }
        break;
    case 'W':
        row1 = inputIndex;
        col1 = 0;
        if (inputW[inputIndex] == nullptr) {
            inputW[inputIndex] = new CrossingInput(crossingMaxSpeed);
        }
        break;
    }
    switch (outputSide) {
    case 'N':
        row2 = 0;
        col2 = outputIndex;
        outputN[outputIndex] = new RoadCell(crossingMaxSpeed);
        outputN[outputIndex]->setCarHolder(new CarHolder());
        break;
    case 'E':
        row2 = outputIndex;
        col2 = crossingLength - 1;
        outputE[outputIndex] = new RoadCell(crossingMaxSpeed);
        outputE[outputIndex]->setCarHolder(new CarHolder());
        break;
    case 'S':
        row2 = crossingHeight - 1;
        col2 = outputIndex;
        outputS[outputIndex] = new RoadCell(crossingMaxSpeed);
        outputS[outputIndex]->setCarHolder(new CarHolder());
        break;
    case 'W':
        row2 = outputIndex;
        col2 = 0;
        outputW[outputIndex] = new RoadCell(crossingMaxSpeed);
        outputW[outputIndex]->setCarHolder(new CarHolder());
        break;
    }
    int roadCellsToCreateCnt = int(std::abs(row1 - row2) + 0.5) + int(std::abs(col1 - col2) + 0.5) + 1;
    std::vector<RoadCell*> tempRoadCells;
    for (int i = 0; i < roadCellsToCreateCnt; i++) {
        tempRoadCells.push_back(new RoadCell(crossingMaxSpeed));
    }
    for (int i = 0; i < roadCellsToCreateCnt - 1; i++) {
        tempRoadCells[i]->setNextCell(tempRoadCells[i + 1]);
        tempRoadCells[i + 1]->setPreviousCell(tempRoadCells[i]);
    }
    int tempRoadCellsIndex = 0;
    switch (inputSide) {
    case 'N':
        inputN[inputIndex]->setNextCell(tempRoadCells[0], laneWeight);
        tempRoadCells[0]->setPreviousCell(inputN[inputIndex]);
        for (int i = 0; i < outputIndex; i++) {
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[i][inputIndex]);
            tempRoadCellsIndex++;
        }
        break;
    case 'E':
        inputE[inputIndex]->setNextCell(tempRoadCells[0], laneWeight);
        tempRoadCells[0]->setPreviousCell(inputE[inputIndex]);
        for (int i = crossingLength - 1; i > outputIndex; i--) {
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[inputIndex][i]);
            tempRoadCellsIndex++;
        }
        break;
    case 'S':
        inputS[inputIndex]->setNextCell(tempRoadCells[0], laneWeight);
        tempRoadCells[0]->setPreviousCell(inputS[inputIndex]);
        for (int i = crossingHeight - 1; i > outputIndex; i--) {
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[i][inputIndex]);
            tempRoadCellsIndex++;
        }
        break;
    case 'W':
        inputW[inputIndex]->setNextCell(tempRoadCells[0], laneWeight);
        tempRoadCells[0]->setPreviousCell(inputW[inputIndex]);
        for (int i = 0; i < outputIndex; i++) {
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[inputIndex][i]);
            tempRoadCellsIndex++;
        }
        break;
    }
    if (!((inputSide == 'N' && outputSide == 'S') ||
        (inputSide == 'S' && outputSide == 'N') ||
        (inputSide == 'E' && outputSide == 'W') ||
        (inputSide == 'W' && outputSide == 'E'))) {
        tempRoadCells[tempRoadCellsIndex]->setMaxSpeed(1);
    }
    switch (outputSide) {
    case 'N':
        outputN[outputIndex]->setPreviousCell(tempRoadCells[roadCellsToCreateCnt - 1]);
        tempRoadCells[roadCellsToCreateCnt - 1]->setNextCell(outputN[outputIndex]);
        for (int i = inputIndex; i >= 0; i--) {
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[i][outputIndex]);
            tempRoadCellsIndex++;
        }
        break;
    case 'E':
        outputE[outputIndex]->setPreviousCell(tempRoadCells[roadCellsToCreateCnt - 1]);
        tempRoadCells[roadCellsToCreateCnt - 1]->setNextCell(outputE[outputIndex]);
        for (int i = inputIndex; i <= crossingLength - 1; i++) {
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[outputIndex][i]);
            tempRoadCellsIndex++;
        }
        break;
    case 'S':
        outputS[outputIndex]->setPreviousCell(tempRoadCells[roadCellsToCreateCnt - 1]);
        tempRoadCells[roadCellsToCreateCnt - 1]->setNextCell(outputS[outputIndex]);
        for (int i = inputIndex; i <= crossingHeight - 1; i++) {
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[i][outputIndex]);
            tempRoadCellsIndex++;
        }
        break;
    case 'W':
        outputW[outputIndex]->setPreviousCell(tempRoadCells[roadCellsToCreateCnt - 1]);
        tempRoadCells[roadCellsToCreateCnt - 1]->setNextCell(outputW[outputIndex]);
        for (int i = inputIndex; i >= 0; i--) {
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[outputIndex][i]);
            tempRoadCellsIndex++;
        }
        break;
    }
}

void Crossing::linkRoadLaneToCrossing(Cell* previousCell, char inputSide, int inputIndex) {
    switch(inputSide) {   
        case 'N':
            inputN[inputIndex]->setPreviousCell(previousCell);
            previousCell->setNextCell(inputN[inputIndex]);
            break;
        case 'E':
            inputE[inputIndex]->setPreviousCell(previousCell); 
            previousCell->setNextCell(inputE[inputIndex]);
            break;
        case 'S':
            inputS[inputIndex]->setPreviousCell(previousCell);
            previousCell->setNextCell(inputS[inputIndex]);
            break;
        case 'W':
            inputW[inputIndex]->setPreviousCell(previousCell);
            previousCell->setNextCell(inputW[inputIndex]);
            break;
    }
}

void Crossing::linkRoadLaneToCrossing(char outputSide, int outputIndex, Cell* nextCell) {
    switch(outputSide) {   
        case 'N':
            outputN[outputIndex]->setNextCell(nextCell);
            nextCell->setPreviousCell(outputN[outputIndex]);
            break;
        case 'E':
            outputE[outputIndex]->setNextCell(nextCell);
            nextCell->setPreviousCell(outputE[outputIndex]);
            break;
        case 'S':
            outputS[outputIndex]->setNextCell(nextCell);
            nextCell->setPreviousCell(outputS[outputIndex]);
            break;
        case 'W':
            outputW[outputIndex]->setNextCell(nextCell);
            nextCell->setPreviousCell(outputW[outputIndex]);
            break;
    }
}

std::string Crossing::toString() {
    std::string crossingStr = "";
    for (std::vector<CarHolder*> carHolderRow : carHolderMatrix) {
        for (CarHolder* carHolder : carHolderRow) {
            if (carHolder->getVehicle() == nullptr) {
                crossingStr += ".";
            }
            else {
                crossingStr += std::to_string(carHolder->getVehicle()->getSpeed());
            }
        }
        crossingStr += "\n";
    }
    return crossingStr;
}

void Crossing::checkParametersAreCorrect(char inputSide, int inputIndex, char outputSide, int outputIndex) {
    if (!(inputSide == 'N' || 
        inputSide == 'E' || 
        inputSide == 'S' || 
        inputSide == 'W')) {
        throw std::invalid_argument("inputSide is not one of {N, E, S, W}");
    }
    if (!(outputSide == 'N' ||
        outputSide == 'E' ||
        outputSide == 'S' ||
        outputSide == 'W')) {
        throw std::invalid_argument("outputSide is not one of {N, E, S, W}");
    }
    if (inputSide == outputSide) {
        throw std::invalid_argument("inputSide and outputSide are the same");
    }
    if (((inputSide == 'N' && outputSide == 'S') ||
        (inputSide == 'S' && outputSide == 'N') ||
        (inputSide == 'E' && outputSide == 'W') ||
        (inputSide == 'W' && outputSide == 'E')) && inputIndex != outputIndex) {
        throw std::invalid_argument("inputSide and outputSide on opposite sides have diffrent inputIndex and outputIndex");
    }
    bool inputFlag  = false;
    switch (inputSide) {
    case 'N':
        if (outputN[inputIndex] != nullptr) {
            inputFlag = true;
        }
        break;
    case 'E':
        if (outputE[inputIndex] != nullptr) {
            inputFlag = true;
        }
        break;
    case 'S':
        if (outputS[inputIndex] != nullptr) {
            inputFlag = true;
        }
        break;
    case 'W':
        if (outputW[inputIndex] != nullptr) {
            inputFlag = true;
        }
        break;
    }
    if (inputFlag == true) {
        throw std::invalid_argument("on the inputSide in inputIndex cell is already crossing output");
    }
    bool outputFlag = false;
    switch (outputSide) {
    case 'N':
        if (inputN[outputIndex] != nullptr) {
            outputFlag = true;
        }
        break;
    case 'E':
        if (inputE[outputIndex] != nullptr) {
            outputFlag = true;
        }
        break;
    case 'S':
        if (inputS[outputIndex] != nullptr) {
            outputFlag = true;
        }
        break;
    case 'W':
        if (inputW[outputIndex] != nullptr) {
            outputFlag = true;
        }
        break;
    }
    if (outputFlag == true) {
        throw std::invalid_argument("on the outputSide in outputIndex cell is already crossing input");
    }
}