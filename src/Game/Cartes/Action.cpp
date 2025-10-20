#include "Game/Cartes/Action.hpp"

namespace Game::Cartes {

Action::Action(int id, const std::string& nom, int cout,
               const Systeme::Faction& faction, const std::string& description,
               const std::vector<Systeme::Effet>& effets)
    : Carte(id, nom, cout, "action", faction, description), effets(effets) {}

void Action::jouer() {
    // Appliquer les effets de la carte action
    for ( auto& effet : effets) {
        if (effet.peutEtreActive()) {
            effet.appliquer();
        }
    }
}

} // namespace Game::Cartes