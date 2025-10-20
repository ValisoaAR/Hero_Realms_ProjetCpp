#include "Game/Utils/SimpleRng.h"

namespace Game::Utils {

std::mt19937 SimpleRng::generateur;

void SimpleRng::setSeed(unsigned int seed) {
    generateur.seed(seed);
}

int SimpleRng::getInt(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(generateur);
}

bool SimpleRng::getBool(double probabilite) {
    std::bernoulli_distribution dist(probabilite);
    return dist(generateur);
}

} // namespace Game::Utils