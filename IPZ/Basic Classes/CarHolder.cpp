#pragma once

#include "CarHolder.h"

CarHolder::CarHolder() : vehicle(nullptr) {}

CarHolder::~CarHolder() {
    delete vehicle;
}

void CarHolder::setVehicle(Vehicle* veh) {
    vehicle = veh;
}

Vehicle* CarHolder::getVehicle() {
    return vehicle;
}