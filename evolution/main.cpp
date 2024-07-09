#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Simulation.h"


int main() {
    srand(time(0));

    const float mortality = 0.5f;
    const float infectionProbability = 0.4f;
    const uint32_t incubationTime = 7;
    const uint32_t infectionDuration = 8;
    const uint32_t walkRange = 5;

    Simulation simulation{ mortality, infectionProbability, incubationTime, infectionDuration, walkRange };
    simulation.run();
    return 0;
}