#include "../../../include/Game/Zones/ZoneFireGem.hpp"
#include "../../../include/Game/Cartes/CarteData.hpp"

namespace Game::Zones {

ZoneFireGem::ZoneFireGem() : ZoneDeCarte("firegem") {}

void ZoneFireGem::initialiser() {
    // Créer les Fire Gems et les ajouter à la zone
    auto fireGems = HeroRealms::CreerFireGems();
    for (auto& gem : fireGems) {
        ajouterCarte(gem);
    }
}

std::shared_ptr<Cartes::Carte> ZoneFireGem::acheterFireGem() {
    if (!cartes.empty()) {
        auto fireGem = cartes.back();
        cartes.pop_back();
        return fireGem;
    }
    return nullptr;
}

} // namespace Game::Zones
