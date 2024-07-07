#pragma once
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Field.h"



class Simulation {
private:
    Field population;
    sf::RenderWindow window;
    tgui::Gui gui;
    
    void onValueChange(float value);
    
public:
    Simulation(uint32_t numPeople, float infProb, uint32_t infDur);

    void run();

    void handleEvents();

    void initializeUI();
};

