// Include
#include "basic_classes/Cell.h"
#include "basic_classes/Destructor.h"
#include "basic_classes/Generator.h"
#include "basic_classes/Map.h"
#include "basic_classes/Road.h"
#include "basic_classes/Teleporter.h"
#include "basic_classes/Vehicle.h"
#include <SFML/Graphics.hpp>

// TO DO
// zapobiegaæ wielokrotnemu wywo³aniu raz naciœniêtego przycisku
// uniwersalnoœæ wymiarów okienka
// polskie znaki

struct Button
{
    sf::Text buttonText;
    sf::FloatRect bounds;
    sf::Font font;
    sf::RectangleShape background; // w konstruktorze ustawiam size

    Button(std::string txt, std::string fontFile, int size, float whichButton)
    {
        font.loadFromFile(fontFile);
        buttonText.setFont(font);
        buttonText.setString(txt);
        buttonText.setCharacterSize(size);
        bounds = buttonText.getLocalBounds();

        buttonText.setPosition(775, int(70*whichButton));
        buttonText.setFillColor(sf::Color::Black);
        bounds.left = buttonText.getPosition().x;
        bounds.top = buttonText.getPosition().y + 10; // TO DO: wymyœliæ coœ lepszego ni¿ +10
        bounds.width = 200;
        bounds.height += 20;

        background.setSize(sf::Vector2f(bounds.width, bounds.height));
        background.setPosition(bounds.left, bounds.top);

        // buttonText.setPosition(int(bounds.width/2),int(bounds.height/2));

        buttonText.setPosition((bounds.left + bounds.width/12), (bounds.top + bounds.height/50));
        //buttonText.setOrigin((bounds.left + bounds.width / 2), (bounds.top + bounds.height / 2));
        //buttonText.setPosition(sf::Vector2f(0,0));


    }

    // TO DO
    // funkcja drawButton()
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Simulation");

    // napis MENU
    sf::Text menuText;
    sf::Font font;

    font.loadFromFile("calibri.ttf"); // TODO: zabezpieczyæ na wypadek b³êdu

    menuText.setFont(font);
    menuText.setString("Menu");
    menuText.setCharacterSize(40);
    sf::FloatRect bounds = menuText.getLocalBounds();
    menuText.setPosition(1000 - int(1.9*bounds.width), 5);
    menuText.setFillColor(sf::Color::Black);

    Button start("Start", "calibri.ttf", 30, 1);
    Button stop("Stop", "calibri.ttf", 30, 2);
    Button stats("Statystyki", "calibri.ttf", 30, 3);
    Button saveMap("Zapisz map\234", "calibri.ttf", 30, 4);
    Button loadMap("Wczytaj mapê", "calibri.ttf", 30, 5);
    Button saveSimulation("Zapisz stan\nsymulacji", "calibri.ttf", 30, 6);
    Button loadSimulation("Wczytaj stan\nsymulacji", "calibri.ttf", 30, 7.5);
    Button exitSimulation("Wyjœcie", "calibri.ttf", 30, 9);

    sf::RectangleShape menuRect(sf::Vector2f(250, 1000));
    menuRect.setFillColor(sf::Color(159, 193, 211));
    menuRect.setPosition(750, 0);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && start.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            std::cout << "Wcisnieto start\n";
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stop.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            std::cout << "Wcisnieto stop\n";
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stats.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            std::cout << "Wcisnieto statystyki\n";
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && saveMap.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            std::cout << "Wcisnieto zapis mapy\n";
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && loadMap.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            std::cout << "Wcisnieto wczytywanie mapy\n";
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && saveSimulation.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            std::cout << "Wcisnieto zapis symulacji\n";
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && loadSimulation.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            std::cout << "Wcisnieto wczytywanie symulacji\n";
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && exitSimulation.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            // ostrze¿enie  w wypadku wyjœcia w trakcie symulacji
            // jakiœ zapis symulacji czy coœ
            window.close();
        }

        window.clear(sf::Color(255, 255, 255)); // odœwie¿a

        window.draw(menuRect);
        window.draw(menuText);

        window.draw(start.background);
        window.draw(stop.background);
        window.draw(stats.background);
        window.draw(saveMap.background);
        window.draw(saveSimulation.background);
        window.draw(loadMap.background);
        window.draw(loadSimulation.background);
        window.draw(exitSimulation.background);

        window.draw(start.buttonText);
        window.draw(stop.buttonText);
        window.draw(stats.buttonText);
        window.draw(saveMap.buttonText);
        window.draw(saveSimulation.buttonText);
        window.draw(loadMap.buttonText);
        window.draw(loadSimulation.buttonText);
        window.draw(exitSimulation.buttonText);

        window.display();
    }

    return 0;
}