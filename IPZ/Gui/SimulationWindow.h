#include <map>
#include <sstream>

#include <SFML/Graphics.hpp>
#include "../Basic Classes/Simulation.h"
#include "Localization.h"
#include "../Functionality/DensityPlotGenerator.h"

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

public:
    void createSimulationWindow(Simulation* simulation, std::vector<Localization*> localizations, double cellSizeConst = 0.005);
};




