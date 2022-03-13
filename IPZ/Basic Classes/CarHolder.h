#pragma once

#include "Vehicle.h"

class CarHolder {
protected:
    Vehicle* vehicle;
public:
    CarHolder();
    ~CarHolder();
    void setVehicle(Vehicle* veh);
    Vehicle* getVehicle();
};