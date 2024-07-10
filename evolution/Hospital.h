#pragma once
#include "Person.h"


class Hospital
{
private:
	uint32_t capacity;
	uint32_t inHospital = 0;
	const float healChance = 0.1f;

public:
	Hospital(uint32_t capacity);

	Hospital() {}

	void addPerson(Person& person);

	bool isFreeRoom() const;

	void Heal(Person& person, float mortalityChance);

	void setCapacity(uint32_t capacity);

	void resetInHospital();

	friend void updateStatus(Virus& virus, Person& person, Hospital* hospital);
};

