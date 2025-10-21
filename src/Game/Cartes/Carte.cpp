#include "Game/Cartes/Carte.hpp"

namespace Game::Cartes {

Carte::Carte(int id, const std::string& nom, int cout, const std::string& type,
             const Systeme::Faction& faction, const std::string& description)
    : id(id), nom(nom), cout(cout), type(type), faction(faction), description(description) {}

} // namespace Game::Cartes

