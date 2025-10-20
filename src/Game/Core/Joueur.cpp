#include "Game/Core/Joueur.hpp"

namespace Game::Core {

Joueur::Joueur(int id, int pv)
    : id(id), pv(pv), ressources(0, 0),
      main("main"), deck("deck"), defausse("defausse"), champions("champions")
{
}

void Joueur::modifierPv(int delta) {
    pv += delta;
    if (pv < 0) pv = 0;
}

void Joueur::modifierOr(int delta) {
    ressources.ajouterOr(delta);
}

void Joueur::modifierCombat(int delta) {
    ressources.ajouterCombat(delta);
}

} // namespace Game::Core