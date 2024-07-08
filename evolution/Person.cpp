#include "Person.h"
#include <iostream>

Person::Person(uint32_t id, sf::Vector2f startPos, uint32_t walkRange, sf::Vector2u fieldSize)
    : id{ id }, position{ startPos }, timeInfected{ }, status{ Status::Healthy }
{ 
    const uint32_t i{ static_cast<uint32_t>(startPos.y / 20) }, j{ static_cast<uint32_t>(position.x / 20) };
    const std::pair<uint32_t, uint32_t>
        lowerBound{ std::max(static_cast<int32_t>(i - walkRange), 0), std::max(static_cast<int32_t>(j - walkRange), 0) },
        upperBound{ std::min(static_cast<int32_t>(i + walkRange), static_cast<int32_t>(fieldSize.y - 1)), std::min(static_cast<int32_t>(j + walkRange), static_cast<int32_t>(fieldSize.x - 1)) };

    lowerPossibleBound = lowerBound;
    upperPossibleBound = upperBound;
}

std::pair<uint32_t, uint32_t> Person::choosePosition() const
{
    uint32_t i = std::rand() % (upperPossibleBound.first - lowerPossibleBound.first + 1) + lowerPossibleBound.first;
    uint32_t j = std::rand() % (upperPossibleBound.second - lowerPossibleBound.second + 1) + lowerPossibleBound.second;

    return { i, j };
}


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
