#include "Game/Systeme/Ressources.hpp"

namespace Game::Systeme {

Ressources::Ressources(int or_initial, int combat_initial)
    : or_val(or_initial), combat(combat_initial) {}

void Ressources::ajouterOr(int montant) {
    or_val += montant;
    if (or_val < 0) or_val = 0;
}

void Ressources::ajouterCombat(int montant) {
    combat += montant;
    if (combat < 0) combat = 0;
}

void Ressources::reinitialiser() {
    or_val = 0;
    combat = 0;
}

} // namespace Game::Systeme