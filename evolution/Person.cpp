#include "Person.h"
#include <iostream>

Person::Person(uint32_t id, sf::Vector2f startPos, uint32_t walkRange)
    : id{ id }, position{ startPos }, timeInfected{ }, status{ Status::Recovered }, walkRange{ walkRange }
{}

void Person::updateStatus()
{
    switch (status)
    {
    case Status::Healthy:
        
        break;

    case Status::incubationPeriod:
        
        break;

    case Status::Infected:
        
        break;

    case Status::Recovered:
        
        break;

    case Status::Dead:
        
        break;

    default:
        break;
    }
}

void Person::draw(sf::RenderWindow& window) const
{
    sf::RectangleShape shape{ sf::Vector2f{ size - 1, size - 1 } };
    shape.setPosition(position);
    switch (status)
    {
    case Status::Healthy:
        shape.setFillColor({ 238, 238, 238 });
        break;

    case Status::incubationPeriod:
        shape.setFillColor({ 209, 86, 70 });
        break;

    case Status::Infected:
        shape.setFillColor({ 255, 0, 0 });
        break;

    case Status::Recovered:
        shape.setFillColor({ 50, 205, 209 });
        break;

    case Status::Dead:
        shape.setFillColor({ 20, 1, 1 });
        break;
    default:
        break;
    }

    window.draw(shape);
}

void Person::setStatus(Status status)
{

    this->status = status;
}

Status Person::getStatus() const
{
    return status;
}

sf::Vector2f Person::getPosition() const
{
    return position;
}

void Person::infect()
{

}

uint32_t Person::getSize()
{
    return size;
}
