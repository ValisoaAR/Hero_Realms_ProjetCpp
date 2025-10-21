#include "../../../include/Game/Zones/ZoneDeCarte.hpp"
#include "../../../include/Game/Utils/SimpleRng.h"
#include <algorithm>

namespace Game::Zones {

ZoneDeCarte::ZoneDeCarte(const std::string& type) : type(type) {}

void ZoneDeCarte::ajouterCarte(Cartes::Carte* carte, int position) {
    if (position < 0 || position >= static_cast<int>(cartes.size())) {
        cartes.push_back(carte);
    } else {
        cartes.insert(cartes.begin() + position, carte);
    }
}

Cartes::Carte* ZoneDeCarte::retirerCarte(int position) {
    if (position < 0 || position >= static_cast<int>(cartes.size())) {
        return nullptr;
    }
    
    Cartes::Carte* carte = cartes[position];
    cartes.erase(cartes.begin() + position);
    return carte;
}

void ZoneDeCarte::melanger() {
    std::random_shuffle(cartes.begin(), cartes.end());
}

size_t ZoneDeCarte::getNbCartes() const {
    return cartes.size();
}

} // namespace Game::Zones