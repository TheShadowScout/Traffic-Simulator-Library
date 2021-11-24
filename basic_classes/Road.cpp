#include <string>
using namespace std;

class Road{
    int IDRoad;
    int maxSpeed;
    string nameRoad;
    //list<Cell> road;
    //Cell*road;
    //list<Cell> head;
    //Cell*head;
    //list<Cell> tail;
    //Cell*tail;

    public:
        Road(){
            //constructor
            IDRoad=1;  
        }

        void setMaxSpeed(int maxSpeed)
        {
            this->maxSpeed=maxSpeed;
        }
        void setName(string nameRoad){
            this->nameRoad=nameRoad;
        }
        int getMaxSpeed(){
            return maxSpeed;
        }
        int getIDRoad(){
            return IDRoad;
        }
        string getName(){
            return nameRoad;
        }
        void createXml(){
            return;
        }
};