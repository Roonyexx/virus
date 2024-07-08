#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Simulation.h"


int main() {
    srand(time(0));

    const float mortality = 0.1f;
    const float infectionProbability = 0.5f;
    const uint32_t incubationTime = 5;
    const uint32_t infectionDuration = 5;
    const uint32_t walkRange = 10;

    Simulation simulation{ mortality, infectionProbability, incubationTime, infectionDuration, walkRange };
    simulation.run();
    return 0;
}