#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Simulation.h"


int main() {
    srand(static_cast<unsigned>(time(0)));
    Simulation simulation(100, 0.1, 500);
    simulation.run();
    return 0;
}