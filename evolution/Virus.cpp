#include "Virus.h"
#include <iostream>
bool Virus::randomEvent(float probability)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1); 

	return dis(gen) < probability;
}

Virus::Virus(float mortality, float infectionProbability, uint32_t incubationTime, uint32_t infectionDuration) :
	mortality{ mortality }, infectionProbability{ infectionProbability }, incubationTime{ incubationTime }, infectionDuration{ infectionDuration }
{ }

void Virus::infectionSpread(std::vector<std::vector<Person>>& people, Person& person)
{

	if (person.getStatus() != Status::incubationPeriod && person.getStatus() != Status::Infected) return;

	const auto positionToInfect{ person.choosePosition() };


	if (people[positionToInfect.first][positionToInfect.second].getStatus() == Status::Healthy)
	{
		if (randomEvent(infectionProbability)) people[positionToInfect.first][positionToInfect.second].setStatus(Status::incubationPeriod);
	}
}

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
