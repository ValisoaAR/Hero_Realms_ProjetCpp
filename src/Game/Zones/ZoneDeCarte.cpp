#include "../../../include/Game/Zones/ZoneDeCarte.hpp"
#include <algorithm>
#include <random>

namespace Game::Zones {

ZoneDeCarte::ZoneDeCarte(const std::string& type) : type(type) {}

void ZoneDeCarte::ajouterCarte(std::shared_ptr<Cartes::Carte> carte) {
    if (carte) {
        cartes.push_back(carte);
    }
}

std::shared_ptr<Cartes::Carte> ZoneDeCarte::retirerCarte(int position) {
    if (position < 0 || position >= static_cast<int>(cartes.size())) {
        return nullptr;
    }
    
    auto carte = cartes[position];
    cartes.erase(cartes.begin() + position);
    return carte;
}

std::shared_ptr<Cartes::Carte> ZoneDeCarte::getCarte(int position) const {
    if (position < 0 || position >= static_cast<int>(cartes.size())) {
        return nullptr;
    }
    return cartes[position];
}

void ZoneDeCarte::melanger() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cartes.begin(), cartes.end(), g);
}

} // namespace Game::Zones