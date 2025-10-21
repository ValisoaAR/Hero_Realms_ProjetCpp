#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <memory>
#include <map>
#include "Game/Core/Joueur.hpp"
#include "Game/Core/Partie.hpp"
#include "Game/Cartes/CarteData.hpp"
#include "Game/Cartes/Carte.hpp"
#include "Game/Cartes/Champion.hpp"
#include "Game/Cartes/Action.hpp"
#include "Game/Cartes/Objet.hpp"

using namespace HeroRealms;
using Game::Cartes::Carte;
using Game::Cartes::Champion;
using Game::Cartes::Action;
using Game::Cartes::Objet;

// Structure pour simuler un joueur en console avec toutes les règles Hero Realms
struct JoueurConsole {
    int id;
    int pv;
    std::vector<std::shared_ptr<Carte>> deck;
    std::vector<std::shared_ptr<Carte>> main;
    std::vector<std::shared_ptr<Carte>> defausse;
    std::vector<std::shared_ptr<Champion>> championsEnJeu;  // Champions actifs sur le terrain
    int orTour = 0;
    int combatTour = 0;
    std::map<Game::Systeme::FactionType, int> factionsJouees;  // Compte les factions jouées ce tour
};

// Fonction pour piocher des cartes
void piocherCartes(JoueurConsole& joueur, int nombre, std::mt19937& rng) {
    for (int i = 0; i < nombre; ++i) {
        if (joueur.deck.empty() && !joueur.defausse.empty()) {
            std::cout << "  -> Deck vide, melange de la defausse..." << std::endl;
            joueur.deck = joueur.defausse;
            joueur.defausse.clear();
            std::shuffle(joueur.deck.begin(), joueur.deck.end(), rng);
        }
        if (!joueur.deck.empty()) {
            joueur.main.push_back(joueur.deck.back());
            joueur.deck.pop_back();
        }
    }
}

// Fonction pour afficher l'etat du joueur
void afficherEtatJoueur(const JoueurConsole& joueur) {
    std::cout << "\n+--- Joueur " << joueur.id << " --------------------+" << std::endl;
    std::cout << "| PV: " << joueur.pv << " | Or: " << joueur.orTour << " | Combat: " << joueur.combatTour << std::endl;
    std::cout << "| Main (" << joueur.main.size() << "): ";
    for (size_t i = 0; i < joueur.main.size(); ++i) {
        std::cout << "[" << (i+1) << "]" << joueur.main[i]->getNom() << " ";
    }
    std::cout << "\n| Champions en jeu (" << joueur.championsEnJeu.size() << "): ";
    for (size_t i = 0; i < joueur.championsEnJeu.size(); ++i) {
        auto champ = joueur.championsEnJeu[i];
        std::cout << "[" << (i+1) << "]" << champ->getNom() << "(" << champ->getPv() << "PV" 
                  << (champ->estGarde() ? ",GARDE" : "") << ") ";
    }
    std::cout << "\n+--------------------------------+" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   Hero Realms - Partie a 2 joueurs   " << std::endl;
    std::cout << "========================================" << std::endl;

    // Initialisation des joueurs avec deck de depart
    JoueurConsole joueur1{1, 50, CreerDeckDepart()};
    JoueurConsole joueur2{2, 50, CreerDeckDepart()};
    
    // Initialisation du generateur aleatoire
    std::random_device rd;
    std::mt19937 rng(rd());
    
    // Melange des decks
    std::shuffle(joueur1.deck.begin(), joueur1.deck.end(), rng);
    std::shuffle(joueur2.deck.begin(), joueur2.deck.end(), rng);
    
    // Distribution initiale de 3 cartes (Hero Realms regle: 3 cartes au debut)
    piocherCartes(joueur1, 3, rng);
    piocherCartes(joueur2, 3, rng);

    // Initialisation du marche avec toutes les cartes du Base Set
    std::cout << "\n[Init] Creation du marche..." << std::endl;
    std::vector<std::shared_ptr<Carte>> piocheMarche = CreerCartesBaseSet();
    auto fireGems = CreerFireGems();
    piocheMarche.insert(piocheMarche.end(), fireGems.begin(), fireGems.end());
    std::shuffle(piocheMarche.begin(), piocheMarche.end(), rng);
    
    // Le marché contient 5 cartes face visible
    std::vector<std::shared_ptr<Carte>> marche;
    for (int i = 0; i < 5 && !piocheMarche.empty(); ++i) {
        marche.push_back(piocheMarche.back());
        piocheMarche.pop_back();
    }
    std::cout << "[Init] Marche initialise avec " << marche.size() << " cartes" << std::endl;
    std::cout << "[Init] Pioche du marche: " << piocheMarche.size() << " cartes restantes" << std::endl;

    int tour = 1;
    bool partie_finie = false;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "         Debut de la partie !           " << std::endl;
    std::cout << "========================================" << std::endl;
    while (!partie_finie) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "           TOUR " << tour << "                        " << std::endl;
        std::cout << "========================================" << std::endl;
        
        for (int idx = 0; idx < 2; ++idx) {
            JoueurConsole& joueur = (idx == 0) ? joueur1 : joueur2;
            JoueurConsole& adv = (idx == 0) ? joueur2 : joueur1;

            std::cout << "\n--- Tour du Joueur " << joueur.id << " ---" << std::endl;
            
            // Debut du tour : pioche jusqu'a 5 cartes
            std::cout << "\n[Phase de pioche]" << std::endl;
            piocherCartes(joueur, 5, rng);
            
            // Reinitialiser les ressources du tour
            joueur.orTour = 0;
            joueur.combatTour = 0;
            joueur.factionsJouees.clear();
            
            // Afficher le marche
            std::cout << "\n[Marche] Cartes disponibles:" << std::endl;
            for (size_t i = 0; i < marche.size(); ++i) {
                std::cout << "  [" << (i+1) << "] " << marche[i]->getNom() 
                          << " (Cout: " << marche[i]->getCout() << " or)";
                if (marche[i]->getType() == "champion") {
                    auto champ = std::dynamic_pointer_cast<Champion>(marche[i]);
                    if (champ) {
                        std::cout << " [Champion " << champ->getPv() << "PV"
                                  << (champ->estGarde() ? " GARDE" : "") << "]";
                    }
                }
                std::cout << std::endl;
            }

            bool fin_tour = false;
            while (!fin_tour && !partie_finie) {
                afficherEtatJoueur(joueur);
                
                std::cout << "\n[Actions] Que voulez-vous faire?" << std::endl;
                std::cout << "  1. Jouer une carte de votre main" << std::endl;
                std::cout << "  2. Acheter une carte du marche" << std::endl;
                std::cout << "  3. Attaquer (champions/joueur adverse)" << std::endl;
                std::cout << "  4. Activer un champion" << std::endl;
                std::cout << "  5. Fin du tour" << std::endl;
                std::cout << "Choix: ";
                
                int choix; 
                std::cin >> choix;
                
                switch (choix) {
                    case 1: { // Jouer une carte
                        if (joueur.main.empty()) {
                            std::cout << "[X] Votre main est vide!" << std::endl;
                            break;
                        }
                        
                        std::cout << "Quelle carte jouer? (1-" << joueur.main.size() << "): ";
                        int carte_idx; 
                        std::cin >> carte_idx;
                        
                        if (carte_idx < 1 || carte_idx > (int)joueur.main.size()) {
                            std::cout << "[X] Choix invalide." << std::endl;
                            break;
                        }
                        
                        auto carte = joueur.main[carte_idx-1];
                        std::cout << "\n[OK] Vous jouez: " << carte->getNom() << std::endl;
                        
                        // Compter la faction jouee pour les capacites alliees
                        joueur.factionsJouees[carte->getFaction()]++;
                        bool estAllie = joueur.factionsJouees[carte->getFaction()] >= 2;
                        
                        // Appliquer les effets de base selon le nom de la carte
                        if (carte->getNom() == "Gold") {
                            joueur.orTour += 1;
                            std::cout << "  -> +1 Or" << std::endl;
                        } else if (carte->getNom() == "Ruby") {
                            joueur.orTour += 2;
                            std::cout << "  -> +2 Or" << std::endl;
                        } else if (carte->getNom() == "Dagger") {
                            joueur.combatTour += 1;
                            std::cout << "  -> +1 Combat" << std::endl;
                        } else if (carte->getNom() == "Shortsword") {
                            joueur.combatTour += 2;
                            std::cout << "  -> +2 Combat" << std::endl;
                        }
                        
                        // Si c'est un champion, il reste en jeu
                        if (carte->getType() == "champion") {
                            auto champ = std::dynamic_pointer_cast<Champion>(carte);
                            if (champ) {
                                joueur.championsEnJeu.push_back(champ);
                                std::cout << "  -> Champion mis en jeu!" << std::endl;
                                if (champ->estGarde()) {
                                    std::cout << "  -> Ce champion a GARDE!" << std::endl;
                                }
                            }
                        } else {
                            // Sinon la carte va a la defausse
                            joueur.defausse.push_back(carte);
                        }
                        
                        if (estAllie) {
                            std::cout << "  [**] ALLIE active! (faction " << (int)carte->getFaction() << ")" << std::endl;
                        }
                        
                        joueur.main.erase(joueur.main.begin() + (carte_idx-1));
                        break;
                    }
                    case 2: { // Acheter une carte
                        if (marche.empty()) {
                            std::cout << "[X] Le marche est vide!" << std::endl;
                            break;
                        }
                        
                        std::cout << "Quelle carte acheter? (1-" << marche.size() << "): ";
                        int achat_idx; 
                        std::cin >> achat_idx;
                        
                        if (achat_idx < 1 || achat_idx > (int)marche.size()) {
                            std::cout << "[X] Choix invalide." << std::endl;
                            break;
                        }
                        
                        auto carte = marche[achat_idx-1];
                        if (joueur.orTour >= carte->getCout()) {
                            joueur.orTour -= carte->getCout();
                            joueur.defausse.push_back(carte);  // Les cartes achetees vont a la defausse
                            std::cout << "\n[OK] Vous achetez: " << carte->getNom() 
                                      << " (-" << carte->getCout() << " Or)" << std::endl;
                            std::cout << "  -> Carte ajoutee a votre defausse" << std::endl;
                            
                            marche.erase(marche.begin() + (achat_idx-1));
                            
                            // Remplir le marche depuis la pioche
                            if (!piocheMarche.empty()) {
                                marche.push_back(piocheMarche.back());
                                piocheMarche.pop_back();
                                std::cout << "  -> Nouvelle carte au marche: " 
                                          << marche.back()->getNom() << std::endl;
                            }
                        } else {
                            std::cout << "[X] Pas assez d'or! (Besoin: " << carte->getCout() 
                                      << ", Vous avez: " << joueur.orTour << ")" << std::endl;
                        }
                        break;
                    }
                    case 3: { // Attaquer
                        if (joueur.combatTour <= 0) {
                            std::cout << "[X] Vous n'avez pas de points de combat!" << std::endl;
                            break;
                        }
                        
                        // Verifier s'il y a des champions avec Garde
                        std::vector<int> gardesIdx;
                        for (size_t i = 0; i < adv.championsEnJeu.size(); ++i) {
                            if (adv.championsEnJeu[i]->estGarde()) {
                                gardesIdx.push_back(i);
                            }
                        }
                        
                        if (!gardesIdx.empty()) {
                            std::cout << "\n[!] L'adversaire a des champions avec GARDE!" << std::endl;
                            std::cout << "Vous devez d'abord detruire les gardes:" << std::endl;
                            for (int idx : gardesIdx) {
                                auto champ = adv.championsEnJeu[idx];
                                std::cout << "  [" << (idx+1) << "] " << champ->getNom() 
                                          << " (" << champ->getPv() << " PV)" << std::endl;
                            }
                            std::cout << "Quel champion attaquer? (0 pour annuler): ";
                            int cible;
                            std::cin >> cible;
                            
                            if (cible == 0) break;
                            if (cible < 1 || cible > (int)adv.championsEnJeu.size()) {
                                std::cout << "[X] Choix invalide." << std::endl;
                                break;
                            }
                            
                            auto champCible = adv.championsEnJeu[cible-1];
                            champCible->subirDegats(joueur.combatTour);
                            std::cout << "\n[ATK] Vous attaquez " << champCible->getNom() 
                                      << " (-" << joueur.combatTour << " PV)" << std::endl;
                            
                            if (champCible->getPv() <= 0) {
                                std::cout << "  [MORT] Champion detruit!" << std::endl;
                                adv.defausse.push_back(champCible);
                                adv.championsEnJeu.erase(adv.championsEnJeu.begin() + (cible-1));
                            }
                            joueur.combatTour = 0;
                            
                        } else if (!adv.championsEnJeu.empty()) {
                            // Il y a des champions mais pas de garde - choix d'attaquer champion ou joueur
                            std::cout << "\nQue voulez-vous attaquer?" << std::endl;
                            std::cout << "  0. Le joueur adverse directement" << std::endl;
                            for (size_t i = 0; i < adv.championsEnJeu.size(); ++i) {
                                auto champ = adv.championsEnJeu[i];
                                std::cout << "  " << (i+1) << ". Champion: " << champ->getNom() 
                                          << " (" << champ->getPv() << " PV)" << std::endl;
                            }
                            std::cout << "Choix: ";
                            int cible;
                            std::cin >> cible;
                            
                            if (cible == 0) {
                                // Attaque directe du joueur
                                adv.pv -= joueur.combatTour;
                                std::cout << "\n[ATK] Vous attaquez Joueur " << adv.id 
                                          << " (-" << joueur.combatTour << " PV)" << std::endl;
                                joueur.combatTour = 0;
                                if (adv.pv <= 0) partie_finie = true;
                            } else if (cible >= 1 && cible <= (int)adv.championsEnJeu.size()) {
                                auto champCible = adv.championsEnJeu[cible-1];
                                champCible->subirDegats(joueur.combatTour);
                                std::cout << "\n[ATK] Vous attaquez " << champCible->getNom() 
                                          << " (-" << joueur.combatTour << " PV)" << std::endl;
                                
                                if (champCible->getPv() <= 0) {
                                    std::cout << "  [MORT] Champion detruit!" << std::endl;
                                    adv.defausse.push_back(champCible);
                                    adv.championsEnJeu.erase(adv.championsEnJeu.begin() + (cible-1));
                                }
                                joueur.combatTour = 0;
                            } else {
                                std::cout << "[X] Choix invalide." << std::endl;
                            }
                        } else {
                            // Pas de champions adverses - attaque directe
                            adv.pv -= joueur.combatTour;
                            std::cout << "\n[ATK] Vous attaquez Joueur " << adv.id 
                                      << " (-" << joueur.combatTour << " PV)" << std::endl;
                            joueur.combatTour = 0;
                            if (adv.pv <= 0) partie_finie = true;
                        }
                        break;
                    }
                    
                    case 4: { // Activer un champion
                        if (joueur.championsEnJeu.empty()) {
                            std::cout << "[X] Vous n'avez pas de champions en jeu!" << std::endl;
                            break;
                        }
                        
                        std::cout << "Quel champion activer? (1-" << joueur.championsEnJeu.size() << "): ";
                        int champ_idx;
                        std::cin >> champ_idx;
                        
                        if (champ_idx >= 1 && champ_idx <= (int)joueur.championsEnJeu.size()) {
                            auto champ = joueur.championsEnJeu[champ_idx-1];
                            std::cout << "[OK] Activation de " << champ->getNom() << std::endl;
                            std::cout << "  (Capacites a implementer)" << std::endl;
                        } else {
                            std::cout << "[X] Choix invalide." << std::endl;
                        }
                        break;
                    }
                    
                    case 5: // Fin du tour
                        fin_tour = true;
                        std::cout << "\n[OK] Fin du tour du Joueur " << joueur.id << std::endl;
                        break;
                        
                    default:
                        std::cout << "[X] Action inconnue." << std::endl;
                        break;
                }
                // Verifier si un joueur est KO
                if (joueur.pv <= 0) {
                    std::cout << "\n[KO] Joueur " << joueur.id << " est elimine!" << std::endl;
                    partie_finie = true;
                }
                if (adv.pv <= 0) {
                    std::cout << "\n[KO] Joueur " << adv.id << " est elimine!" << std::endl;
                    partie_finie = true;
                }
            }
            
            // Fin du tour : nettoyage
            std::cout << "\n[Fin du tour] Defausse de la main..." << std::endl;
            
            // Defausser toutes les cartes de la main
            joueur.defausse.insert(joueur.defausse.end(), joueur.main.begin(), joueur.main.end());
            joueur.main.clear();
            
            // Defausser tous les champions en jeu (sauf ceux avec capacite "reste en jeu")
            for (auto& champ : joueur.championsEnJeu) {
                joueur.defausse.push_back(champ);
            }
            joueur.championsEnJeu.clear();
            
            std::cout << "[Fin du tour] Champions defausses" << std::endl;
            std::cout << "[Fin du tour] Deck: " << joueur.deck.size() 
                      << " | Defausse: " << joueur.defausse.size() << std::endl;
        }
        tour++;
    }
    
    // Fin de la partie
    std::cout << "\n========================================" << std::endl;
    std::cout << "          FIN DE LA PARTIE !            " << std::endl;
    std::cout << "========================================" << std::endl;
    
    if (joueur1.pv > 0) {
        std::cout << "[VICTOIRE] Joueur 1 gagne avec " << joueur1.pv << " PV restants!" << std::endl;
    } else {
        std::cout << "[VICTOIRE] Joueur 2 gagne avec " << joueur2.pv << " PV restants!" << std::endl;
    }
    
    return 0;
}

