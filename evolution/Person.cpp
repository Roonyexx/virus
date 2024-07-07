#include "Person.h"
#include <iostream>

Person::Person(uint32_t id, sf::Vector2f startPos)
    : id{ id }, position{ startPos }, infected{ false }, recovered{ false }, 
    infectionDuration{ }, timeInfected{ }, color{ 238, 238, 238 }
{

    
}

void Person::updateStatus()
{
    if (infected) 
    {
        timeInfected++;
        if (timeInfected >= infectionDuration) 
        {
            recovered = true;
            infected = false;
            color = sf::Color::Blue;
        }
    }
}

void Person::draw(sf::RenderWindow& window) const
{
    sf::RectangleShape shape{ sf::Vector2f{ size - 1, size - 1 } };
    shape.setPosition(position);
    shape.setFillColor(color);
    window.draw(shape);
}

bool Person::isInfected() const
{
    return infected;
}

bool Person::isRecovered() const
{
    return recovered;
}

sf::Vector2f Person::getPosition() const
{
    return position;
}

void Person::infect(uint32_t duration)
{
    infected = true;
    infectionDuration = duration;
    timeInfected = 0;
    color = sf::Color::Red;
}

uint32_t Person::getSize()
{
    return size;
}
