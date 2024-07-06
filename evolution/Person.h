#pragma once
#include <SFML/Graphics.hpp>

class Person {
private:
    uint32_t id;
    sf::Vector2f position;
    sf::Color color;
    bool infected;
    bool recovered;
    uint32_t infectionDuration;
    uint32_t timeInfected;
    static const uint32_t size{ 20 };

public:

    Person() { }

    Person(uint32_t id, sf::Vector2f startPos);

    void move() {
        /*position.x += (rand() % 3 - 1) * 10;
        position.y += (rand() % 3 - 1) * 10;*/
    }

    void updateStatus();

    void draw(sf::RenderWindow& window) const;

    bool isInfected() const;

    bool isRecovered() const;

    sf::Vector2f getPosition() const;

    void infect(uint32_t duration);

    static uint32_t getSize();
};

