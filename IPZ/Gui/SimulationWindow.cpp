#include "SimulationWindow.h"

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

SimulationWindow::FrequencyButton::FrequencyButton(std::string txt, std::string fontFile, int size, float whichButton, bool isLeft)
{
    font.loadFromFile(fontFile);
    buttonText.setFont(font);
    buttonText.setString(txt);
    buttonText.setCharacterSize(size);
    bounds = buttonText.getLocalBounds();

    buttonText.setPosition(width - 225, int(70 * whichButton));
    buttonText.setFillColor(sf::Color::Black);
    if (isLeft)
    {
        bounds.left = buttonText.getPosition().x;
    }
    else
    {
        bounds.left = buttonText.getPosition().x + 150;
    }
    
    bounds.height = 40;
    bounds.top = buttonText.getPosition().y + 10;
    bounds.width = 50;

    background.setSize(sf::Vector2f(bounds.width, bounds.height));
    background.setPosition(bounds.left, bounds.top);

    buttonText.setPosition((bounds.left + bounds.width / 12), (bounds.top + bounds.height / 50));
}


void SimulationWindow::createSimulationWindow(Simulation* simulation, std::vector<Localization*> localizations, double cellSizeConst)
{
    double refreshRate = 0.5;
    sf::RenderWindow window(sf::VideoMode(width, height), "Simulation", sf::Style::Titlebar | sf::Style::Close);

    sf::Text menuText;
    sf::Text refreshRateText;
    sf::Font font;

    font.loadFromFile("gui/calibri.ttf");

    menuText.setFont(font);
    menuText.setString("Menu");
    menuText.setCharacterSize(40);
    sf::FloatRect bounds = menuText.getLocalBounds();
    menuText.setPosition(width - 2 * bounds.width, 5);
    menuText.setFillColor(sf::Color::Black);

    refreshRateText.setFont(font);
    std::stringstream ss;
    ss << std::setprecision(2) << refreshRate;
    refreshRateText.setString(ss.str());
    refreshRateText.setCharacterSize(30);
    sf::FloatRect rfBounds = refreshRateText.getLocalBounds();
    refreshRateText.setPosition(width - 225 + 85, 70 * 4.15);
    refreshRateText.setFillColor(sf::Color::Black);

    std::string fontName = "gui/calibri.ttf";

    Button start("Start", fontName, 30, 1);
    Button stop("Stop", fontName, 30, 2);
    Button stats("Statistics", fontName, 30, 3);
    // Button saveMap("Save map", fontName, 30, 4);
    // Button loadMap("Load map", fontName, 30, 5);
    // Button clearSimulation("Clear\nsimulation", fontName, 30, 6);
    FrequencyButton lowerFrequency("  +", fontName, 30, 4, false);
    FrequencyButton higherFrequency("  -", fontName, 30, 4, true);
    Button exitSimulation("Quit", fontName, 30, 5);

    sf::RectangleShape menuRect(sf::Vector2f(250, height));
    menuRect.setFillColor(sf::Color(159, 193, 211));
    menuRect.setPosition(width - 250, 0);

    float cellSize = cellSizeConst * height;

    std::vector<sf::RectangleShape> shapes;

    bool simulationStarted = false;
    sf::Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        //std::cout << time << std::endl;
        if (simulationStarted && time >= refreshRate) {
            simulation->transitionFunc();
            for (Localization* localization : localizations) {
                localization->prepShapes(cellSize, &shapes);
            }
            clock.restart();
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                // rozpoczêcie symulacji
                if (start.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                {
                    simulationStarted = true;
                }
                // zatrzymanie symulacji
                if (stop.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                {
                    simulationStarted = false;
                }
                // generowanie statystyk
                if (stats.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                {
                    simulation->saveStatisticsToFile();
                    GenerateDensityPlot();
                }
                // zapisywanie mapy
                //if (saveMap.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                //{
                //    //DataSaving JSON(simulation->getSimulationMap());
                //    //JSON.saveData();
                //}
                //// wczytywanie mapy
                //if (loadMap.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                //{
                //    std::cout << "Wcisnieto wczytywanie mapy\n";
                //}
                //// czyszczenie symulacji
                //if (clearSimulation.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                //{
                //    std::cout << "Czyszczenie symulacji" << std::endl;
                //}
                // wy³¹czanie programu
                if (exitSimulation.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                {
                    window.close();
                }
                // zmniejszanie czêstotliwoœci odœwie¿ania symulacji
                if (lowerFrequency.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                {
                    // Max
                    if (refreshRate > 0.2)
                        refreshRate -= 0.1;
                    ss.str("");
                    ss << std::setprecision(2) << 1.1 - refreshRate;
                    refreshRateText.setString(ss.str());
                }
                // zwiêkszanie czêstotliwoœci odœwie¿ania symulacji
                if (higherFrequency.bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                {
                    // Min
                    if (refreshRate < 0.9)
                        refreshRate += 0.1;
                    ss.str("");
                    ss << std::setprecision(2) << 1.1 - refreshRate;
                    refreshRateText.setString(ss.str());
                }
            }
        }

        for (sf::RectangleShape shape : shapes) {
            window.draw(shape);
        }

        window.draw(menuRect);
        window.draw(menuText);
        window.draw(refreshRateText);

        window.draw(start.background);
        window.draw(stop.background);
        window.draw(stats.background);
       /* window.draw(saveMap.background);
        window.draw(loadMap.background);
        window.draw(clearSimulation.background);*/
        window.draw(lowerFrequency.background);
        window.draw(higherFrequency.background);
        window.draw(exitSimulation.background);

        window.draw(start.buttonText);
        window.draw(stop.buttonText);
        window.draw(stats.buttonText);
       /* window.draw(saveMap.buttonText);
        window.draw(loadMap.buttonText);
        window.draw(clearSimulation.buttonText);*/
        window.draw(lowerFrequency.buttonText);
        window.draw(higherFrequency.buttonText);
        window.draw(exitSimulation.buttonText);

        window.display();

        window.clear(sf::Color(255, 255, 255));
    }
}
    /*
    auto r = dynamic_cast<Map*>(s.getSimulationMap())->getRoads();
    std::vector<sf::RectangleShape> roadRects;
    int offset = height / (2 * r.size());
    int offset2 = (width - 250) / (2 * r.size());
    int pixelSize = width * 0.005;
    int roadHeight = height * 0.020;
    int roadGap = height / (r.size() + 1);
    int prevRoadHeight = 0;

    // drogi
    for (int i = 0; i < r.size(); i++)
    {
        if (r[i]->getDirection() == 'N' || r[i]->getDirection() == 'S')
        {
            sf::RectangleShape shape(sf::Vector2f(roadHeight * r[i]->getHeight(), pixelSize * r[i]->getLength()));
            shape.setPosition(offset2 + roadGap * i + prevRoadHeight, 0);// width * 0.325 - r[i]->getLength() * pixelSize + (int)r[i]->getLength() * pixelSize / 2);
            shape.setFillColor(sf::Color(211, 211, 211));
            roadRects.push_back(shape);
        }
        else
        {
            sf::RectangleShape shape(sf::Vector2f(pixelSize * r[i]->getLength(), roadHeight * r[i]->getHeight()));
            shape.setPosition(width * 0.325 - r[i]->getLength() * pixelSize + (int)r[i]->getLength() * pixelSize / 2, offset + roadGap * i + prevRoadHeight);
            shape.setFillColor(sf::Color(211, 211, 211));
            roadRects.push_back(shape);
        }

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
                        if (r[whichRoad]->getLanes()[whichLane][whichCell]->getVehicle() != nullptr)
                        {
                            sf::RectangleShape shape(sf::Vector2f(carLength, carHeight));
                            shape.setFillColor(sf::Color(255, 0, 0));
                            switch (r[whichRoad]->getDirection())
                            {
                                case 'N':
                                    break;
                                case 'S':
                                    std::cout << whichCell * pixelSize + width * 0.325 - r[whichRoad]->getLength() * pixelSize + (int)r[whichRoad]->getLength() * pixelSize / 2 << std::endl;
                                    shape.setPosition(offset2 + roadGap * whichRoad + whichLane * roadHeight - carHeight + 2 + roadHeight / 2 + prevRoadHeight, whichCell * pixelSize); //+ width * 0.325 - r[whichRoad]->getLength() * pixelSize + (int)r[whichRoad]->getLength() * pixelSize / 2);
                                    break;
                                case 'E':
                                    shape.setPosition(whichCell * pixelSize + width * 0.325 - r[whichRoad]->getLength() * pixelSize + (int)r[whichRoad]->getLength() * pixelSize / 2, offset + roadGap * whichRoad + whichLane * roadHeight - carHeight + 2 + roadHeight / 2 + prevRoadHeight);
                                    break;
                                case 'W':
                                    break;
                            }

                            vehs.push_back(shape);
                        }

                        if (r[whichRoad]->getRoad()[whichLane][whichCell]->getLight() != NULL)
                        {
                            LightColor lightColor = r[whichRoad]->getRoad()[whichLane][whichCell]->getLight()->getColor();

                            if (r[whichRoad]->getDirection() == 'N' || r[whichRoad]->getDirection() == 'S')
                            {
                                sf::RectangleShape shape(sf::Vector2f(lightHeight, lightLength));
                                setLights(shape, lightColor);
                                shape.setPosition(offset2 + roadGap * whichRoad + whichLane * roadHeight - carHeight + height * 0.002 + roadHeight / 2 + prevRoadHeight - height * 0.007, whichCell * pixelSize); //+ width * 0.325 - r[whichRoad]->getLength() * pixelSize + (int)r[whichRoad]->getLength() * pixelSize / 2);
                                lights.push_back(shape);
                            }
                            else
                            {
                                sf::RectangleShape shape(sf::Vector2f(lightLength, lightHeight));
                                setLights(shape, lightColor);
                                shape.setPosition(whichCell * pixelSize + width * 0.325 - r[whichRoad]->getLength() * pixelSize + (int)r[whichRoad]->getLength() * pixelSize / 2, offset + roadGap * whichRoad + whichLane * roadHeight - carHeight + height * 0.002 + roadHeight / 2 + prevRoadHeight - height * 0.007);
                                lights.push_back(shape);
                            }
                        }
                    }
                }
                prevRoadHeight += roadHeight * r[whichRoad]->getHeight();
            }
            clock.restart();
        }
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
*/