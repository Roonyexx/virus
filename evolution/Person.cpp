#include "Person.h"


bool Person::isMasked() const
{
    return mask;
}

Person::Person(uint32_t id, sf::Vector2f startPos, uint32_t walkRange, sf::Vector2u fieldSize, bool mask)
    : id{ id }, position{ startPos }, timeInfected{ }, status{ Status::Healthy }, 
    shape{ sf::Vector2f{ size - 1, size - 1 } }, mask{ mask }
{ 
    this->setWalkRange(walkRange, fieldSize);
    shape.setPosition(position);
}

std::pair<uint32_t, uint32_t> Person::choosePosition() const
{
    uint32_t i = std::rand() % (upperPossibleBound.first - lowerPossibleBound.first + 1) + lowerPossibleBound.first;
    uint32_t j = std::rand() % (upperPossibleBound.second - lowerPossibleBound.second + 1) + lowerPossibleBound.second;

    return { i, j };
}



void Person::draw(sf::RenderWindow& window) 
{
    window.draw(shape);
}

void Person::setStatus(Status status)
{
    this->status = status;
    switch (status)
    {
    case Status::Healthy:
        shape.setFillColor({ 238, 238, 238 });
        break;

    case Status::incubationPeriod:
        shape.setFillColor({ 242, 209, 213 });
        break;

    case Status::Infected:
        shape.setFillColor({ 255, 0, 0 });
        break;

    case Status::inHospital:
        shape.setFillColor({ 30, 199, 85 });
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
}

Status Person::getStatus() const
{
    return status;
}

sf::Vector2f Person::getPosition() const
{
    return position;
}


uint32_t Person::getTimeInfected() const
{
    return timeInfected;
}

void Person::setTimeInfected(uint32_t time)
{
    timeInfected = time;
}

uint32_t Person::getSize()
{
    return size;
}

void Person::setWalkRange(uint32_t walkRange, sf::Vector2u fieldSize)
{
    const uint32_t i{ static_cast<uint32_t>(position.y / size) }, j{ static_cast<uint32_t>(position.x / size) };
    const std::pair<uint32_t, uint32_t>
        lowerBound{ std::max(static_cast<int32_t>(i - walkRange), 0), std::max(static_cast<int32_t>(j - walkRange), 0) },
        upperBound{ std::min(static_cast<int32_t>(i + walkRange), static_cast<int32_t>(fieldSize.y - 1)), std::min(static_cast<int32_t>(j + walkRange), static_cast<int32_t>(fieldSize.x - 1)) };

    lowerPossibleBound = lowerBound;
    upperPossibleBound = upperBound;
}

bool randomEvent(float probability) 
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    return dis(gen) < probability;
}
