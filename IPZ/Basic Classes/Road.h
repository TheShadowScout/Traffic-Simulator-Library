#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Cell.h"

class Road {
public:
    int static IDcnt;

protected:
    int ID;
    int maxSpeed;
    int length;
    int height;

    std::string name;
    std::vector<std::vector<Cell*>> road;

public:
    std::vector<Cell*> head;
    std::vector<Cell*> tail;

public:
    Road(std::string name, int length, int height, int maxSpeed) : name(name), length(length), height(height), maxSpeed(maxSpeed) {
        ID = IDcnt++;
        createRoad();
    }

    Road(int length, int height, int maxSpeed) : length(length), height(height), maxSpeed(maxSpeed) {
        ID = IDcnt++;
        name = std::to_string(ID);
        createRoad();
    }

    void createRoad() {
        for (int i = 0; i < height; i++) {
            std::vector<Cell*> newRoadLane;
            for (int j = 0; j < length; j++) {
                Cell* newCell = new Cell(maxSpeed);
                if (j == 0) {
                    head.push_back(newCell);
                    newRoadLane.push_back(newCell);
                }
                else {
                    newCell->setPreviousCell(newRoadLane[j - 1]);
                    newRoadLane[j - 1]->setNextCell(newCell);
                    newRoadLane.push_back(newCell);
                    if (j == length - 1)
                        tail.push_back(newCell);
                }
            }
            road.push_back(newRoadLane);
            if (i > 0) {
                for (int j = 0; j < length; j++) {
                    road[i][j]->setLeftCell(road[i - 1][j]);
                    road[i - 1][j]->setRightCell(road[i][j]);
                }
            }
        }
    }

    void setMaxSpeed(int maxSpeed) {
        this->maxSpeed = maxSpeed;
    }

    void setName(std::string name) {
        this->name = name;
    }

    int getMaxSpeed() {
        return maxSpeed;
    }

    int getID() {
        return ID;
    }

    std::string getName() {
        return name;
    }

    void createXml() {
    }

    std::string tempToString() {
        std::string roadStr = "";
        for (std::vector<Cell*> roadLane : road) {
            for (Cell* laneCell : roadLane) {
                if (laneCell->getVehicle() == nullptr) {
                    roadStr += ".";
                }
                else {
                    if (laneCell->getVehicle()->checkIsObstacle() == true) {
                        roadStr += "!";
                    }
                    else {
                        roadStr += std::to_string(laneCell->getVehicle()->getSpeed());
                    }           
                }
            }
            roadStr += "\n";
        }
        return roadStr;
    }
};