#pragma once
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>
#include "Field.h"
#include "Virus.h"



class Simulation {
private:
    Field population;
    Virus virus;
    Hospital hospital;
    uint32_t walkRange;
    uint32_t maskPercent;
    uint32_t contactsPerDay;
    bool paused = true;
    sf::RenderWindow window;
    tgui::Gui gui;
    
    void step();
    void reset();
public:
    Simulation(float mortality, float infProb, uint32_t incTime, uint32_t infDur, uint32_t walkRange, uint32_t hospitalCapacity, uint32_t maskPercent, uint32_t contactsPerDay); 

    void run();

    void handleEvents();

    void initializeUI();
};

