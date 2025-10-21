#pragma once
#include "Carte.hpp"
#include "../Systeme/Effet.hpp"
#include <vector>

namespace Game::Cartes {
    class Objet : public Carte {
    public:
        Objet(int id, const std::string& nom, int cout, 
              const Systeme::Faction& faction, const std::string& description,
              const std::vector<Systeme::Effet>& effets);
        
        // Constructeur simplifié pour CarteData
        Objet(const std::string& nom, Systeme::FactionType faction, int cout);
              
        const std::vector<Systeme::Effet>& getEffets() const { return effets; }
        void utiliser();
        
    private:
        std::vector<Systeme::Effet> effets;
    };
}