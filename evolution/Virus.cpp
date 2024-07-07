#include "Virus.h"

Virus::Virus(float mortality, float infectionProbability, uint32_t incubationTime, uint32_t infectionDuration) :
	mortality{ mortality }, infectionProbability{ infectionProbability }, incubationTime{ incubationTime }, infectionDuration{ infectionDuration }
{ }

void Virus::setMortality(float mortality)
{
	this->mortality = mortality;
}

void Virus::setInfectionProbability(float infectionProbability)
{
	this->infectionProbability = infectionProbability;
}

void Virus::setIncubationTime(uint32_t incubationTime)
{
	this->incubationTime = incubationTime;
}

void Virus::setInfectionDuration(uint32_t infectionDuration)
{
	this->infectionDuration = infectionDuration;
}

float Virus::getMortality() const
{
	return mortality;
}

float Virus::getInfectionProbability() const
{
	return infectionProbability;
}

uint32_t Virus::getIncubationTime() const
{
	return incubationTime;
}

uint32_t Virus::getInfectionDuration() const
{
	return infectionDuration;
}
