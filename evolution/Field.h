#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Person.h"

class Field {
private:
    std::vector<std::vector<Person>> people;
    float infectionProbability;
    uint32_t infectionDuration;
    sf::Vector2u numPeople;

public:
    Field(float infProb, uint32_t infDur, sf::Vector2u windowSize);

    void update();

    void draw(sf::RenderWindow& window);

    void checkInfections();
};

