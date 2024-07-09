#include "Virus.h"
#include <iostream>



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

void updateStatus(Virus& virus, Person& person, Hospital* hospital)
{
	switch (person.status)
	{
	case Status::incubationPeriod:
		if (person.timeInfected < virus.incubationTime)
			person.timeInfected++;
		else if (person.timeInfected == virus.incubationTime)
			{ 
				person.setStatus(Status::Infected); 
				person.timeInfected = 0; 
				if (randomEvent(0.7f)) hospital->addPerson(person);
			}
		break;

	case Status::Infected:
	case Status::inHospital:
		if (person.timeInfected < virus.infectionDuration)
			person.timeInfected++;
		else if (person.timeInfected == virus.infectionDuration)
		{
			if (person.getStatus() == Status::inHospital) hospital->inHospital--;
			if (randomEvent(virus.mortality))
			{
				person.setStatus(Status::Dead);
			}
			else
			{
				person.setStatus(Status::Recovered);
			}
		}
		break;

	case Status::Recovered:
	case Status::Healthy:
	case Status::Dead:
		break;


	default:
		break;
	}
}
