#include "Virus.h"
#include <iostream>



Virus::Virus(float mortality, float infectionProbability, uint32_t incubationTime, uint32_t infectionDuration) :
	mortality{ mortality }, infectionProbability{ infectionProbability }, incubationTime{ incubationTime }, infectionDuration{ infectionDuration }
{ }

void Virus::infectionSpread(std::vector<std::vector<Person>>& people, Person& person, uint32_t contactsPerDay)
{

	if (person.getStatus() != Status::incubationPeriod && person.getStatus() != Status::Infected || person.getTimeInfected() == 0) return;
	for (int i{ }; i < contactsPerDay; i++)
	{
		const auto positionToInfect{ person.choosePosition() };
		Person& other{ people[positionToInfect.first][positionToInfect.second] };

		if (other.getStatus() == Status::Healthy)
		{
			int divider{ 2 * ((int)person.isMasked() + (int)other.isMasked()) };
			if (divider == 0) divider = 1;

			float finalInfectionProbability{ infectionProbability / divider };

			if (randomEvent(finalInfectionProbability)) other.setStatus(Status::incubationPeriod);
		}
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
		if (person.timeInfected + 1 < virus.incubationTime)
			person.timeInfected++;
		else if (person.timeInfected + 1 >= virus.incubationTime)
			{ 
				person.setStatus(Status::Infected); 
				person.timeInfected = 1; 
				if (randomEvent(0.7f)) hospital->addPerson(person);
			}
		break;

	case Status::Infected:
	case Status::inHospital:
		if (person.timeInfected < virus.infectionDuration)
			person.timeInfected++;
		else if (person.timeInfected >= virus.infectionDuration)
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
