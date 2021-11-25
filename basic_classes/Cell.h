#pragma once

#include "Vehicle.h"
class Cell {
    private:
    Vehicle vehicle;

    Cell* right_cell;
    Cell *left_cell;
    Cell *previous_cell;
    Cell *next_cell;

    
    public:
    Cell() : right_cell(nullptr),left_cell(nullptr),previous_cell(nullptr),next_cell(nullptr){}

    void set_vehicle(Vehicle new_vehicle){
        this->vehicle = new_vehicle;
        }

    void set_right_cell(Cell new_right_cell){
        this->right_cell = &new_right_cell;
    }

    void set_left_cell(Cell new_left_cell){
        this->left_cell = &new_left_cell;
    }

    void set_previous_cell(Cell  new_previous_cell){
        this->previous_cell = &new_previous_cell;
    }

    void set_next_cell(Cell new_next_cell){
        this->next_cell = &new_next_cell;
    }

    


    Vehicle get_vehicle(){
        return vehicle;
        }

    Cell* get_right_cell(){
        return right_cell;
    }

    Cell* get_left_cell(){
        return left_cell;
    }

    Cell* get_previous_cell(){
       return previous_cell;
    }

    Cell* get_next_cell(Cell* new_next_cell){
        return next_cell;
    }

};
//#endif