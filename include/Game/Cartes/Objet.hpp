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
              
        void utiliser();
        
        // Note: getEffets() est hérité de Carte
        // Note: effets est hérité de Carte (protected)
    };
}