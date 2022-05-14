#pragma once

#include "Vehicle.h"

class CarHolder {
protected:
    Vehicle* vehicle;
public:
    CarHolder();
    ~CarHolder();
    Vehicle* getVehicle();
    void setVehicle(Vehicle* veh);
};