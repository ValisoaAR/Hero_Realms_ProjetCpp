// ✅ FICHIER UTILISÉ - Gestion du marché

#include "../../../include/Game/Zones/Marche.hpp"
#include <algorithm>

namespace Game::Zones {

Marche::Marche() : ZoneDeCarte("marche") {}

void Marche::initialiser(std::vector<std::shared_ptr<Cartes::Carte>>& pioche, std::mt19937& rng) {
    // Mélanger la pioche
    std::shuffle(pioche.begin(), pioche.end(), rng);
    
    // Piocher les 5 premières cartes
    remplir(pioche);
}

void Marche::remplir(std::vector<std::shared_ptr<Cartes::Carte>>& pioche) {
    while (cartes.size() < TAILLE_MARCHE && !pioche.empty()) {
        cartes.push_back(pioche.back());
        pioche.pop_back();
    }
}

std::shared_ptr<Cartes::Carte> Marche::acheter(int position) {
    return retirerCarte(position);
}

void Marche::rafraichir(std::vector<std::shared_ptr<Cartes::Carte>>& pioche, 
                        std::vector<std::shared_ptr<Cartes::Carte>>& defausse) {
    // Défausser toutes les cartes du marché
    while (!cartes.empty()) {
        defausse.push_back(cartes.back());
        cartes.pop_back();
    }
    
    // Remplir avec de nouvelles cartes
    remplir(pioche);
}

} // namespace Game::Zones