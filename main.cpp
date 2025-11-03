#include <iostream>
#include "Game/Core/GameController.hpp"
#include "Game/Core/GameView.hpp"
#include "Game/Utils/Couleurs.hpp"

using namespace Game::Core;
using namespace Game::Utils::Couleurs;

void afficherMenuDemarrage() {
    std::cout << "\n";
    std::cout << TITRE << "========================================" << RESET << std::endl;
    std::cout << TITRE << "         HERO REALMS - MENU             " << RESET << std::endl;
    std::cout << TITRE << "========================================" << RESET << std::endl;
    std::cout << "\n" << GRAS << "Choisissez le mode de jeu:" << RESET << std::endl;
    std::cout << "  " << CYAN << "1." << RESET << " Jouer contre l'IA" << std::endl;
    std::cout << "  " << CYAN << "2." << RESET << " Jouer a 2 joueurs (local)" << std::endl;
    std::cout << "  " << ROUGE << "0." << RESET << " Quitter" << std::endl;
    std::cout << "\n" << JAUNE << "Choix: " << RESET;
}

int main() {
    bool continuer = true;
    
    while (continuer) {
        afficherMenuDemarrage();
        
        int choix;
        std::cin >> choix;
        
        // Vérifier si l'entrée est valide
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "\n[ERREUR] Entree invalide! Veuillez entrer un numero.\n" << std::endl;
            continue;
        }
        
        switch (choix) {
            case 1: {
                // Mode contre l'IA
                std::cout << "\n[MODE] Vous allez jouer contre l'IA!" << std::endl;
                std::cout << "Appuyez sur Entree pour commencer...";
                std::cin.ignore();
                std::cin.get();
                
                GameController controller;
                GameView view;
                controller.setJoueur2EstIA(true);
                controller.setNomJoueur2("IA");
                controller.jouerPartie(view);
                
                std::cout << "\nAppuyez sur Entree pour retourner au menu...";
                std::cin.get();
                break;
            }
            
            case 2: {
                // Mode 2 joueurs local
                std::cout << "\n[MODE] Partie a 2 joueurs en local!" << std::endl;
                std::cout << "Appuyez sur Entree pour commencer...";
                std::cin.ignore();
                std::cin.get();
                
                GameController controller;
                GameView view;
                controller.setJoueur2EstIA(false);
                controller.setNomJoueur2("Joueur 2");
                controller.jouerPartie(view);
                
                std::cout << "\nAppuyez sur Entree pour retourner au menu...";
                std::cin.get();
                break;
            }
            
            case 0:
                std::cout << "\nMerci d'avoir joue a Hero Realms! Au revoir!" << std::endl;
                continuer = false;
                break;
                
            default:
                std::cout << "\n[ERREUR] Choix invalide! Veuillez choisir 1, 2 ou 0.\n" << std::endl;
                break;
        }
    }
    
    return 0;
}

