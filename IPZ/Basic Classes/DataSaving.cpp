#pragma once
#include "DataSaving.h"

DataSaving::DataSaving(Map* mapa) {
	this->mapa = mapa;
}

void DataSaving::saveData() {
	mapa->createJSON();
}
