#include "Simulation.h"
#include <iostream>


Simulation::Simulation(uint32_t numPeople, float infProb, uint32_t infDur)
    : population{ infProb, infDur, sf::Vector2u(1280, 720)}, window { sf::VideoMode{ 1280, 720 }, "Virus" } 
{ }


void Simulation::run()
{
    while (window.isOpen()) 
    {
        handleEvents();
        population.update();
        window.clear(sf::Color::White);
        population.draw(window);
        window.display();
    }
}

void Simulation::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
