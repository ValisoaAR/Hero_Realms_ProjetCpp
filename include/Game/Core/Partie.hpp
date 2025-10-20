#pragma once
#include <vector>
#include "Phase.hpp"
#include "Joueur.hpp"

namespace Game::Core {
    class Partie {
    public:
        Partie();
        void demarrer();
        void finirTour();
        void terminer();
        
    private:
        std::vector<Joueur> joueurs;
        Phase phaseActuelle;
    };
}