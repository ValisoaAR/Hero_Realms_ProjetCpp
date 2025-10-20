#pragma once
#include <string>
#include "../Systeme/Faction.hpp"
#include "../Systeme/Capacite.hpp"

namespace Game::Cartes {
    class Carte {
    public:
        Carte(int id, const std::string& nom, int cout, const std::string& type, 
              const Systeme::Faction& faction, const std::string& description);
              
        virtual ~Carte() = default;
        
        int getId() const { return id; }
        const std::string& getNom() const { return nom; }
        int getCout() const { return cout; }
        const std::string& getType() const { return type; }
        const Systeme::Faction& getFaction() const { return faction; }
        const std::string& getDescription() const { return description; }
        
    protected:
        int id;
        std::string nom;
        int cout;
        std::string type;
        Systeme::Faction faction;
        std::string description;
    };
}