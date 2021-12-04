#pragma once
#include <string>
#include <list>

class Road{
    protected:
    int IDRoad;
    int maxSpeed;
    std::string name;
    std::list<Cell> road;
    std::list<Cell> head;
    std::list<Cell> tail;

    public:
    // maxSpeed - maksymalna pr�dko��, name - nazwa drogi
    Road(int maxSpeed, std::string name){
        IDRoad=1;  
        this->maxSpeed = maxSpeed;
        this->name = name;
    }

    // maxSpeed - maksymalna pr�dko��
    void setMaxSpeed(int maxSpeed)
    {
        this->maxSpeed=maxSpeed;
    }
    
    // name - nazwa drogi
    void setName(std::string name){
        this->name=name;
    }
    int getMaxSpeed(){
        return maxSpeed;
    }
    int getIDRoad(){
        return IDRoad;
    }
    std::string getName(){
        return name;
    }
    void createXml(){
        return;
    }
};