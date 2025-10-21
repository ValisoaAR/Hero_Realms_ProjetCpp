#include "../../../include/Game/Systeme/Faction.hpp"

namespace Game::Systeme {

Faction::Faction(FactionType type) : type(type) {}

const std::string& Faction::getNom() const {
    static const std::string noms[] = {
        "Guilde",
        "Impérial",
        "Nécros",
        "Sauvage",
        "Neutre"
    };
    return noms[static_cast<int>(type)];
}

} // namespace Game::Systeme