#include "../../../include/Game/Cartes/Objet.hpp"

namespace Game::Cartes {

Objet::Objet(int id, const std::string& nom, int cout,
             const Systeme::Faction& faction, const std::string& description,
             const std::vector<Systeme::Effet>& effetsInit)
    : Carte(id, nom, cout, "objet", faction, description) {
    // Copier les effets dans le vecteur hérité
    for (const auto& effet : effetsInit) {
        effets.push_back(effet);
    }
}

Objet::Objet(const std::string& nom, Systeme::FactionType faction, int cout)
    : Carte(0, nom, cout, "objet", faction, "") {}

void Objet::utiliser() {
    // Les effets sont maintenant appliqués par GameController
    // Cette méthode peut rester vide ou afficher un message
}

} // namespace Game::Cartes