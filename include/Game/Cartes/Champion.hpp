#pragma once
#include "Carte.hpp"
#include "../Systeme/Effet.hpp"
#include <vector>

namespace Game::Cartes {
    class Champion : public Carte {
    public:
        Champion(int id, const std::string& nom, int cout, 
                const Systeme::Faction& faction, const std::string& description,
                int pv, bool garde);
        
        // Constructeur simplifié pour CarteData
        Champion(const std::string& nom, Systeme::FactionType faction, int cout, int pv, bool garde);
                
        int getPv() const { return pv; }
        bool estActif() const { return active; }
        bool estGarde() const { return garde; }
        
        void activer();
        void desactiver();
        void subirDegats(int degats);
        
    private:
        int pv;
        bool active;
        bool garde;
        std::vector<Systeme::Effet> effets;
    };
}