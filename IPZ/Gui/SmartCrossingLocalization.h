#pragma once

#include "Localization.h"
#include "../Models/SmartCrossing.h"

class SmartCrossingLocalization : public Localization {
    protected:
        SmartCrossing* smartCrossing;

    public:
        SmartCrossingLocalization(int xPosition, int yPosition, SmartCrossing* smartCrossing);
        void draw(float cellWidth, double cellHeight);
};