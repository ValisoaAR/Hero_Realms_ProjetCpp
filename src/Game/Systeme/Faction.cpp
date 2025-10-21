#include "../../../include/Game/Systeme/Faction.hpp"

namespace Game::Systeme {

FactionClass::FactionClass(FactionType type) : type(type) {}

const std::string& FactionClass::getNom() const {
    static const std::string noms[] = {
        "Imperial",
        "Guild",
        "Necros",
        "Wild",
        "Neutral"
    };
    return noms[static_cast<int>(type)];
}

} // namespace Game::Systeme