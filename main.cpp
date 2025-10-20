

#include <iostream>
#include "Game/Core/Partie.hpp"
#include "Game/Core/Joueur.hpp"

int main() {
    using namespace Game::Core;
    std::cout << "=== Hero Realms - Démarrage de la partie ===" << std::endl;

    // Création de deux joueurs
    Joueur joueur1(1);
    Joueur joueur2(2);

    // Création de la partie
    Partie partie;
    // (Normalement on ajouterait les joueurs à la partie, ici c'est un exemple)
    // partie.ajouterJoueur(joueur1);
    // partie.ajouterJoueur(joueur2);

    partie.demarrer();

    std::cout << "La partie a démarré avec succès !" << std::endl;
    return 0;
}

