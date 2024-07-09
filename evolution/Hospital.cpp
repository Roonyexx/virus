#include "Hospital.h"

Hospital::Hospital(uint32_t capacity) : capacity{ capacity }
{ }

void Hospital::addPerson(Person &person)
{
    if (!isFreeRoom()) return;

    inHospital++;
}

bool Hospital::isFreeRoom() const
{
    return (capacity - inHospital) > 0;
}

void Hospital::Heal(Person &person, float mortalityChance)
{
    if (person.getStatus() != Status::inHospital || mortalityChance == 0) return;
    float finalHealChance{ (healChance * (float)sqrt(person.getTimeInfected()) / mortalityChance) / 2 };

    if (randomEvent(finalHealChance))
    {
        person.setStatus(Status::Recovered);
        inHospital--;
    }
}