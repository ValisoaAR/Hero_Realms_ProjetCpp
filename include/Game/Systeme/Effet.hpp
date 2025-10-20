#pragma once
#include <string>

namespace Game::Systeme {
    class Effet {
    public:
        Effet(const std::string& type, int valeur,
              const std::string& condition_type = "aucune",
              const std::string& condition_valeur = "",
              const std::string& activation = "toujours");
              
        const std::string& getType() const { return type; }
        int getValeur() const { return valeur; }
        const std::string& getConditionType() const { return condition_type; }
        const std::string& getConditionValeur() const { return condition_valeur; }
        const std::string& getActivation() const { return activation; }
        
        bool peutEtreActive() const;
        void appliquer();
        
    private:
        std::string type;  // "or", "dmg", "pioche", "soin", "sacrifice"
        int valeur;
        std::string condition_type;  // "aucune", "faction", "champion"
        std::string condition_valeur;  // ex: "Imperial", "Necros", id de champion...
        std::string activation;  // "toujours", "sacrifice"
    };
}