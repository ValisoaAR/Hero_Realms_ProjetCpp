#pragma once
#include <string>

namespace Game::Systeme {

    enum class FactionType {
        IMPERIAL,
        GUILD,
        NECROS,
        WILD,
        NEUTRAL
    };

    using Faction = FactionType;  // Alias pour compatibilité avec le code existant

    class FactionClass {
    public:
        FactionClass(FactionType type);
        const std::string& getNom() const;
        FactionType getType() const { return type; }
        
    private:
        FactionType type;
    };
}