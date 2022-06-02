#pragma once

#include "SmartCrossing.h"

SmartCrossing::SmartCrossing(std::string name, int height, int length, int maxSpeed) : Crossing(name, height, length, maxSpeed) {
    create();
}

SmartCrossing::SmartCrossing(int height, int length, int maxSpeed) : Crossing(height, length, maxSpeed) {
    create();
}

SmartCrossing::~SmartCrossing() {
    for (int i = 0; i < length; i++) {
        delete inputsN[i];
        delete inputsS[i];
    }
    for (int i = 0; i < height; i++) {
        delete inputsE[i];
        delete inputsW[i];
    }
}

void SmartCrossing::create() {
    inputsN = std::vector<SmartCrossingInput*>(length);
    inputsE = std::vector<SmartCrossingInput*>(height);
    inputsS = std::vector<SmartCrossingInput*>(length);
    inputsW = std::vector<SmartCrossingInput*>(height);
}

void SmartCrossing::addNewCrossingLane(char inputSide, int inputIndex, char outputSide, int outputIndex, int laneWeight) {
    try {
        checkParametersAreCorrect(inputSide, inputIndex, outputSide, outputIndex);
    }
    catch (const std::exception& exception) {
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
        if (inputsN[inputIndex] == nullptr) {
            inputsN[inputIndex] = new SmartCrossingInput(maxSpeed);
        }
        break;
    case 'E':
        row1 = inputIndex;
        col1 = length - 1;
        if (inputsE[inputIndex] == nullptr) {
            inputsE[inputIndex] = new SmartCrossingInput(maxSpeed);
        }
        break;
    case 'S':
        row1 = height - 1;
        col1 = inputIndex;
        if (inputsS[inputIndex] == nullptr) {
            inputsS[inputIndex] = new SmartCrossingInput(maxSpeed);
        }
        break;
    case 'W':
        row1 = inputIndex;
        col1 = 0;
        if (inputsW[inputIndex] == nullptr) {
            inputsW[inputIndex] = new SmartCrossingInput(maxSpeed);
        }
        break;
    }
    switch (outputSide) {
    case 'N':
        row2 = 0;
        col2 = outputIndex;
        outputsN[outputIndex] = new RoadCell(maxSpeed);
        outputsN[outputIndex]->setCarHolder(new CarHolder());
        break;
    case 'E':
        row2 = outputIndex;
        col2 = length - 1;
        outputsE[outputIndex] = new RoadCell(maxSpeed);
        outputsE[outputIndex]->setCarHolder(new CarHolder());
        break;
    case 'S':
        row2 = height - 1;
        col2 = outputIndex;
        outputsS[outputIndex] = new RoadCell(maxSpeed);
        outputsS[outputIndex]->setCarHolder(new CarHolder());
        break;
    case 'W':
        row2 = outputIndex;
        col2 = 0;
        outputsW[outputIndex] = new RoadCell(maxSpeed);
        outputsW[outputIndex]->setCarHolder(new CarHolder());
        break;
    }
    int roadCellsToCreateCnt = int(std::abs(row1 - row2) + 0.5) + int(std::abs(col1 - col2) + 0.5) + 1;
    std::vector<RoadCell*> tempRoadCells;
    for (int i = 0; i < roadCellsToCreateCnt; i++) {
        tempRoadCells.push_back(new RoadCell(maxSpeed));
    }
    for (int i = 0; i < roadCellsToCreateCnt - 1; i++) {
        tempRoadCells[i]->setNextCell(tempRoadCells[i + 1]);
        tempRoadCells[i + 1]->setPreviousCell(tempRoadCells[i]);
    }
    lanes.push_back(tempRoadCells);
    switch (inputSide) {
    case 'N':
        inputsN[inputIndex]->addDestinatinCell(tempRoadCells.back());
        break;
    case 'E':
        inputsE[inputIndex]->addDestinatinCell(tempRoadCells.back());
        break;
    case 'S':
        inputsS[inputIndex]->addDestinatinCell(tempRoadCells.back());
        break;
    case 'W':
        inputsW[inputIndex]->addDestinatinCell(tempRoadCells.back());
        break;
    }
    int tempRoadCellsIndex = 0;
    switch (inputSide) {
    case 'N':
        inputsN[inputIndex]->setNextCell(tempRoadCells[0], laneWeight);
        tempRoadCells[0]->setPreviousCell(inputsN[inputIndex]);
        for (int i = 0; i < outputIndex; i++) {
            if (carHolderMatrix[i][inputIndex] == nullptr) {
                carHolderMatrix[i][inputIndex] = new CarHolder();
            }
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[i][inputIndex]);
            tempRoadCellsIndex++;
        }
        break;
    case 'E':
        inputsE[inputIndex]->setNextCell(tempRoadCells[0], laneWeight);
        tempRoadCells[0]->setPreviousCell(inputsE[inputIndex]);
        for (int i = length - 1; i > outputIndex; i--) {
            if (carHolderMatrix[inputIndex][i] == nullptr) {
                carHolderMatrix[inputIndex][i] = new CarHolder();
            }
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[inputIndex][i]);
            tempRoadCellsIndex++;
        }
        break;
    case 'S':
        inputsS[inputIndex]->setNextCell(tempRoadCells[0], laneWeight);
        tempRoadCells[0]->setPreviousCell(inputsS[inputIndex]);
        for (int i = height - 1; i > outputIndex; i--) {
            if (carHolderMatrix[i][inputIndex] == nullptr) {
                carHolderMatrix[i][inputIndex] = new CarHolder();
            }
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[i][inputIndex]);
            tempRoadCellsIndex++;
        }
        break;
    case 'W':
        inputsW[inputIndex]->setNextCell(tempRoadCells[0], laneWeight);
        tempRoadCells[0]->setPreviousCell(inputsW[inputIndex]);
        for (int i = 0; i < outputIndex; i++) {
            if (carHolderMatrix[inputIndex][i] == nullptr) {
                carHolderMatrix[inputIndex][i] = new CarHolder();
            }
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
        outputsN[outputIndex]->setPreviousCell(tempRoadCells[roadCellsToCreateCnt - 1]);
        tempRoadCells[roadCellsToCreateCnt - 1]->setNextCell(outputsN[outputIndex]);
        for (int i = inputIndex; i >= 0; i--) {
            if (carHolderMatrix[i][outputIndex] == nullptr) {
                carHolderMatrix[i][outputIndex] = new CarHolder();
            }
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[i][outputIndex]);
            tempRoadCellsIndex++;
        }
        break;
    case 'E':
        outputsE[outputIndex]->setPreviousCell(tempRoadCells[roadCellsToCreateCnt - 1]);
        tempRoadCells[roadCellsToCreateCnt - 1]->setNextCell(outputsE[outputIndex]);
        for (int i = inputIndex; i <= length - 1; i++) {
            if (carHolderMatrix[outputIndex][i] == nullptr) {
                carHolderMatrix[outputIndex][i] = new CarHolder();
            }
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[outputIndex][i]);
            tempRoadCellsIndex++;
        }
        break;
    case 'S':
        outputsS[outputIndex]->setPreviousCell(tempRoadCells[roadCellsToCreateCnt - 1]);
        tempRoadCells[roadCellsToCreateCnt - 1]->setNextCell(outputsS[outputIndex]);
        for (int i = inputIndex; i <= height - 1; i++) {
            if (carHolderMatrix[i][outputIndex] == nullptr) {
                carHolderMatrix[i][outputIndex] = new CarHolder();
            }
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[i][outputIndex]);
            tempRoadCellsIndex++;
        }
        break;
    case 'W':
        outputsW[outputIndex]->setPreviousCell(tempRoadCells[roadCellsToCreateCnt - 1]);
        tempRoadCells[roadCellsToCreateCnt - 1]->setNextCell(outputsW[outputIndex]);
        for (int i = inputIndex; i >= 0; i--) {
            if (carHolderMatrix[outputIndex][i] == nullptr) {
                carHolderMatrix[outputIndex][i] = new CarHolder();
            }
            tempRoadCells[tempRoadCellsIndex]->setCarHolder(carHolderMatrix[outputIndex][i]);
            tempRoadCellsIndex++;
        }
        break;
    }
}
std::vector<SmartCrossingInput*> SmartCrossing::getInputsN(){
    return inputsN;
}
std::vector<SmartCrossingInput*> SmartCrossing::getInputsW(){
    return inputsW;
}
std::vector<SmartCrossingInput*> SmartCrossing::getInputsS(){
    return inputsS;
}
std::vector<SmartCrossingInput*> SmartCrossing::getInputsE(){
    return inputsE;
}

void SmartCrossing::addTrafficLights(TrafficLights* newLight, char inputSide, int inputIndex) {
    switch (inputSide) {
    case 'N':
        if (inputsN[inputIndex] != nullptr)
        {
            inputsN[inputIndex]->setTrafficLight(newLight);
            trafficLights.push_back(newLight);
        }
        break;
    case 'E':
        if (inputsE[inputIndex] != nullptr)
        {
            inputsE[inputIndex]->setTrafficLight(newLight);
            trafficLights.push_back(newLight);
        }
        break;
    case 'S':
        if (inputsS[inputIndex] != nullptr)
        {
            inputsS[inputIndex]->setTrafficLight(newLight);
            trafficLights.push_back(newLight);
        }
        break;
    case 'W':
        if (inputsW[inputIndex] != nullptr)
        {
            inputsW[inputIndex]->setTrafficLight(newLight);
            trafficLights.push_back(newLight);
        }
        break;
    }
}

void SmartCrossing::linkCellToCrossingInput(Cell* previousCell, char inputSide, int inputIndex) {
    switch (inputSide) {
    case 'N':
        inputsN[inputIndex]->setPreviousCell(previousCell);
        previousCell->setNextCell(inputsN[inputIndex]);
        break;
    case 'E':
        inputsE[inputIndex]->setPreviousCell(previousCell);
        previousCell->setNextCell(inputsE[inputIndex]);
        break;
    case 'S':
        inputsS[inputIndex]->setPreviousCell(previousCell);
        previousCell->setNextCell(inputsS[inputIndex]);
        break;
    case 'W':
        inputsW[inputIndex]->setPreviousCell(previousCell);
        previousCell->setNextCell(inputsW[inputIndex]);
        break;
    }
}

void SmartCrossing::updateCrossing()
{
    for (SmartCrossingInput* input : inputsN) {
        if (input != nullptr) {
            input->drawLane();
        }
    }
    for (SmartCrossingInput* input : inputsE) {
        if (input != nullptr) {
            input->drawLane();
        }
    }
    for (SmartCrossingInput* input : inputsW) {
        if (input != nullptr) {
            input->drawLane();
        }
    }
    for (SmartCrossingInput* input : inputsS) {
        if (input != nullptr) {
            input->drawLane();
        }
    }
}

int SmartCrossing::getPassableCellsCnt() {
    int passableCellsCnt = 0;
    for (std::vector<CarHolder*> carHolderRow : carHolderMatrix) {
        for (CarHolder* carHolder : carHolderRow) {
            if (carHolder != nullptr) {
                passableCellsCnt++;
            }
        }
    }
    for (int i = 0; i < length; i++) {
        if (inputsN[i] != nullptr || outputsN[i] != nullptr) {
            passableCellsCnt++;
        }
        if (inputsS[i] != nullptr || outputsS[i] != nullptr) {
            passableCellsCnt++;
        }
    }
    for (int i = 0; i < height; i++) {
        if (inputsE[i] != nullptr || outputsE[i] != nullptr) {
            passableCellsCnt++;
        }
        if (inputsW[i] != nullptr || outputsW[i] != nullptr) {
            passableCellsCnt++;
        }
    }
    return passableCellsCnt;
}

void SmartCrossing::checkParametersAreCorrect(char inputSide, int inputIndex, char outputSide, int outputIndex) {
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
    bool inputFlag = false;
    switch (inputSide) {
    case 'N':
        if (outputsN[inputIndex] != nullptr) {
            inputFlag = true;
        }
        break;
    case 'E':
        if (outputsE[inputIndex] != nullptr) {
            inputFlag = true;
        }
        break;
    case 'S':
        if (outputsS[inputIndex] != nullptr) {
            inputFlag = true;
        }
        break;
    case 'W':
        if (outputsW[inputIndex] != nullptr) {
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
        if (inputsN[outputIndex] != nullptr) {
            outputFlag = true;
        }
        break;
    case 'E':
        if (inputsE[outputIndex] != nullptr) {
            outputFlag = true;
        }
        break;
    case 'S':
        if (inputsS[outputIndex] != nullptr) {
            outputFlag = true;
        }
        break;
    case 'W':
        if (inputsW[outputIndex] != nullptr) {
            outputFlag = true;
        }
        break;
    }
    if (outputFlag == true) {
        throw std::invalid_argument("on the outputSide in outputIndex cell is already crossing input");
    }
}

std::string SmartCrossing::toString() {
    std::string repStr = "Crossing: ";
    repStr += name;
    repStr += "\n ";
    for (int i = 0; i < length; i++) {
        if (inputsN[i] != nullptr && outputsN[i] == nullptr) {
            Vehicle* tempVeh = inputsN[i]->getVehicle();
            if (tempVeh == nullptr) {
                repStr += ".";
            }
            else {
                repStr += std::to_string(tempVeh->getSpeed());
            }
        }
        else if (inputsN[i] == nullptr && outputsN[i] != nullptr) {
            Vehicle* tempVeh = outputsN[i]->getVehicle();
            if (tempVeh == nullptr) {
                repStr += ".";
            }
            else {
                repStr += std::to_string(tempVeh->getSpeed());
            }
        }
        else {
            repStr += " ";
        }
    }
    repStr += "\n";
    for (int i = 0; i < height; i++) {
        if (inputsW[i] != nullptr && outputsW[i] == nullptr) {
            Vehicle* tempVeh = inputsW[i]->getVehicle();
            if (tempVeh == nullptr) {
                repStr += ".";
            }
            else {
                repStr += std::to_string(tempVeh->getSpeed());
            }
        }
        else if (inputsW[i] == nullptr && outputsW[i] != nullptr) {
            Vehicle* tempVeh = outputsW[i]->getVehicle();
            if (tempVeh == nullptr) {
                repStr += ".";
            }
            else {
                repStr += std::to_string(tempVeh->getSpeed());
            }
        }
        else {
            repStr += " ";
        }
        for (CarHolder* carHolder : carHolderMatrix[i]) {
            if (carHolder != nullptr) {
                Vehicle* tempVeh = carHolder->getVehicle();
                if (tempVeh == nullptr) {
                    repStr += ".";
                }
                else {
                    repStr += std::to_string(tempVeh->getSpeed());
                }
            }
            else {
                repStr += " ";
            }
        }
        if (inputsE[i] != nullptr && outputsE[i] == nullptr) {
            Vehicle* tempVeh = inputsE[i]->getVehicle();
            if (tempVeh == nullptr) {
                repStr += ".";
            }
            else {
                repStr += std::to_string(tempVeh->getSpeed());
            }
        }
        else if (inputsE[i] == nullptr && outputsE[i] != nullptr) {
            Vehicle* tempVeh = outputsE[i]->getVehicle();
            if (tempVeh == nullptr) {
                repStr += ".";
            }
            else {
                repStr += std::to_string(tempVeh->getSpeed());
            }
        }
        else {
            repStr += " ";
        }
        repStr += "\n";
    }
    repStr += " ";
    for (int i = 0; i < length; i++) {
        if (inputsS[i] != nullptr && outputsS[i] == nullptr) {
            Vehicle* tempVeh = inputsS[i]->getVehicle();
            if (tempVeh == nullptr) {
                repStr += ".";
            }
            else {
                repStr += std::to_string(tempVeh->getSpeed());
            }
        }
        else if (inputsS[i] == nullptr && outputsS[i] != nullptr) {
            Vehicle* tempVeh = outputsS[i]->getVehicle();
            if (tempVeh == nullptr) {
                repStr += ".";
            }
            else {
                repStr += std::to_string(tempVeh->getSpeed());
            }
        }
        else {
            repStr += " ";
        }
    }
    repStr += "\n";
    return repStr;
}