#pragma once
#include <vector>
#include "Phase.hpp"
#include "Joueur.hpp"
#include "CarteData.hpp"

namespace Game::Core {
    class Partie {
    public:
        Partie();
        void ajouterJoueur(const Joueur& joueur);
        void demarrer();
        void finirTour();
        void terminer();

        std::vector<Joueur>& getJoueurs() { return joueurs; }

    private:
        std::vector<Joueur> joueurs;
        Phase phaseActuelle;
    };
}