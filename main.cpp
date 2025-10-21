


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include "Game/Core/Joueur.hpp"
#include "Game/Core/Partie.hpp"
#include "Game/Cartes/CarteData.hpp"

using namespace HeroRealms;


#include "Game/Cartes/Carte.hpp"
using Game::Cartes::Carte;
struct JoueurConsole {
    int id;
    int pv = 50;
    std::vector<std::shared_ptr<Carte>> deck;
    std::vector<std::shared_ptr<Carte>> main;
    std::vector<std::shared_ptr<Carte>> defausse;
    int orTour = 0;
    int combatTour = 0;
};

int main() {
    std::cout << "=== Hero Realms - Démarrage de la partie ===" << std::endl;

    // Initialisation des joueurs
    JoueurConsole joueur1{1, 50, CreerDeckDepart()};
    JoueurConsole joueur2{2, 50, CreerDeckDepart()};
    std::random_shuffle(joueur1.deck.begin(), joueur1.deck.end());
    std::random_shuffle(joueur2.deck.begin(), joueur2.deck.end());

    // Initialisation du marché
    std::vector<std::shared_ptr<Carte>> piocheMarche = CreerCartesBaseSet();
    auto fireGems = CreerFireGems();
    piocheMarche.insert(piocheMarche.end(), fireGems.begin(), fireGems.end());
    std::random_shuffle(piocheMarche.begin(), piocheMarche.end());
    std::vector<std::shared_ptr<Carte>> marche;
    for (int i = 0; i < 5 && !piocheMarche.empty(); ++i) {
        marche.push_back(piocheMarche.back());
        piocheMarche.pop_back();
    }

    int tour = 1;
    bool partie_finie = false;
    while (!partie_finie) {
        std::cout << "\n=== Tour " << tour << " ===" << std::endl;
        for (int idx = 0; idx < 2; ++idx) {
            JoueurConsole& joueur = (idx == 0) ? joueur1 : joueur2;
            JoueurConsole& adv = (idx == 0) ? joueur2 : joueur1;

            // Pioche 5 cartes
            while (joueur.main.size() < 5 && !joueur.deck.empty()) {
                joueur.main.push_back(joueur.deck.back());
                joueur.deck.pop_back();
            }
            if (joueur.main.size() < 5 && !joueur.defausse.empty()) {
                std::cout << "Deck vide, mélange la défausse." << std::endl;
                joueur.deck = joueur.defausse;
                joueur.defausse.clear();
                std::random_shuffle(joueur.deck.begin(), joueur.deck.end());
                while (joueur.main.size() < 5 && !joueur.deck.empty()) {
                    joueur.main.push_back(joueur.deck.back());
                    joueur.deck.pop_back();
                }
            }

            joueur.orTour = 0;
            joueur.combatTour = 0;

            std::cout << "\nJoueur " << joueur.id << " : " << joueur.pv << " PV" << std::endl;
            std::cout << "Main : ";
            for (size_t i = 0; i < joueur.main.size(); ++i) std::cout << i+1 << "." << joueur.main[i]->getNom() << (i < joueur.main.size()-1 ? ", " : "");
            std::cout << std::endl;

            std::cout << "Marché : ";
            for (size_t i = 0; i < marche.size(); ++i) std::cout << i+1 << "." << marche[i]->getNom() << "(" << marche[i]->getCout() << " or) ";
            std::cout << std::endl;

            bool fin_tour = false;
            while (!fin_tour && !partie_finie) {
                std::cout << "Actions : 1.Jouer carte 2.Acheter 3.Attaquer 4.Fin du tour" << std::endl;
                int choix; std::cin >> choix;
                switch (choix) {
                    case 1: {
                        std::cout << "Quelle carte jouer ? (1-" << joueur.main.size() << ")" << std::endl;
                        int carte_idx; std::cin >> carte_idx;
                        if (carte_idx >= 1 && carte_idx <= (int)joueur.main.size()) {
                            auto carte = joueur.main[carte_idx-1];
                            // Effet simple : or/combat
                            if (carte->getNom() == "Gold") joueur.orTour += 1;
                            else if (carte->getNom() == "Ruby") joueur.orTour += 2;
                            else if (carte->getNom() == "Dagger") joueur.combatTour += 1;
                            else if (carte->getNom() == "Shortsword") joueur.combatTour += 2;
                            // ... autres effets à enrichir ici
                            std::cout << "Vous jouez " << carte->getNom() << std::endl;
                            joueur.defausse.push_back(carte);
                            joueur.main.erase(joueur.main.begin() + (carte_idx-1));
                        } else std::cout << "Choix invalide." << std::endl;
                        break;
                    }
                    case 2: {
                        std::cout << "Quelle carte acheter ? (1-" << marche.size() << ")" << std::endl;
                        int achat_idx; std::cin >> achat_idx;
                        if (achat_idx >= 1 && achat_idx <= (int)marche.size()) {
                            auto carte = marche[achat_idx-1];
                            if (joueur.orTour >= carte->getCout()) {
                                joueur.orTour -= carte->getCout();
                                joueur.deck.push_back(carte);
                                std::cout << "Vous achetez " << carte->getNom() << " et l'ajoutez à votre deck." << std::endl;
                                marche.erase(marche.begin() + (achat_idx-1));
                                if (!piocheMarche.empty()) {
                                    marche.push_back(piocheMarche.back());
                                    piocheMarche.pop_back();
                                }
                            } else std::cout << "Pas assez d'or." << std::endl;
                        } else std::cout << "Choix invalide." << std::endl;
                        break;
                    }
                    case 3: {
                        // Attaque : priorité aux gardes
                        int totalGarde = 0;
                        // ... ici, il faudrait parcourir les champions adverses pour voir les gardes
                        // Version simple : attaque directe
                        if (joueur.combatTour > 0) {
                            adv.pv -= joueur.combatTour;
                            std::cout << "Vous attaquez Joueur " << adv.id << " (-" << joueur.combatTour << " PV)" << std::endl;
                            joueur.combatTour = 0;
                            if (adv.pv <= 0) partie_finie = true;
                        } else std::cout << "Pas de points de combat." << std::endl;
                        break;
                    }
                    case 4:
                        fin_tour = true;
                        std::cout << "Fin du tour." << std::endl;
                        break;
                    default:
                        std::cout << "Action inconnue." << std::endl;
                        break;
                }
                std::cout << "Etat : PV=" << joueur.pv << " | Or tour=" << joueur.orTour << " | Combat tour=" << joueur.combatTour << std::endl;
                if (joueur.pv <= 0) {
                    std::cout << "Joueur " << joueur.id << " est KO !" << std::endl;
                    partie_finie = true;
                }
                if (adv.pv <= 0) {
                    std::cout << "Joueur " << adv.id << " est KO !" << std::endl;
                    partie_finie = true;
                }
            }
            // Fin du tour : défausser la main
            joueur.defausse.insert(joueur.defausse.end(), joueur.main.begin(), joueur.main.end());
            joueur.main.clear();
        }
        tour++;
    }
    std::cout << "\nFin de la partie !" << std::endl;
    return 0;
}

