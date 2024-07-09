#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Person.h"
#include "Virus.h"

class Field {
private:
    std::vector<std::vector<Person>> people;
    float infectionProbability;
    uint32_t infectionDuration;
    sf::Vector2u numPeople;

public:
    Field(sf::Vector2u windowSize, uint32_t walkRange);

    void update(Virus& virus);

    void draw(sf::RenderWindow& window);

    void setWalkRange(uint32_t walkRange);

};

