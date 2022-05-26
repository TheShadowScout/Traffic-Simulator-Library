#pragma once

#include <SFML/Graphics.hpp>

class Localization {
    protected:
	    int xPosition;
        int yPosition;
        
    public:
        Localization(int xPosition, int yPosition);
        virtual void draw(float cellSize, sf::RenderWindow* window) = 0;
    
};

