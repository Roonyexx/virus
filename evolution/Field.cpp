#include "Field.h"

Field::Field(sf::Vector2u windowSize, uint32_t walkRange, Hospital* hospital, uint32_t maskPercent) : hospital { hospital }
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
            people[i][j] = Person{ id++, sf::Vector2f(j * Person::getSize(), i * Person::getSize()), walkRange, numPeople, randomEvent(maskPercent / 100.f)};
        }
    }
}

void Field::update(Virus& virus, uint32_t contactsPerDay)
{
    for (auto& raw : people) 
    {
        for (auto& person : raw)
        {
            if (person.getStatus() == Status::incubationPeriod || person.getStatus() == Status::Infected)
                virus.infectionSpread(people, person, contactsPerDay);
            updateStatus(virus, person, hospital);
            if (person.getStatus() == Status::inHospital) hospital->Heal(person, virus.getMortality());
        }
    }
}

void Field::draw(sf::RenderWindow& window)
{

    for (auto& raw : people) 
        for (auto& person : raw)
            person.draw(window);
}

void Field::setWalkRange(uint32_t walkRange)
{
    for (auto& raw : people)
        for (auto& person : raw)
            person.setWalkRange(walkRange, numPeople);
}

void Field::setHospital(Hospital* hospital)
{
    this->hospital = hospital;
}

uint32_t Field::percentToPeople(uint8_t percent)
{
    return round(numPeople.x * numPeople.y * percent / 100);
}

Person* Field::findPerson(sf::Vector2i position)
{
    const uint32_t i{ position.y / Person::getSize() };
    const uint32_t j{ position.x / Person::getSize() };

    if (i >= numPeople.y || j >= numPeople.x) return nullptr;

    return &people[i][j];
}

