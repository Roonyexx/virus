#include "Hospital.h"

Hospital::Hospital(uint32_t capacity) : capacity{ capacity }
{ }

void Hospital::addPerson(Person &person)
{
    if (!isFreeRoom()) return;
    person.setStatus(Status::inHospital);
    inHospital++;
}

bool Hospital::isFreeRoom() const
{
    return (capacity - inHospital) > 0;
}

void Hospital::Heal(Person &person, float mortalityChance)
{
    if (person.getStatus() != Status::inHospital || mortalityChance == 0) return;
    float finalHealChance{ (healChance * (float)sqrt(person.getTimeInfected()) / mortalityChance) / 4 };

    if (randomEvent(finalHealChance))
    {
        person.setStatus(Status::Recovered);
        inHospital--;
    }
}

void Hospital::setCapacity(uint32_t capacity)
{
    this->capacity = capacity;
}

void Hospital::resetInHospital()
{
    inHospital = 0;
}


