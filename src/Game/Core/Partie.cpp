#include "Game/Core/Partie.hpp"

namespace Game::Core {

void Partie::ajouterJoueur(const Joueur& joueur) {
    joueurs.push_back(joueur);
}

Partie::Partie() : phaseActuelle(Phase::DEBUT_TOUR) {}

void Partie::demarrer() {
    // Distribuer les decks de départ aux joueurs
    // 8 pièces de or (0 coût) et 2 dagues courtes (1 coût, +1 combat)
    for (auto& joueur : joueurs) {
        // À implémenter: distribution des cartes de départ
    }
    
    // Mélanger les decks des joueurs
    // À implémenter
    
    // Piocher les premières mains (5 cartes)
    // À implémenter
}

void Partie::finirTour() {
    auto& joueurActuel = joueurs[0]; // À modifier pour gérer plusieurs joueurs
    
    // Défausser les cartes restantes en main
    // À implémenter
    
    // Désactiver les champions
    // À implémenter
    
    // Piocher 5 nouvelles cartes
    // À implémenter
    
    phaseActuelle = Phase::DEBUT_TOUR;
}

void Partie::terminer() {
    // Vérifier les conditions de victoire
    // Gérer la fin de partie
    // À implémenter
}

} // namespace Game::Core