#include "Field.h"


Field::Field(sf::Vector2u windowSize, uint32_t walkRange)
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
            people[i][j] = Person{ id++, sf::Vector2f(j * Person::getSize(), i * Person::getSize()), walkRange, numPeople };
            if(i == numPeople.y / 2 && j == numPeople.x / 2) people[i][j].setStatus(Status::incubationPeriod);
        }
    }
}

void Field::update(Virus& virus)
{
    for (auto& raw : people) 
    {
        for (auto& person : raw)
        {
            if (person.getStatus() == Status::incubationPeriod || person.getStatus() == Status::Infected)
                virus.infectionSpread(people, person);
            updateStatus(virus, person);
        }
    }

}

void Field::draw(sf::RenderWindow& window)
{

    for (auto& raw : people) 
        for (auto& person : raw)
            person.draw(window);
}