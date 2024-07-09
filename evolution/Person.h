#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Virus;

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
    static const uint32_t size{ 10 };
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

    uint32_t getTimeInfected() const;
    void setTimeInfected(uint32_t time);

    static uint32_t getSize();

    friend void updateStatus(Virus& virus, Person& person);
};

