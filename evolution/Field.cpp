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
            people[i][j] = Person(id++, sf::Vector2f(j * Person::getSize(), i * Person::getSize()), walkRange);
        }
    }
}

void Field::update()
{
    //for (auto& raw : people) 
    //{
    //    for (auto& person : raw)
    //    {
    //        person.move();
    //        person.updateStatus();
    //    }
    //}


}

void Field::draw(sf::RenderWindow& window)
{

    for (const auto& raw : people) 
        for (const auto& person : raw)
            person.draw(window);
}


