#pragma once
#include <string>

namespace Game::Systeme {
    // Classe simple pour représenter un effet de carte
    // L'application des effets est gérée par GameController
    class Effet {
    public:
        Effet(const std::string& type, int valeur,
              const std::string& condition_type = "aucune",
              const std::string& condition_valeur = "",
              const std::string& activation = "immediate");
              
        const std::string& getType() const { return type; }
        int getValeur() const { return valeur; }
        const std::string& getConditionType() const { return condition_type; }
        const std::string& getConditionValeur() const { return condition_valeur; }
        const std::string& getActivation() const { return activation; }
        
    private:
        std::string type;  // "or", "combat", "pioche", "soin", "sacrifice", "stun", "prepare", "defausse_adversaire", "choix"
        int valeur;
        std::string condition_type;  // "aucune", "ally", "per_champion"
        std::string condition_valeur;  // ex: "IMPERIAL", "GUILD", "NECROS", "WILD", "per_champion"
        std::string activation;  // "immediate", "expend", "ally", "sacrifice"
    };
}