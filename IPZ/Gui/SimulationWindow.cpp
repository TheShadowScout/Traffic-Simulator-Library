#include "SimulationWindow.h"
#include "../Functionality/DensityPlotGenerator.h"
#include "../Basic Classes/DataSaving.h"
#include <map>

int width = sf::VideoMode::getDesktopMode().width;
int height = sf::VideoMode::getDesktopMode().height;

SimulationWindow::Button::Button(std::string txt, std::string fontFile, int size, float whichButton)
{
    font.loadFromFile(fontFile);
    buttonText.setFont(font);
    buttonText.setString(txt);
    buttonText.setCharacterSize(size);
    bounds = buttonText.getLocalBounds();

    buttonText.setPosition(width - 225, int(70 * whichButton));
    buttonText.setFillColor(sf::Color::Black);
    bounds.left = buttonText.getPosition().x;
    bounds.top = buttonText.getPosition().y + 10;
    bounds.width = 200;
    bounds.height += 20;

    background.setSize(sf::Vector2f(bounds.width, bounds.height));
    background.setPosition(bounds.left, bounds.top);

    buttonText.setPosition((bounds.left + bounds.width / 12), (bounds.top + bounds.height / 50));
}

void SimulationWindow::createSimulationWindow(Simulation s)
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Simulation", sf::Style::Titlebar | sf::Style::Close);

    sf::Text menuText;
    sf::Font font;

    font.loadFromFile("gui/calibri.ttf");

    menuText.setFont(font);
    menuText.setString("Menu");
    menuText.setCharacterSize(40);
    sf::FloatRect bounds = menuText.getLocalBounds();
    menuText.setPosition(width - 2 * bounds.width, 5);
    menuText.setFillColor(sf::Color::Black);

    std::string fontName = "gui/calibri.ttf";

    Button start("Start", fontName, 30, 1);
    Button stop("Stop", fontName, 30, 2);
    Button stats("Statistics", fontName, 30, 3);
    Button saveMap("Save map", fontName, 30, 4);
    Button loadMap("Load map", fontName, 30, 5);
    Button saveSimulation("Save\nsimulation", fontName, 30, 6);
    Button loadSimulation("Load\nsimulation", fontName, 30, 7.5);
    Button exitSimulation("Quit", fontName, 30, 9);

    sf::RectangleShape menuRect(sf::Vector2f(250, height));
    menuRect.setFillColor(sf::Color(159, 193, 211));
    menuRect.setPosition(width - 250, 0);

    auto r = s.getSimulationMap()->getRoads();
    std::vector<sf::RectangleShape> roadRects;
    int offset = height / (2 * r.size());
    double refreshRate = 0.5;
    int pixelSize = width * 0.005;
    int roadHeight = height * 0.020;
    int roadGap = height / (r.size() + 1);
    int prevRoadHeight = 0;
    for (int i = 0; i < r.size(); i++)
    {
        sf::RectangleShape shape(sf::Vector2f(pixelSize * r[i]->getLength(), roadHeight * r[i]->getHeight()));
        shape.setFillColor(sf::Color(211, 211, 211));
        shape.setPosition(width * 0.325 - r[i]->getLength() * pixelSize + (int)r[i]->getLength() * pixelSize / 2, offset + roadGap * i + prevRoadHeight);
        roadRects.push_back(shape);
        prevRoadHeight += roadHeight * r[i]->getHeight();
    }

    bool simulationStarted = false;
    sf::Clock clock;

    std::vector<sf::RectangleShape> vehs;

    int carHeight = int(height * 0.004);
    int carLength = int(width * 0.004);
    
    std::vector<sf::RectangleShape> lights;
    
    int lightHeight = height * 0.005;
    int lightLength = width * 0.005;

    s.initiateSimulation();
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        if (simulationStarted && time >= refreshRate)
        {
            vehs.clear();
            s.transitionFunc();

            prevRoadHeight = 0;
            for (int whichRoad = 0; whichRoad < r.size(); whichRoad++)
            {

                for (int whichLane = 0; whichLane < r[whichRoad]->getHeight(); whichLane++)
                {
                    for (int whichCell = 0; whichCell < r[whichRoad]->getLength(); whichCell++)
                    {
                        if (r[whichRoad]->getRoad()[whichLane][whichCell]->getVehicle() != nullptr)
                        {
                            sf::RectangleShape shape(sf::Vector2f(carLength, carHeight));
                            shape.setFillColor(sf::Color(255, 0, 0));
                            shape.setPosition(whichCell * pixelSize + width * 0.325 - r[whichRoad]->getLength() * pixelSize + (int)r[whichRoad]->getLength() * pixelSize / 2, offset + roadGap * whichRoad + whichLane * roadHeight - carHeight + 2 + roadHeight / 2 + prevRoadHeight);
                            vehs.push_back(shape);            
                        }

                        if (r[whichRoad]->getRoad()[whichLane][whichCell]->getLight() != NULL)
                        {
                            LightColor lightColor = r[whichRoad]->getRoad()[whichLane][whichCell]->getLight()->getColor();
                            sf::RectangleShape shape(sf::Vector2f(lightLength, lightHeight));
                            switch (lightColor)
                            {
                            case LightColor::red:
                                shape.setFillColor(sf::Color(255, 0, 0));
                                shape.setOutlineColor(sf::Color(0, 0, 0));
                                shape.setOutlineThickness(1);

                                break;
                            case LightColor::green:
                                shape.setFillColor(sf::Color(0, 255, 0));
                                shape.setOutlineColor(sf::Color(0, 0, 0));
                                shape.setOutlineThickness(1);
                                break;
                            case LightColor::yellow:
                            case LightColor::redyellow:
                                shape.setFillColor(sf::Color(255, 255, 0));
                                shape.setOutlineColor(sf::Color(0, 0, 0));
                                shape.setOutlineThickness(1);
                                break;
                            default:
                                break;
                            }
                            
                            shape.setPosition(whichCell * pixelSize + width * 0.325 - r[whichRoad]->getLength() * pixelSize + (int)r[whichRoad]->getLength() * pixelSize / 2, offset + roadGap * whichRoad + whichLane * roadHeight - carHeight + height * 0.002 + roadHeight / 2 + prevRoadHeight - height * 0.007);
                            lights.push_back(shape);
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
            s.saveStatisticsToFile();
            GenerateDensityPlot();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && saveMap.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        {
            DataSaving JSON(s.getSimulationMap());
            JSON.saveData();
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
        for (int i = 0; i < lights.size(); i++)
        {
            window.draw(lights[i]);
        }
        for (int i = 0; i < vehs.size(); i++)
            window.draw(vehs[i]);

        window.display();
    }
}