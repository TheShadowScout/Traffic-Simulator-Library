#pragma once


class Localization {
    protected:
	    int xPosition;
        int yPosition;
        
    public:
        Localization(int xPosition, int yPosition);
        virtual void draw(double cellWidth, double cellHeight) = 0;
    
};

