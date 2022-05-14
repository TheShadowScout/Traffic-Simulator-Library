#pragma once

#include "Localization.h"
#include "../Models/LaneEndsMergeR.h"

class LaneEndsMergeLocalizationR : public Localization {
protected:
    LaneEndsMergeR* laneEndsMergeR;
    char moveDirection;

public:
    LaneEndsMergeLocalizationR(int xPosition, int yPosition, LaneEndsMergeR* laneEndsMergeR, char moveDirection = 'E');
    void draw(double cellWidth, double cellHeight);
};