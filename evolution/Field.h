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
    Hospital* hospital;
    sf::Vector2u numPeople;

public:
    Field(sf::Vector2u windowSize, uint32_t walkRange, Hospital* hospital);

    void update(Virus& virus);

    void draw(sf::RenderWindow& window);

    void setWalkRange(uint32_t walkRange);

    void setHospital(Hospital* hospital);

    uint32_t percentToPeople(uint8_t percent);

    Person* findPerson(sf::Vector2i position);

};

