#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Virus;
class Hospital;
bool randomEvent(float probability);

typedef enum {
    Healthy,
    incubationPeriod,
    Infected,
    inHospital,
    Recovered,
    Dead
} Status;

class Person {
private:
    uint32_t id;
    sf::Vector2f position;
    uint32_t timeInfected;
    bool mask;
    static const uint32_t size{ 10 };
    std::pair<uint32_t, uint32_t> lowerPossibleBound, upperPossibleBound;
    Status status;
    sf::RectangleShape shape;

public:

    Person() { }

    bool isMasked() const;

    Person(uint32_t id, sf::Vector2f startPos, uint32_t walkRange, sf::Vector2u fieldSize, bool mask = false);

    std::pair<uint32_t, uint32_t> choosePosition() const;

    void draw(sf::RenderWindow& window);

    Status getStatus() const;

    void setStatus(Status status);

    sf::Vector2f getPosition() const;

    void infect();

    uint32_t getTimeInfected() const;
    void setTimeInfected(uint32_t time);

    static uint32_t getSize();

    friend void updateStatus(Virus& virus, Person& person, Hospital* hospital);

    void setWalkRange(uint32_t walkRange, sf::Vector2u fieldSize);
};

