#include "../../../include/Game/Cartes/Action.hpp"

namespace Game::Cartes {

Action::Action(int id, const std::string& nom, int cout,
               const Systeme::Faction& faction, const std::string& description,
               const std::vector<Systeme::Effet>& effetsInit)
    : Carte(id, nom, cout, "action", faction, description) {
    // Copier les effets dans le vecteur hérité
    for (const auto& effet : effetsInit) {
        effets.push_back(effet);
    }
}

Action::Action(const std::string& nom, Systeme::FactionType faction, int cout)
    : Carte(0, nom, cout, "action", faction, "") {}

void Action::jouer() {
    // Les effets sont maintenant appliqués par GameController
    // Cette méthode peut rester vide ou afficher un message
}

} // namespace Game::Cartes