// Include
#include <SFML/Graphics.hpp>
#include "../Basic Classes/Simulation.h"


class SimulationWindow
{
    struct Button
    {
        sf::Text buttonText;
        sf::FloatRect bounds;
        sf::Font font;
        sf::RectangleShape background;

        Button(std::string txt, std::string fontFile, int size, float whichButton);
    };

public:
    void createSimulationWindow(Simulation s);
};




