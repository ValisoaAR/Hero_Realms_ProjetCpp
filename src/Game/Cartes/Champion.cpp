#include "../../../include/Game/Cartes/Champion.hpp"

namespace Game::Cartes {

Champion::Champion(int id, const std::string& nom, int cout,
                  const Systeme::Faction& faction, const std::string& description,
                  int pv, bool garde)
    : Carte(id, nom, cout, "champion", faction, description),
      pv(pv), active(false), garde(garde) {}

// Constructeur simplifié pour CarteData
Champion::Champion(const std::string& nom, Systeme::FactionType faction, int cout, int pv, bool garde)
    : Carte(0, nom, cout, "champion", faction, ""),
      pv(pv), active(false), garde(garde) {}

void Champion::activer() {
    // Marquer le champion comme actif (utilisé ce tour)
    active = true;
    // Note: Les effets "expend" sont appliqués par GameController::activerChampion()
}

void Champion::desactiver() {
    active = false;
}

void Champion::subirDegats(int degats) {
    pv -= degats;
    if (pv < 0) pv = 0;
}

} // namespace Game::Cartes