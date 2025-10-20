#include "Game/Zones/Marche.hpp"

namespace Game::Zones {

Marche::Marche() : ZoneDeCarte("marche") {}

void Marche::rafraichir() {
    // Défausser toutes les cartes du marché
    while (!cartes.empty()) {
        // À implémenter: déplacer les cartes vers la défausse
        cartes.pop_back();
    }
    
    // Piocher de nouvelles cartes du deck du marché
    // À implémenter
}

void Marche::acheterCarte(int position) {
    if (position < 0 || position >= static_cast<int>(cartes.size())) {
        return;
    }
    
    // Vérifier si le joueur a assez d'or
    // Ajouter la carte à la défausse du joueur
    // À implémenter
    
    retirerCarte(position);
}

void Marche::defausserCarte(int position) {
    if (position < 0 || position >= static_cast<int>(cartes.size())) {
        return;
    }
    
    // Déplacer la carte vers la défausse du marché
    // À implémenter
    
    retirerCarte(position);
}

} // namespace Game::Zones