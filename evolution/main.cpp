#include <SFML/Graphics.hpp>
#include "Simulation.h"


int main() {
    srand(time(0));

    const float mortality = 0.5f;
    const float infectionProbability = 0.4f;
    const uint32_t incubationTime = 7;
    const uint32_t infectionDuration = 8;
    const uint32_t walkRange = 3;
    const uint32_t hospitalCapacity = 0;
    const uint32_t maskPercent = 5;
    const uint32_t contactsPerDay = 5;

    Simulation simulation{ mortality, infectionProbability, incubationTime, infectionDuration, walkRange, hospitalCapacity, maskPercent, contactsPerDay };
    simulation.run();
    return 0;
}