#pragma once

#include "Vehicle.h"

#include <iostream>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;


class Cell {
protected:
    Cell* rightCell;
    Cell* leftCell;
    Cell* previousCell;
    Cell* nextCell;
    Vehicle* vehicle;
    int maxSpeed;


public:
    Cell() : rightCell(nullptr), leftCell(nullptr), previousCell(nullptr), nextCell(nullptr), vehicle(nullptr), maxSpeed(0) {}
    Cell(int maxSpeed) : rightCell(nullptr), leftCell(nullptr), previousCell(nullptr), nextCell(nullptr), vehicle(nullptr), maxSpeed(maxSpeed) {}

    void setVehicle(Vehicle* newVehicle) {
        this->vehicle = newVehicle;
    }

    void setRightCell(Cell* newRightCell) {
        this->rightCell = newRightCell;
    }

    void setLeftCell(Cell* newLeftCell) {
        this->leftCell = newLeftCell;
    }

    void setPreviousCell(Cell* newPreviousCell) {
        this->previousCell = newPreviousCell;
    }

    void setNextCell(Cell* newNextCell) {
        this->nextCell = newNextCell;
    }

    void setMaxSpeed(int maxSpeed) {
        this->maxSpeed = maxSpeed;
    }

    Vehicle* getVehicle() {
        return vehicle;
    }

    Cell* getRightCell() {
        return rightCell;
    }

    Cell* getLeftCell() {
        return leftCell;
    }

    Cell* getPreviousCell() {
        return previousCell;
    }

    Cell* getNextCell() {
        return nextCell;
    }

    int getMaxSpeed() {
        return maxSpeed;
    }

    // Czy w statystykach pojedynczej komórki jest konieczność zapisanie informacji o najbliższych do niej komórek, czy też nie?
    // Zauważyłem również, że komórki nie posiadają swojego ID czy też to nie jest potrzebne.
    void createJSON() {
        ptree CellTree;                  
        std::string nameTree = "Cell";
        CellTree.put(nameTree + ".MaxSpeed", getMaxSpeed());

        std::ostringstream oss;
        boost::property_tree::write_json(oss, CellTree);
        std::cout << oss.str();
    }

};