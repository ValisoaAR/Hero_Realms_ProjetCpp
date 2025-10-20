#pragma once
#include <vector>
#include <string>
#include "../Cartes/Carte.hpp"

namespace Game::Zones {
    class ZoneDeCarte {
    public:
        ZoneDeCarte(const std::string& type);
        
        void ajouterCarte(Cartes::Carte* carte, int position = -1);
        Cartes::Carte* retirerCarte(int position);
        void melanger();
        size_t getNbCartes() const;
        
    protected:
        std::string type;  // deck, main, defausse, champions, deck_marche, marche, sacrifice
        std::vector<Cartes::Carte*> cartes;
    };
}