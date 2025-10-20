#pragma once
#include <random>

namespace Game::Utils {
    class SimpleRng {
    public:
        static void setSeed(unsigned int seed);
        static int getInt(int min, int max);
        static bool getBool(double probabilite = 0.5);
        
    private:
        static std::mt19937 generateur;
    };
}