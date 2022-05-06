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

    struct FrequencyButton
    {
        sf::Text buttonText;
        sf::FloatRect bounds;
        sf::Font font;
        sf::RectangleShape background;

        FrequencyButton(std::string txt, std::string fontFile, int size, float whichButton, bool isLeft);
    };

    void setLights(sf::RectangleShape& shape, LightColor lightColor);

public:
    void createSimulationWindow(Map* map, double randEventProb);
};




