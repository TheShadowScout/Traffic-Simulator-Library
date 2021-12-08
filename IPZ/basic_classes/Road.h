#pragma once
#include <string>
#include <vector>
#include "Cell.h"
using namespace std;

class Road {
protected:
    int IDRoad = 1;
    int maxSpeed;
    int length;
    int height;

    string name;
    vector<vector<Cell*> > road;
    vector<Cell*> head;
    vector<Cell*> tail;

public:
    // maxSpeed - maksymalna pr�dko��, name - nazwa drogi
    Road(int maxSpeed, string name, int length, int height) {
        IDRoad += 1;
        this->maxSpeed = maxSpeed;
        this->name = name;
        this->length = length;
        this->height = height;
    }

    void createRoad() {
        for (int i = 0; i < height; i++) {
            vector<Cell*> newRoad;
            for (int j = 0; j < length; j++) {
                Cell* newCell = new Cell();
                if (j == 0) {
                    head.push_back(newCell);
                    newRoad.push_back(newCell);
                }
                else {
                    newCell->setPreviousCell(newRoad[j - 1]);
                    newRoad[j - 1]->setNextCell(newCell);
                    newRoad.push_back(newCell);
                    if (j == length - 1)
                        tail.push_back(newCell);
                }
            }
            road.push_back(newRoad);
            if (i > 0) {
                for (int j = 0; j < length; j++) {
                    road[i][j]->setLeftCell(road[i - 1][j]);
                    road[i - 1][j]->setRightCell(road[i][j]);
                }
            }
        }
    }

    // maxSpeed - maksymalna pr�dko��
    void setMaxSpeed(int maxSpeed)
    {
        this->maxSpeed = maxSpeed;
    }

    // name - nazwa drogi
    void setName(string name) {
        this->name = name;
    }
    int getMaxSpeed() {
        return maxSpeed;
    }
    int getIDRoad() {
        return IDRoad;
    }
    string getName() {
        return name;
    }
    void createXml;
    }
};