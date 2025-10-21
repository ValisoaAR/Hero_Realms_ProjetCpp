

#include <iostream>

#include "Game/Core/Partie.hpp"
#include "Game/Core/Joueur.hpp"
#include <vector>
#include <string>
#include <algorithm>

struct CarteSimple {
    std::string nom;
    int cout;
    std::string type; // "or", "dague", "marche"
    int effet; // or ou combat
};

int main() {
    using namespace Game::Core;
    std::cout << "=== Hero Realms - Démarrage de la partie ===" << std::endl;

    // Création de deux joueurs
    Joueur joueur1(1);
    Joueur joueur2(2);

    // Decks de départ
    std::vector<CarteSimple> deck_depart;
    for (int i = 0; i < 8; ++i) deck_depart.push_back({"Or", 0, "or", 1});
    deck_depart.push_back({"Epée courte", 1, "arme", 2});
    deck_depart.push_back({"Dague", 1, "dague", 1});

    // Decks des joueurs
    std::vector<CarteSimple> deck1 = deck_depart;
    std::vector<CarteSimple> deck2 = deck_depart;
    std::random_shuffle(deck1.begin(), deck1.end());
    std::random_shuffle(deck2.begin(), deck2.end());

    // Or de départ
    joueur1.modifierOr(7);
    joueur2.modifierOr(7);

    // Main et défausse
    std::vector<CarteSimple> main1, main2, defausse1, defausse2;

    // Marché
    std::vector<CarteSimple> marche = {
        {"Epée longue", 3, "arme", 3},
        {"Arc", 2, "arme", 2},
        {"Bouclier", 2, "objet", 0},
        {"Potion", 1, "objet", 0}
    };

    Partie partie;
    partie.ajouterJoueur(joueur1);
    partie.ajouterJoueur(joueur2);
    partie.demarrer();

    std::cout << "La partie a démarré avec succès !" << std::endl;

    int tour = 1;
    bool partie_finie = false;
    while (!partie_finie) {
        std::cout << "\n=== Tour " << tour << " ===" << std::endl;
        for (int idx = 0; idx < 2; ++idx) {
            Joueur& joueur = partie.getJoueurs()[idx];
            std::vector<CarteSimple>& deck = (idx == 0) ? deck1 : deck2;
            std::vector<CarteSimple>& main = (idx == 0) ? main1 : main2;
            std::vector<CarteSimple>& defausse = (idx == 0) ? defausse1 : defausse2;

            // Pioche 5 cartes
            while (main.size() < 5 && !deck.empty()) {
                main.push_back(deck.back());
                deck.pop_back();
            }
            if (main.size() < 5 && !defausse.empty()) {
                std::cout << "Deck vide, mélange la défausse." << std::endl;
                deck = defausse;
                defausse.clear();
                std::random_shuffle(deck.begin(), deck.end());
                while (main.size() < 5 && !deck.empty()) {
                    main.push_back(deck.back());
                    deck.pop_back();
                }
            }

            std::cout << "\nJoueur " << joueur.getId() << " : " << joueur.getPv() << " PV, " << joueur.getOr() << " or, " << joueur.getCombat() << " combat" << std::endl;
            std::cout << "Main : ";
            for (size_t i = 0; i < main.size(); ++i) std::cout << main[i].nom << (i < main.size()-1 ? ", " : "");
            std::cout << std::endl;

            std::cout << "Marché : ";
            for (size_t i = 0; i < marche.size(); ++i) std::cout << i+1 << "." << marche[i].nom << "(" << marche[i].cout << " or) ";
            std::cout << std::endl;

            bool fin_tour = false;
            while (!fin_tour && !partie_finie) {
                std::cout << "Choisissez une action :" << std::endl;
                std::cout << "  1. Attaquer l'autre joueur" << std::endl;
                std::cout << "  2. Jouer une carte de la main" << std::endl;
                std::cout << "  3. Acheter une carte du marché" << std::endl;
                std::cout << "  4. Fin du tour" << std::endl;
                int choix;
                std::cin >> choix;
                switch (choix) {
                    case 1: {
                        int cible = (joueur.getId() == 1) ? 2 : 1;
                        for (auto& adv : partie.getJoueurs()) {
                            if (adv.getId() == cible) {
                                adv.modifierPv(-5);
                                std::cout << "  -> Vous attaquez Joueur " << cible << " (-5 PV)" << std::endl;
                                if (adv.getPv() <= 0) partie_finie = true;
                            }
                        }
                        break;
                    }
                    case 2: {
                        std::cout << "Quelle carte voulez-vous jouer ? (1-" << main.size() << ")" << std::endl;
                        int carte_idx; std::cin >> carte_idx;
                        if (carte_idx >= 1 && carte_idx <= (int)main.size()) {
                            CarteSimple carte = main[carte_idx-1];
                            if (carte.type == "or") {
                                joueur.modifierOr(carte.effet);
                                std::cout << "  -> Vous gagnez " << carte.effet << " or" << std::endl;
                            } else if (carte.type == "dague" || carte.type == "arme") {
                                joueur.modifierCombat(carte.effet);
                                std::cout << "  -> Vous gagnez " << carte.effet << " combat" << std::endl;
                            } else {
                                std::cout << "  -> Effet de la carte non géré." << std::endl;
                            }
                            defausse.push_back(carte);
                            main.erase(main.begin() + (carte_idx-1));
                        } else {
                            std::cout << "  -> Choix invalide." << std::endl;
                        }
                        break;
                    }
                    case 3: {
                        std::cout << "Quelle carte acheter ? (1-" << marche.size() << ")" << std::endl;
                        int achat_idx; std::cin >> achat_idx;
                        if (achat_idx >= 1 && achat_idx <= (int)marche.size()) {
                            CarteSimple carte = marche[achat_idx-1];
                            if (joueur.getOr() >= carte.cout) {
                                joueur.modifierOr(-carte.cout);
                                deck.push_back(carte);
                                std::cout << "  -> Vous achetez " << carte.nom << " et l'ajoutez à votre deck." << std::endl;
                                marche.erase(marche.begin() + (achat_idx-1));
                            } else {
                                std::cout << "  -> Pas assez d'or." << std::endl;
                            }
                        } else {
                            std::cout << "  -> Choix invalide." << std::endl;
                        }
                        break;
                    }
                    case 4:
                        fin_tour = true;
                        std::cout << "  -> Fin du tour pour ce joueur" << std::endl;
                        break;
                    default:
                        std::cout << "  -> Action inconnue, tour passé." << std::endl;
                        break;
                }
                std::cout << "Etat : " << joueur.getPv() << " PV, " << joueur.getOr() << " or, " << joueur.getCombat() << " combat" << std::endl;
                if (joueur.getPv() <= 0) {
                    std::cout << "\nJoueur " << joueur.getId() << " est KO !" << std::endl;
                    partie_finie = true;
                }
            }
            // Fin du tour : défausser la main
            defausse.insert(defausse.end(), main.begin(), main.end());
            main.clear();
            // Réinitialiser les ressources combat
            joueur.modifierCombat(-joueur.getCombat());
        }
        tour++;
    }
    std::cout << "\nFin de la partie !" << std::endl;
    return 0;
}

