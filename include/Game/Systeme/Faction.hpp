#pragma once
#include <string>

namespace Game::Systeme {
    enum class FactionType {
        GUILDE,
        IMPERIAL,
        NECROS,
        SAUVAGE,
        NEUTRE
    };

    class Faction {
    public:
        Faction(FactionType type);
        const std::string& getNom() const;
        FactionType getType() const { return type; }
        
    private:
        FactionType type;
    };
}