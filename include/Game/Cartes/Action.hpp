#pragma once
#include "Carte.hpp"
#include "../Systeme/Effet.hpp"
#include <vector>

namespace Game::Cartes {
    class Action : public Carte {
    public:
        Action(int id, const std::string& nom, int cout, 
               const Systeme::Faction& faction, const std::string& description,
               const std::vector<Systeme::Effet>& effets);
        
        // Constructeur simplifié pour CarteData
        Action(const std::string& nom, Systeme::FactionType faction, int cout);
               
        const std::vector<Systeme::Effet>& getEffets() const { return effets; }
        void jouer();
        
    private:
        std::vector<Systeme::Effet> effets;
    };
}