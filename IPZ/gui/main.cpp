// Include
#include "basic_classes/Cell.h"
#include "basic_classes/Destructor.h"
#include "basic_classes/Generator.h"
#include "basic_classes/Map.h"
#include "basic_classes/Road.h"
#include "basic_classes/Teleporter.h"
#include "basic_classes/Vehicle.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    // napis MENU
    sf::Text menuText;
    sf::Font font;

    font.loadFromFile("calibri.ttf"); // TODO: zabezpieczyæ na wypadek b³êdu

    menuText.setFont(font);
    menuText.setString("Menu");
    menuText.setCharacterSize(40);
    sf::FloatRect bounds = menuText.getLocalBounds();
    menuText.setPosition(1000 - 2*bounds.width, 20);
    menuText.setFillColor(sf::Color::Black);

    //PRZYCISK
    sf::Text button1;
    button1.setFont(font);
    button1.setString("Start");
    button1.setCharacterSize(30);
    sf::FloatRect bounds2 = button1.getLocalBounds();
    button1.setPosition(1000 - 2 * bounds2.width, 120);
    button1.setFillColor(sf::Color::Black);
    bounds2.left = button1.getPosition().x;
    bounds2.top = button1.getPosition().y;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bounds2.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            menuText.setString("SUKCES");
        }

        window.clear(sf::Color(255, 255, 255)); // odœwie¿a
        window.draw(menuText);
        window.draw(button1);
        window.display();
    }

    return 0;
}