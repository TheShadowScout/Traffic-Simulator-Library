#include "gui.h"

Gui::Button(std::string txt, std::string fontFile, int size, float whichButton)
        {
            font.loadFromFile(fontFile);
            buttonText.setFont(font);
            buttonText.setString(txt);
            buttonText.setCharacterSize(size);
            bounds = buttonText.getLocalBounds();

            buttonText.setPosition(775, int(70*whichButton));
            buttonText.setFillColor(sf::Color::Black);
            bounds.left = buttonText.getPosition().x;
            bounds.top = buttonText.getPosition().y + 10;
            bounds.width = 200;
            bounds.height += 20;

            background.setSize(sf::Vector2f(bounds.width, bounds.height));
            background.setPosition(bounds.left, bounds.top);

            buttonText.setPosition((bounds.left + bounds.width/12), (bounds.top + bounds.height/50));
        }

void Gui::createSimulation(Simulation s)
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Simulation");

    sf::Text menuText;
    sf::Font font;

    font.loadFromFile("gui/calibri.ttf"); // TODO: zabezpieczy� na wypadek b��du

    menuText.setFont(font);
    menuText.setString("Menu");
    menuText.setCharacterSize(40);
    sf::FloatRect bounds = menuText.getLocalBounds();
    menuText.setPosition(1000 - int(1.9 * bounds.width), 5);
    menuText.setFillColor(sf::Color::Black);

    Button start("Start", "gui/calibri.ttf", 30, 1);
    Button stop("Stop", "gui/calibri.ttf", 30, 2);
    Button stats("Statistics", "gui/calibri.ttf", 30, 3);
    Button saveMap("Save map", "gui/calibri.ttf", 30, 4);
    Button loadMap("Load map", "gui/calibri.ttf", 30, 5);
    Button saveSimulation("Save\nsimulation", "gui/calibri.ttf", 30, 6);
    Button loadSimulation("Load\nsimulation", "gui/calibri.ttf", 30, 7.5);
    Button exitSimulation("Quit", "gui/calibri.ttf", 30, 9);

    sf::RectangleShape menuRect(sf::Vector2f(250, 1000));
    menuRect.setFillColor(sf::Color(159, 193, 211));
    menuRect.setPosition(750, 0);

    auto r = s.getMap()->getRoads();
    std::vector<sf::RectangleShape> roadRects;
    int offset = 1000 / (2*r.size());
    double refreshRate = 0.1; // w sekundach
    int pixelSize = 5; // szeroko�� kom�rki
    int roadHeight = 20;
    int roadGap = 1000 / (r.size() + 1);
    int prevRoadHeight = 0;
    for (int i = 0; i < r.size(); i++)
    {
        sf::RectangleShape shape(sf::Vector2f(pixelSize * r[i]->getLength(), roadHeight * r[i]->getHeight()));
        shape.setFillColor(sf::Color(211, 211, 211));
        shape.setPosition(325-r[i]->getLength()* pixelSize + (int)r[i]->getLength() * pixelSize/2, offset + roadGap *i+ prevRoadHeight);
        roadRects.push_back(shape);
        prevRoadHeight += roadHeight * r[i]->getHeight();
    }

    bool simulationStarted = false;
    sf::Clock clock;

    std::vector<sf::RectangleShape> vehs;

    int carHeight = 4;
    int carLength = 4;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        if (simulationStarted && time >= refreshRate)
        {
            vehs.clear();
            s.transitionFunc();
            // std::cout << s.tempToString() << std::endl;

            prevRoadHeight = 0;
            for (int whichRoad = 0; whichRoad < r.size(); whichRoad++)
            {
                
                for (int whichLane = 0; whichLane < r[whichRoad]->getHeight(); whichLane++)
                {
                    for (int whichCell = 0; whichCell < r[whichRoad]->getLength(); whichCell++)
                    {
                        if (r[whichRoad]->road[whichLane][whichCell]->getVehicle() != nullptr)
                        {
                            sf::RectangleShape shape(sf::Vector2f(carLength, carHeight));
                            shape.setFillColor(sf::Color(255, 0, 0));
                            shape.setPosition(whichCell * pixelSize + 325 - r[whichRoad]->getLength() * pixelSize + (int)r[whichRoad]->getLength() * pixelSize / 2,offset + roadGap*whichRoad+whichLane*roadHeight-carHeight+2+roadHeight/2+ prevRoadHeight);
                            vehs.push_back(shape);
                        }
                    }
                }
                prevRoadHeight += roadHeight * r[whichRoad]->getHeight();
            }
            clock.restart();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && start.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            simulationStarted = true;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stop.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            simulationStarted = false;
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
            // ostrze�enie  w wypadku wyj�cia w trakcie symulacji
            window.close();
        }

        window.clear(sf::Color(255, 255, 255));

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

        for (int i = 0; i < r.size(); i++)
        {
            window.draw(roadRects[i]);
        }
       
        for (int i = 0; i < vehs.size(); i++)
            window.draw(vehs[i]);
        
        window.display();
    }
}
