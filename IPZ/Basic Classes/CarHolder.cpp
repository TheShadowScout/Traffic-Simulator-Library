#pragma once

#include "CarHolder.h"

CarHolder::CarHolder() : vehicle(nullptr) {}

CarHolder::~CarHolder() {
    delete vehicle;
}

Vehicle* CarHolder::getVehicle() {
    return vehicle;
}

void CarHolder::setVehicle(Vehicle* veh) {
    vehicle = veh;
}
