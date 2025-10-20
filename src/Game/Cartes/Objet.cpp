#include "Game/Cartes/Objet.hpp"

namespace Game::Cartes {

Objet::Objet(int id, const std::string& nom, int cout,
             const Systeme::Faction& faction, const std::string& description,
             const std::vector<Systeme::Effet>& effets)
    : Carte(id, nom, cout, "objet", faction, description), effets(effets) {}

void Objet::utiliser() {
    // Appliquer les effets de l'objet
    for ( auto& effet : effets) {
        if (effet.peutEtreActive()) {
            effet.appliquer();
        }
    }
}

} // namespace Game::Cartes