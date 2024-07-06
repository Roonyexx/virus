#include "Field.h"


Field::Field(float infProb, uint32_t infDur, sf::Vector2u windowSize)
    : infectionProbability{ infProb }, infectionDuration{ infDur }
{
    const sf::Vector2u numPeople{ windowSize.x / Person::getSize(), windowSize.y / Person::getSize() };
    this->numPeople = numPeople;
    people.resize(numPeople.y);
    uint32_t id{ };

    for (uint32_t i{ }; i < numPeople.y; ++i)
    {
        people[i].resize(numPeople.x);
        for (uint32_t j{ }; j < numPeople.x; ++j)
        {
            people[i][j] = Person(id++, sf::Vector2f(j * Person::getSize(), i * Person::getSize()));
        }
    }
}

void Field::update()
{
    for (auto& raw : people) 
    {
        for (auto& person : raw)
        {
            person.move();
            person.updateStatus();
        }
    }
    checkInfections();
}

void Field::draw(sf::RenderWindow& window)
{

    for (const auto& raw : people) 
        for (const auto& person : raw)
            person.draw(window);
}

void Field::checkInfections()
{
    for (auto& raw : people)
    {
        for (auto& person : raw)
        {
            if (person.isInfected() && !person.isRecovered())
            {
                for (auto& raw : people)
                {
                    for (auto& other : raw)
                    {
                        if (&person != &other && !other.isInfected())
                        {
                            float distance = sqrt(pow(person.getPosition().x - other.getPosition().x, 2) +
                                pow(person.getPosition().y - other.getPosition().y, 2));
                            if (distance < 10 && static_cast<float>(rand()) / static_cast<float>(RAND_MAX) < infectionProbability)
                            {
                                other.infect(infectionDuration);
                            }
                        }
                    }
                }
            }
        }
    }
}
