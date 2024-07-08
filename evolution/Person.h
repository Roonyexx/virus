#pragma once
#include <SFML/Graphics.hpp>
#include <random>

typedef enum {
    Healthy,
    incubationPeriod,
    Infected,
    Recovered,
    Dead
} Status;

class Person {
private:
    uint32_t id;
    sf::Vector2f position;
    uint32_t timeInfected;
    static const uint32_t size{ 20 };
    std::pair<uint32_t, uint32_t> lowerPossibleBound, upperPossibleBound;
    Status status;

public:

    Person() { }

    Person(uint32_t id, sf::Vector2f startPos, uint32_t walkRange, sf::Vector2u fieldSize);

    std::pair<uint32_t, uint32_t> choosePosition() const;

    void updateStatus();

    void draw(sf::RenderWindow& window) const;

    Status getStatus() const;

    void setStatus(Status status);

    sf::Vector2f getPosition() const;

    void infect();

    static uint32_t getSize();
};

