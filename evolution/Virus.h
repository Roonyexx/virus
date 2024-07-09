#pragma once
#include <stdint.h>
#include <random>
#include "Person.h"
#include "Hospital.h"

class Virus
{
private:
	float mortality;
	float infectionProbability;
	uint32_t incubationTime;
	uint32_t infectionDuration;

public:
	Virus(float mortality, float infectionProbability, uint32_t incubationTime, uint32_t infectionDuration);
	~Virus() {}

	void infectionSpread(std::vector<std::vector<Person>>& people, Person& person);

	void setMortality(float mortality);
	float getMortality() const;

	void setInfectionProbability(float infectionProbability);
	float getInfectionProbability() const;

	void setIncubationTime(uint32_t incubationTime);
	uint32_t getIncubationTime() const;

	void setInfectionDuration(uint32_t infectionDuration);
	uint32_t getInfectionDuration() const;
	
	friend void updateStatus(Virus& virus, Person& person);
};

