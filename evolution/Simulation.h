#pragma once
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Field.h"
#include "Virus.h"



class Simulation {
private:
    Field population;
    Virus virus;
    sf::RenderWindow window;
    tgui::Gui gui;
    
    void onValueChange(float value);
    
    //(float mortality, float infectionProbability, uint32_t incubationTime, uint32_t infectionDuration)

public:
    Simulation(float mortality, float infProb, uint32_t incTime, uint32_t infDur);

    void run();

    void handleEvents();

    void initializeUI();
};

