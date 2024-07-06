#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Field.h"



class Simulation {
private:
    Field population;
    sf::RenderWindow window;
    
public:
    Simulation(uint32_t numPeople, float infProb, uint32_t infDur);

    void run();

    void handleEvents();
};

