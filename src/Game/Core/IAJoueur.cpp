#include "../../../include/Game/Core/IAJoueur.hpp"
#include "../../../include/Game/Core/GameController.hpp"
#include "../../../include/Game/Core/GameView.hpp"
#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>

namespace Game::Core {

    IAJoueur::IAJoueur() {
    }

    void IAJoueur::jouerTour(GameController& controller, GameView& view, int joueurIdx, std::mt19937& rng) {
        Joueur& joueur = controller.getJoueurMutable(joueurIdx);
        Joueur& adversaire = controller.getJoueurMutable(1 - joueurIdx);
        
        std::cout << "\n=== Tour de l'IA (Joueur " << (joueurIdx + 1) << ") ===\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        
        // Phase 1 : Jouer toutes les cartes de la main
        jouerToutesLesCartes(controller, joueur);
        
        // Phase 2 : Acheter des cartes
        acheterCartes(controller, view, joueur, controller.getMarche(), rng);
        
        // Phase 3 : Activer tous les champions
        activerTousLesChampions(controller, joueur);
        
        // Phase 4 : Attaquer
        attaquerAdversaire(controller, joueur, adversaire, rng);
        
        std::cout << "\nL'IA termine son tour.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    void IAJoueur::jouerToutesLesCartes(GameController& controller, Joueur& joueur) {
        // Joue toutes les cartes une par une (indices vont de 0 à taille-1)
        while (joueur.getMain().getNbCartes() > 0) {
            auto& main = joueur.getMain();
            auto carte = main.getCarte(0); // Prend toujours la première carte
            
            std::cout << "L'IA joue : " << carte->getNom() << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            controller.jouerCarte(joueur, 0); // Joue toujours l'index 0
        }
    }

    void IAJoueur::acheterCartes(GameController& controller, GameView& view, 
                                  Joueur& joueur, const Zones::Marche& marche, std::mt19937& rng) {
        // Achète des cartes tant qu'il y a de l'or
        while (joueur.getRessources().getOr() > 0 && marche.getNbCartes() > 0) {
            int idxCarte = choisirMeilleureCarteAcheter(marche, joueur.getRessources().getOr(), rng);
            
            if (idxCarte == -1) {
                break; // Aucune carte achetable
            }
            
            auto carte = marche.getCarte(idxCarte);
            std::cout << "L'IA achete : " << carte->getNom() << " (cout: " << carte->getCout() << ")\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
            
            controller.acheterCarte(joueur, idxCarte);
        }
    }

    void IAJoueur::attaquerAdversaire(GameController& controller, Joueur& joueur, 
                                       Joueur& adversaire, std::mt19937& rng) {
        // Utilise tous les points de combat disponibles
        while (joueur.getRessources().getCombat() > 0) {
            int cible = choisirCibleAttaque(adversaire, rng);
            
            if (cible == -1) {
                // Attaque le joueur directement
                std::cout << "L'IA attaque le joueur adverse pour " 
                          << joueur.getRessources().getCombat() << " degats\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(600));
                
                controller.attaquer(joueur, adversaire, -1);
                break;
            } else {
                // Attaque un champion
                auto champion = adversaire.getChampionsEnJeu()[cible];
                std::cout << "L'IA attaque le champion " << champion->getNom() 
                          << " (Defense: " << std::dynamic_pointer_cast<Cartes::Champion>(champion)->getPv() 
                          << ")\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(600));
                
                controller.attaquer(joueur, adversaire, cible);
            }
        }
    }

    void IAJoueur::activerTousLesChampions(GameController& controller, Joueur& joueur) {
        // Active tous les champions en jeu
        for (size_t i = 0; i < joueur.getChampionsEnJeu().size(); ++i) {
            auto champion = joueur.getChampionsEnJeu()[i];
            std::cout << "L'IA active le champion : " << champion->getNom() << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            controller.activerChampion(joueur, static_cast<int>(i));
        }
    }

    int IAJoueur::choisirMeilleureCarteAcheter(const Zones::Marche& marche, 
                                                int orDisponible, std::mt19937& rng) {
        int meilleurIdx = -1;
        int meilleurScore = -1;
        
        // Parcourt toutes les cartes du marché
        for (int i = 0; i < static_cast<int>(marche.getNbCartes()); ++i) {
            auto carte = marche.getCarte(i);
            
            // Vérifie si on peut l'acheter
            if (carte->getCout() <= orDisponible) {
                int score = evaluerCarte(carte);
                
                // Préfère les cartes plus chères (en général plus puissantes)
                score += carte->getCout() * 10;
                
                if (score > meilleurScore) {
                    meilleurScore = score;
                    meilleurIdx = i;
                }
            }
        }
        
        return meilleurIdx;
    }

    int IAJoueur::choisirCibleAttaque(const Joueur& adversaire, std::mt19937& rng) {
        const auto& champions = adversaire.getChampionsEnJeu();
        
        if (champions.empty()) {
            return -1; // Attaque le joueur
        }
        
        // Cherche d'abord les champions avec garde
        for (size_t i = 0; i < champions.size(); ++i) {
            auto champion = std::dynamic_pointer_cast<Cartes::Champion>(champions[i]);
            if (champion && champion->estGarde()) {
                return static_cast<int>(i);
            }
        }
        
        // Sinon, attaque un champion aléatoire parmi ceux présents
        // ou attaque directement le joueur (50% de chance)
        std::uniform_int_distribution<int> dist(0, 1);
        if (dist(rng) == 0 && !champions.empty()) {
            std::uniform_int_distribution<int> champDist(0, champions.size() - 1);
            return champDist(rng);
        }
        
        return -1; // Attaque le joueur
    }

    int IAJoueur::evaluerCarte(std::shared_ptr<Cartes::Carte> carte) const {
        if (!carte) return 0;
        
        int score = 0;
        
        // Les champions valent plus (restent en jeu)
        auto champion = std::dynamic_pointer_cast<Cartes::Champion>(carte);
        if (champion) {
            score += 50;
            score += champion->getPv() * 5; // Plus de défense = mieux
        }
        
        // Évalue basiquement selon le coût (carte chère = généralement puissante)
        score += carte->getCout() * 15;
        
        return score;
    }

} // namespace Game::Core
