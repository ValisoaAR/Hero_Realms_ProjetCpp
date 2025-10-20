#include "Game/Cartes/Champion.hpp"

namespace Game::Cartes {

Champion::Champion(int id, const std::string& nom, int cout,
                  const Systeme::Faction& faction, const std::string& description,
                  int pv, bool garde)
    : Carte(id, nom, cout, "champion", faction, description),
      pv(pv), active(false), garde(garde) {}

void Champion::activer() {
    if (!active) {
        active = true;
        for (auto& effet : effets) {  // Enlever le const
            if (effet.peutEtreActive()) {
                effet.appliquer();
            }
        }
    }
}

void Champion::desactiver() {
    active = false;
}

void Champion::subirDegats(int degats) {
    pv -= degats;
    if (pv < 0) pv = 0;
}

} // namespace Game::Cartes