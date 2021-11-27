#pragma once
#include <string>
#include <list>

using namespace std;

class Road{
    protected:
    int IDRoad;
    int maxSpeed;
    string name;
    list<Cell> road;
    list<Cell> head;
    list<Cell> tail;

    public:
    // maxSpeed - maksymalna prêdkoœæ, name - nazwa drogi
    Road(int maxSpeed, string name){
        IDRoad=1;  
        this->maxSpeed = maxSpeed;
        this->name = name;
    }

    // maxSpeed - maksymalna prêdkoœæ
    void setMaxSpeed(int maxSpeed)
    {
        this->maxSpeed=maxSpeed;
    }
    
    // name - nazwa drogi
    void setName(string name){
        this->name=name;
    }
    int getMaxSpeed(){
        return maxSpeed;
    }
    int getIDRoad(){
        return IDRoad;
    }
    string getName(){
        return name;
    }
    void createXml(){
        return;
    }
};