#include "../../../include/Game/Core/GameController.hpp"
#include "../../../include/Game/Core/GameView.hpp"
#include "../../../include/Game/Cartes/CarteData.hpp"
#include "../../../include/Game/Cartes/Action.hpp"
#include "../../../include/Game/Cartes/Objet.hpp"
#include <algorithm>
#include <iostream>

namespace Game::Core {

// GameController
GameController::GameController() 
    : joueur1("Joueur 1"), joueur2("Joueur 2"), tourActuel(1), finie(false), godModeActif(false) {
    std::random_device rd;
    rng.seed(rd());
}

void GameController::jouerPartie(GameView& view) {
    // Affichage du titre
    view.afficherTitre();
    
    // Initialisation
    initialiserPartie();
    view.afficherDebut();
    
    // Boucle principale de jeu
    while (!partieFinie()) {
        // Tour pour chaque joueur
        for (int joueurIdx = 0; joueurIdx < 2; ++joueurIdx) {
            jouerTour(joueurIdx, view);
            
            // Vérifier si la partie est terminée
            if (partieFinie()) {
                break;
            }
        }
        tourActuel++;
    }
    
    // Affichage de la fin de partie
    int vainqueur = getVainqueur();
    int pvRestants = getJoueur(vainqueur).getPv();
    view.afficherFinPartie(vainqueur + 1, pvRestants);
}

void GameController::jouerTour(int joueurIdx, GameView& view) {
    auto& joueur = getJoueurMutable(joueurIdx);
    auto& adversaire = getJoueurMutable(1 - joueurIdx);
    
    view.afficherDebutTour(tourActuel, joueurIdx + 1);
    
    // Début du tour
    debutTour(joueur);
    
    // Phase d'actions
    bool finTour = false;
    while (!finTour && !partieFinie()) {
        // Affichage de l'état actuel à chaque itération
        view.afficherEtatJoueur(joueur);
        view.afficherMarche(marche);
        view.afficherMenuPrincipal();
        
        int choix;
        std::cin >> choix;
        
        switch (choix) {
            case 1: { // Jouer une ou plusieurs cartes
                if (joueur.getMain().getCartes().empty()) {
                    view.afficherErreur("Votre main est vide!");
                    break;
                }
                
                bool continuerJouer = true;
                while (continuerJouer && !joueur.getMain().getCartes().empty()) {
                    // Afficher l'état avant de demander quelle carte jouer
                    std::cout << "\n";
                    view.afficherEtatJoueur(joueur);
                    
                    int carteIdx = view.demanderChoix("Quelle carte jouer? (0 pour arreter)", 0, joueur.getMain().getCartes().size());
                    
                    if (carteIdx == 0) {
                        continuerJouer = false;
                    } else if (carteIdx >= 1 && carteIdx <= (int)joueur.getMain().getCartes().size()) {
                        if (jouerCarte(joueur, carteIdx - 1)) {
                            view.afficherResultatAction("Carte jouee avec succes!");
                        } else {
                            view.afficherErreur("Impossible de jouer cette carte.");
                        }
                    } else {
                        view.afficherErreur("Choix invalide.");
                    }
                }
                break;
            }
            
            case 2: { // Acheter une carte
                if (marche.getCartes().empty()) {
                    view.afficherErreur("Le marche est vide!");
                    break;
                }
                
                // Afficher le marché avant de demander l'achat
                std::cout << "\n";
                view.afficherMarche(marche);
                
                int carteIdx = view.demanderChoix("Quelle carte acheter? (0 pour annuler)", 0, marche.getCartes().size());
                
                if (carteIdx == 0) {
                    view.afficherInfo("Achat annule.");
                } else if (carteIdx >= 1 && carteIdx <= (int)marche.getCartes().size()) {
                    if (acheterCarte(joueur, carteIdx - 1)) {
                        view.afficherResultatAction("Carte achetee avec succes!");
                    } else {
                        view.afficherErreur("Impossible d'acheter cette carte (pas assez d'or?).");
                    }
                } else {
                    view.afficherErreur("Choix invalide.");
                }
                break;
            }
            
            case 3: { // Attaquer
                if (joueur.getRessources().getCombat() <= 0) {
                    view.afficherErreur("Vous n'avez pas de points de combat!");
                    break;
                }
                
                // Afficher l'adversaire et les cibles
                std::cout << "\n=== Etat de l'adversaire ===" << std::endl;
                view.afficherEtatJoueur(adversaire);
                view.afficherListeCibles(adversaire);
                
                int cibleIdx;
                if (compterGardesEnJeu(adversaire) > 0) {
                    cibleIdx = view.demanderChoix("Quel garde attaquer? (0 pour annuler)", 0, adversaire.getChampionsEnJeu().size());
                } else {
                    cibleIdx = view.demanderChoix("Quelle cible attaquer? (0=joueur, autre pour annuler)", 0, adversaire.getChampionsEnJeu().size());
                }
                
                if (cibleIdx == 0) {
                    // Annulation si des gardes sont présents
                    if (compterGardesEnJeu(adversaire) > 0) {
                        view.afficherInfo("Action annulee.");
                    } else {
                        // Attaquer le joueur directement
                        if (attaquer(joueur, adversaire, -1)) {
                            view.afficherResultatAction("Joueur adverse attaque!");
                            std::cout << "\n";
                            view.afficherEtatJoueur(adversaire);
                        }
                    }
                } else if (cibleIdx >= 1 && cibleIdx <= (int)adversaire.getChampionsEnJeu().size()) {
                    // Attaquer un champion
                    if (attaquer(joueur, adversaire, cibleIdx - 1)) {
                        view.afficherResultatAction("Champion attaque!");
                        std::cout << "\n";
                        view.afficherEtatJoueur(adversaire);
                    } else {
                        view.afficherErreur("Impossible d'attaquer ce champion.");
                    }
                } else {
                    view.afficherErreur("Choix invalide.");
                }
                break;
            }
            
            case 4: { // Activer un champion
                if (joueur.getChampionsEnJeu().empty()) {
                    view.afficherErreur("Vous n'avez pas de champions en jeu!");
                    break;
                }
                
                // Afficher les champions disponibles
                std::cout << "\n=== Champions en jeu ===" << std::endl;
                auto champions = joueur.getChampionsEnJeu();
                for (size_t i = 0; i < champions.size(); ++i) {
                    auto champ = champions[i];
                    std::cout << "  [" << (i+1) << "] " << champ->getNom() 
                              << " (" << champ->getPv() << " PV)";
                    if (champ->estActif()) std::cout << " [DEJA ACTIF]";
                    std::cout << std::endl;
                }
                
                int champIdx = view.demanderChoix("Quel champion activer? (0 pour annuler)", 0, joueur.getChampionsEnJeu().size());
                
                if (champIdx == 0) {
                    view.afficherInfo("Action annulee.");
                } else if (champIdx >= 1 && champIdx <= (int)joueur.getChampionsEnJeu().size()) {
                    if (activerChampion(joueur, champIdx - 1)) {
                        view.afficherResultatAction("Champion active!");
                    } else {
                        view.afficherErreur("Impossible d'activer ce champion (deja actif?).");
                    }
                } else {
                    view.afficherErreur("Choix invalide.");
                }
                break;
            }
            
            case 5: { // Fin du tour
                finTour = true;
                this->finTour(joueur);  // Utiliser this-> pour distinguer de la variable
                view.afficherInfo("Fin du tour.");
                break;
            }
            
            case 6: { // God-Mode
                activerGodMode(view, joueurIdx);
                break;
            }
            
            default:
                view.afficherErreur("Action inconnue.");
                break;
        }
    }
}

void GameController::initialiserPartie() {
    // Initialiser les decks des joueurs
    initialiserJoueur(joueur1);
    initialiserJoueur(joueur2);
    
    // Initialiser le marché
    initialiserMarche();
    
    tourActuel = 1;
    finie = false;
}

void GameController::initialiserJoueur(Joueur& joueur) {
    // Créer le deck de départ
    auto deck = HeroRealms::CreerDeckDepart();
    
    // Mélanger et ajouter au deck du joueur
    std::shuffle(deck.begin(), deck.end(), rng);
    for (auto& carte : deck) {
        joueur.getDeckMutable().ajouterCarte(carte);
    }
}

void GameController::initialiserMarche() {
    // Créer la pioche du marché
    piocheMarche = HeroRealms::CreerCartesBaseSet();
    auto fireGems = HeroRealms::CreerFireGems();
    piocheMarche.insert(piocheMarche.end(), fireGems.begin(), fireGems.end());
    
    // Initialiser le marché avec la pioche
    marche.initialiser(piocheMarche, rng);
}

void GameController::debutTour(Joueur& joueur) {
    // Piocher jusqu'à 5 cartes
    int cartesAPiocher = 5 - joueur.getMain().getCartes().size();
    if (cartesAPiocher > 0) {
        piocherCartes(joueur, cartesAPiocher);
    }
    
    // Réinitialiser les ressources
    joueur.reinitialiserRessources();
}

void GameController::finTour(Joueur& joueur) {
    // Défausser la main
    defausserMain(joueur);
    
    // Défausser les champions
    defausserChampions(joueur);
}

void GameController::piocherCartes(Joueur& joueur, int nombre) {
    for (int i = 0; i < nombre; ++i) {
        // Si le deck est vide et la défausse non vide, mélanger
        if (joueur.getDeck().getCartes().empty() && !joueur.getDefausse().getCartes().empty()) {
            // Récupérer toutes les cartes de la défausse
            auto cartesDefausse = joueur.getDefausse().getCartes();
            
            // Mélanger
            std::shuffle(cartesDefausse.begin(), cartesDefausse.end(), rng);
            
            // Vider la défausse
            while (!joueur.getDefausseMutable().getCartes().empty()) {
                joueur.getDefausseMutable().retirerCarte(0);
            }
            
            // Remettre dans le deck
            for (auto& carte : cartesDefausse) {
                joueur.getDeckMutable().ajouterCarte(carte);
            }
        }
        
        // Piocher du deck si possible
        if (!joueur.getDeck().getCartes().empty()) {
            auto carte = joueur.getDeck().getCarte(joueur.getDeck().getCartes().size() - 1);
            joueur.getDeckMutable().retirerCarte(joueur.getDeck().getCartes().size() - 1);
            joueur.getMainMutable().ajouterCarte(carte);
        }
    }
}

bool GameController::jouerCarte(Joueur& joueur, int carteIdx) {
    if (carteIdx < 0 || carteIdx >= (int)joueur.getMain().getCartes().size()) {
        return false;
    }
    
    auto carte = joueur.getMain().getCarte(carteIdx);
    
    // Compter la faction jouée
    auto faction = carte->getFaction();
    joueur.ajouterFactionJouee(faction);
    bool estAllie = verifierAllie(joueur, faction);
    
    // Appliquer les effets de la carte
    appliquerEffetsCarte(joueur, carte, estAllie);
    
    // Si c'est un champion, le mettre en jeu
    if (carte->getType() == "champion") {
        auto champ = std::dynamic_pointer_cast<Cartes::Champion>(carte);
        if (champ) {
            joueur.ajouterChampion(champ);
        }
    } else {
        // Sinon, défausser
        joueur.getDefausseMutable().ajouterCarte(carte);
    }
    
    // Retirer de la main
    joueur.getMainMutable().retirerCarte(carteIdx);
    
    return true;
}

void GameController::appliquerEffetsCarte(Joueur& joueur, std::shared_ptr<Cartes::Carte> carte, bool estAllie) {
    const auto& effets = carte->getEffets();
    
    for (const auto& effet : effets) {
        // Vérifier l'activation
        std::string activation = effet.getActivation();
        
        if (activation == "immediate") {
            appliquerEffet(joueur, effet, carte);
        }
        else if (activation == "ally" && estAllie) {
            appliquerEffet(joueur, effet, carte);
        }
        // expend et sacrifice sont gérés ailleurs
    }
}

void GameController::appliquerEffet(Joueur& joueur, const Systeme::Effet& effet, std::shared_ptr<Cartes::Carte> carte) {
    std::string type = effet.getType();
    int valeur = effet.getValeur();
    std::string conditionValeur = effet.getConditionValeur();
    
    if (type == "or") {
        joueur.ajouterOr(valeur);
    }
    else if (type == "combat") {
        joueur.ajouterCombat(valeur);
    }
    else if (type == "soin") {
        joueur.ajouterPv(valeur);
    }
    else if (type == "pioche") {
        piocherCartes(joueur, valeur);
    }
    else if (type == "choix") {
        gererEffetChoix(joueur, carte);
    }
    else if (type == "sacrifice") {
        // Effet de sacrifice : demander quelle carte sacrifier
        if (!joueur.getMain().getCartes().empty()) {
            std::cout << "\nSacrifier une carte de votre main:" << std::endl;
            auto main = joueur.getMain().getCartes();
            for (size_t i = 0; i < main.size(); ++i) {
                std::cout << "  [" << (i+1) << "] " << main[i]->getNom() << std::endl;
            }
            std::cout << "Choix (0 pour annuler): ";
            int choix;
            std::cin >> choix;
            
            if (choix > 0 && choix <= (int)main.size()) {
                auto carteSacrifiee = main[choix-1];
                joueur.getMainMutable().retirerCarte(choix-1);
                
                // Appliquer les effets "sacrifice" de la carte sacrifiée
                for (const auto& effetSacrifice : carteSacrifiee->getEffets()) {
                    if (effetSacrifice.getActivation() == "sacrifice") {
                        appliquerEffet(joueur, effetSacrifice, carteSacrifiee);
                    }
                }
                
                // Défausser la carte sacrifiée
                joueur.getDefausseMutable().ajouterCarte(carteSacrifiee);
                
                // Effet bonus pour avoir sacrifié (selon la carte qui demande le sacrifice)
                if (valeur > 0) {
                    // Par exemple: Fire Bomb donne +5 combat si on sacrifie
                    joueur.ajouterCombat(valeur);
                }
            }
        }
    }
    else if (type == "stun") {
        // Effet Stun : étourdir un champion adverse (le rendre inactif)
        // Pour l'instant, on ne fait rien (nécessite l'adversaire en paramètre)
        std::cout << "  -> Effet Stun disponible (non implémenté dans cette version)" << std::endl;
    }
    else if (type == "prepare") {
        // Effet Prepare : préparer un champion (il peut être utilisé plusieurs fois)
        if (carte->getType() == "champion") {
            auto champ = std::dynamic_pointer_cast<Cartes::Champion>(carte);
            if (champ) {
                champ->desactiver(); // Le champion peut être réactivé
                std::cout << "  -> Champion préparé (peut être réutilisé)" << std::endl;
            }
        }
    }
    else if (type == "defausse_adversaire") {
        // Effet : l'adversaire défausse des cartes
        // Nécessite l'adversaire en paramètre (non disponible ici)
        std::cout << "  -> L'adversaire doit défausser " << valeur << " carte(s)" << std::endl;
        std::cout << "     (À implémenter avec accès à l'adversaire)" << std::endl;
    }
    
    // Gestion des effets avec conditions spéciales
    if (!conditionValeur.empty() && conditionValeur != "aucune") {
        // Effets conditionnels (par exemple : +X par champion, +X par carte de faction)
        if (conditionValeur == "per_champion") {
            int bonus = compterChampionsEnJeu(joueur) * valeur;
            if (type == "or") {
                joueur.ajouterOr(bonus);
            } else if (type == "combat") {
                joueur.ajouterCombat(bonus);
            } else if (type == "soin") {
                joueur.ajouterPv(bonus);
            }
        }
        else if (conditionValeur == "IMPERIAL" || conditionValeur == "GUILD" || 
                 conditionValeur == "NECROS" || conditionValeur == "WILD") {
            // Bonus selon le nombre de cartes d'une faction
            Systeme::FactionType faction;
            if (conditionValeur == "IMPERIAL") faction = Systeme::FactionType::IMPERIAL;
            else if (conditionValeur == "GUILD") faction = Systeme::FactionType::GUILD;
            else if (conditionValeur == "NECROS") faction = Systeme::FactionType::NECROS;
            else faction = Systeme::FactionType::WILD;
            
            int count = compterCartesFaction(joueur, faction);
            int bonus = count * valeur;
            
            if (type == "or") {
                joueur.ajouterOr(bonus);
            } else if (type == "combat") {
                joueur.ajouterCombat(bonus);
            } else if (type == "soin") {
                joueur.ajouterPv(bonus);
            }
        }
    }
}

void GameController::gererEffetChoix(Joueur& joueur, std::shared_ptr<Cartes::Carte> carte) {
    // Effets spécifiques par carte nécessitant un choix
    std::string nom = carte->getNom();
    
    if (nom == "Darian, War Mage") {
        // Choix: +3 combat OU +4 soin
        std::cout << "\n[" << nom << "] Choisissez:" << std::endl;
        std::cout << "  1) +3 Combat" << std::endl;
        std::cout << "  2) +4 Soin" << std::endl;
        std::cout << "Choix: ";
        int choix;
        std::cin >> choix;
        if (choix == 1) {
            joueur.ajouterCombat(3);
            std::cout << "  -> +3 Combat" << std::endl;
        } else {
            joueur.ajouterPv(4);
            std::cout << "  -> +4 Soin" << std::endl;
        }
    }
    else if (nom == "Street Thug") {
        // Choix: +1 or OU +2 combat
        std::cout << "\n[" << nom << "] Choisissez:" << std::endl;
        std::cout << "  1) +1 Or" << std::endl;
        std::cout << "  2) +2 Combat" << std::endl;
        std::cout << "Choix: ";
        int choix;
        std::cin >> choix;
        if (choix == 1) {
            joueur.ajouterOr(1);
            std::cout << "  -> +1 Or" << std::endl;
        } else {
            joueur.ajouterCombat(2);
            std::cout << "  -> +2 Combat" << std::endl;
        }
    }
    else if (nom == "Cult Priest") {
        // Choix: +1 or OU +1 combat
        std::cout << "\n[" << nom << "] Choisissez:" << std::endl;
        std::cout << "  1) +1 Or" << std::endl;
        std::cout << "  2) +1 Combat" << std::endl;
        std::cout << "Choix: ";
        int choix;
        std::cin >> choix;
        if (choix == 1) {
            joueur.ajouterOr(1);
            std::cout << "  -> +1 Or" << std::endl;
        } else {
            joueur.ajouterCombat(1);
            std::cout << "  -> +1 Combat" << std::endl;
        }
    }
    else if (nom == "Tithe Priest") {
        // Choix: +1 or OU +1 soin par champion
        int nbChampions = compterChampionsEnJeu(joueur);
        std::cout << "\n[" << nom << "] Choisissez:" << std::endl;
        std::cout << "  1) +1 Or" << std::endl;
        std::cout << "  2) +" << nbChampions << " Soin (1 par champion)" << std::endl;
        std::cout << "Choix: ";
        int choix;
        std::cin >> choix;
        if (choix == 1) {
            joueur.ajouterOr(1);
            std::cout << "  -> +1 Or" << std::endl;
        } else {
            joueur.ajouterPv(nbChampions);
            std::cout << "  -> +" << nbChampions << " Soin" << std::endl;
        }
    }
    else if (nom == "Master Weaver") {
        // Choix: +3 or OU piocher 3 cartes
        std::cout << "\n[" << nom << "] Choisissez:" << std::endl;
        std::cout << "  1) +3 Or" << std::endl;
        std::cout << "  2) Piocher 3 cartes" << std::endl;
        std::cout << "Choix: ";
        int choix;
        std::cin >> choix;
        if (choix == 1) {
            joueur.ajouterOr(3);
            std::cout << "  -> +3 Or" << std::endl;
        } else {
            piocherCartes(joueur, 3);
            std::cout << "  -> Piocher 3 cartes" << std::endl;
        }
    }
    else if (nom == "Shadow Chain") {
        // Choix: +5 combat OU sacrifier une carte pour +7 combat
        std::cout << "\n[" << nom << "] Choisissez:" << std::endl;
        std::cout << "  1) +5 Combat" << std::endl;
        std::cout << "  2) Sacrifier une carte pour +7 Combat" << std::endl;
        std::cout << "Choix: ";
        int choix;
        std::cin >> choix;
        if (choix == 1) {
            joueur.ajouterCombat(5);
            std::cout << "  -> +5 Combat" << std::endl;
        } else {
            auto main = joueur.getMain().getCartes();
            if (!main.empty()) {
                std::cout << "\nQuelle carte sacrifier?" << std::endl;
                for (size_t i = 0; i < main.size(); ++i) {
                    std::cout << "  [" << (i+1) << "] " << main[i]->getNom() << std::endl;
                }
                std::cout << "Choix: ";
                int carteSacrifice;
                std::cin >> carteSacrifice;
                
                if (carteSacrifice > 0 && carteSacrifice <= (int)main.size()) {
                    auto carteSacrifiee = main[carteSacrifice-1];
                    joueur.getMainMutable().retirerCarte(carteSacrifice-1);
                    joueur.getDefausseMutable().ajouterCarte(carteSacrifiee);
                    joueur.ajouterCombat(7);
                    std::cout << "  -> Sacrifice de " << carteSacrifiee->getNom() << ", +7 Combat" << std::endl;
                }
            } else {
                std::cout << "  -> Pas de carte à sacrifier, +5 Combat par défaut" << std::endl;
                joueur.ajouterCombat(5);
            }
        }
    }
    else if (nom == "Bloodletter") {
        // Choix: +4 combat OU +6 combat (et adversaire gagne 3 PV)
        std::cout << "\n[" << nom << "] Choisissez:" << std::endl;
        std::cout << "  1) +4 Combat" << std::endl;
        std::cout << "  2) +6 Combat (adversaire gagne 3 PV)" << std::endl;
        std::cout << "Choix: ";
        int choix;
        std::cin >> choix;
        if (choix == 1) {
            joueur.ajouterCombat(4);
            std::cout << "  -> +4 Combat" << std::endl;
        } else {
            joueur.ajouterCombat(6);
            std::cout << "  -> +6 Combat (adversaire gagnera 3 PV)" << std::endl;
            // Note: L'adversaire devrait gagner 3 PV, mais on n'a pas accès à lui ici
            // Cette logique devrait être gérée au niveau supérieur
        }
    }
    else {
        std::cout << "  -> Effet de choix non implémenté pour: " << nom << std::endl;
    }
}

int GameController::compterChampionsEnJeu(const Joueur& joueur) const {
    return joueur.getChampionsEnJeu().size();
}

int GameController::compterGardesEnJeu(const Joueur& joueur) const {
    int count = 0;
    for (const auto& champ : joueur.getChampionsEnJeu()) {
        if (champ->estGarde()) count++;
    }
    return count;
}

int GameController::compterCartesFaction(const Joueur& joueur, Systeme::FactionType faction) const {
    int count = 0;
    // Compter dans les champions en jeu
    for (const auto& champ : joueur.getChampionsEnJeu()) {
        if (champ->getFaction() == faction) count++;
    }
    return count;
}

bool GameController::verifierAllie(const Joueur& joueur, Systeme::FactionType faction) const {
    // Un allié est actif si on a déjà joué au moins une carte de cette faction ce tour
    const auto& factionsJouees = joueur.getFactionsJouees();
    auto it = factionsJouees.find(faction);
    return (it != factionsJouees.end() && it->second >= 2);
}

bool GameController::acheterCarte(Joueur& joueur, int marcheIdx) {
    if (marcheIdx < 0 || marcheIdx >= (int)marche.getCartes().size()) {
        return false;
    }
    
    auto carte = marche.getCartes()[marcheIdx];
    if (joueur.getRessources().getOr() < carte->getCout()) {
        return false;
    }
    
    // Acheter via la classe Marche
    auto carteAchetee = marche.acheter(marcheIdx);
    if (carteAchetee) {
        joueur.retirerOr(carte->getCout());
        joueur.getDefausseMutable().ajouterCarte(carteAchetee);
        
        // Remplir le marché
        marche.remplir(piocheMarche);
        return true;
    }
    
    return false;
}

bool GameController::activerChampion(Joueur& joueur, int championIdx) {
    if (championIdx < 0 || championIdx >= (int)joueur.getChampionsEnJeu().size()) {
        return false;
    }
    
    auto champ = joueur.getChampionsEnJeu()[championIdx];
    
    // Activer le champion (applique les effets "expend")
    champ->activer();
    
    // Appliquer les effets "expend"
    for (const auto& effet : champ->getEffets()) {
        if (effet.getActivation() == "expend") {
            // Vérifier si c'est un effet ally
            if (effet.getConditionType() == "ally") {
                if (verifierAllie(joueur, champ->getFaction())) {
                    appliquerEffet(joueur, effet, champ);
                }
            } else {
                appliquerEffet(joueur, effet, champ);
            }
        }
    }
    
    return true;
}

bool GameController::attaquer(Joueur& attaquant, Joueur& defenseur, int cibleIdx) {
    if (attaquant.getRessources().getCombat() <= 0) {
        return false;
    }
    
    // Vérifier les gardes
    std::vector<int> gardesIdx;
    for (size_t i = 0; i < defenseur.getChampionsEnJeu().size(); ++i) {
        if (defenseur.getChampionsEnJeu()[i]->estGarde()) {
            gardesIdx.push_back(i);
        }
    }
    
    if (!gardesIdx.empty() && cibleIdx != -1) {
        // On doit attaquer un garde
        bool estGarde = false;
        for (int idx : gardesIdx) {
            if (idx == cibleIdx) {
                estGarde = true;
                break;
            }
        }
        if (!estGarde) {
            return false; // Impossible d'attaquer autre chose qu'un garde
        }
    }
    
    int combat = attaquant.getRessources().getCombat();
    
    if (cibleIdx == -1) {
        // Attaque directe du joueur
        if (!gardesIdx.empty()) {
            return false; // Il y a des gardes, on ne peut pas attaquer directement
        }
        defenseur.retirerPv(combat);
        attaquant.retirerCombat(combat);
        
        if (defenseur.getPv() <= 0) {
            finie = true;
        }
    } else {
        // Attaque d'un champion
        if (cibleIdx < 0 || cibleIdx >= (int)defenseur.getChampionsEnJeu().size()) {
            return false;
        }
        
        auto champCible = defenseur.getChampionsEnJeu()[cibleIdx];
        champCible->subirDegats(combat);
        attaquant.retirerCombat(combat);
        
        if (champCible->getPv() <= 0) {
            // Champion détruit
            defenseur.getDefausseMutable().ajouterCarte(champCible);
            defenseur.retirerChampion(cibleIdx);
        }
    }
    
    return true;
}

void GameController::defausserMain(Joueur& joueur) {
    auto main = joueur.getMain().getCartes();
    for (auto& carte : main) {
        joueur.getDefausseMutable().ajouterCarte(carte);
    }
    
    // Vider la main
    while (!joueur.getMainMutable().getCartes().empty()) {
        joueur.getMainMutable().retirerCarte(0);
    }
}

void GameController::defausserChampions(Joueur& joueur) {
    auto champions = joueur.getChampionsEnJeu();
    for (auto& champ : champions) {
        champ->desactiver();
        joueur.getDefausseMutable().ajouterCarte(champ);
    }
    
    // Vider les champions
    while (!joueur.getChampionsEnJeu().empty()) {
        joueur.retirerChampion(0);
    }
}

bool GameController::partieFinie() const {
    return finie || joueur1.getPv() <= 0 || joueur2.getPv() <= 0;
}

int GameController::getVainqueur() const {
    if (joueur1.getPv() > 0) return 0;  // Joueur 1 (index 0)
    if (joueur2.getPv() > 0) return 1;  // Joueur 2 (index 1)
    return 0;
}

void GameController::gererDefausseAdversaire(Joueur& adversaire, int nombre) {
    if (adversaire.getMain().getCartes().empty()) {
        std::cout << "  -> L'adversaire n'a pas de cartes en main" << std::endl;
        return;
    }
    
    int cartesADefausser = std::min(nombre, (int)adversaire.getMain().getCartes().size());
    std::cout << "\n[Adversaire] Vous devez défausser " << cartesADefausser << " carte(s):" << std::endl;
    
    for (int i = 0; i < cartesADefausser; ++i) {
        auto main = adversaire.getMain().getCartes();
        if (main.empty()) break;
        
        std::cout << "\nCartes en main:" << std::endl;
        for (size_t j = 0; j < main.size(); ++j) {
            std::cout << "  [" << (j+1) << "] " << main[j]->getNom() << std::endl;
        }
        std::cout << "Quelle carte défausser? ";
        int choix;
        std::cin >> choix;
        
        if (choix > 0 && choix <= (int)main.size()) {
            auto carte = main[choix-1];
            adversaire.getDefausseMutable().ajouterCarte(carte);
            adversaire.getMainMutable().retirerCarte(choix-1);
            std::cout << "  -> " << carte->getNom() << " défaussé" << std::endl;
        }
    }
}

void GameController::gererStunChampion(Joueur& adversaire) {
    if (adversaire.getChampionsEnJeu().empty()) {
        std::cout << "  -> L'adversaire n'a pas de champions en jeu" << std::endl;
        return;
    }
    
    std::cout << "\n[Stun] Choisissez un champion adverse à étourdir:" << std::endl;
    auto champions = adversaire.getChampionsEnJeu();
    for (size_t i = 0; i < champions.size(); ++i) {
        auto champ = champions[i];
        std::cout << "  [" << (i+1) << "] " << champ->getNom() 
                  << " (" << champ->getPv() << " PV)" << std::endl;
    }
    std::cout << "Choix (0 pour annuler): ";
    int choix;
    std::cin >> choix;
    
    if (choix > 0 && choix <= (int)champions.size()) {
        auto champ = champions[choix-1];
        champ->activer(); // Marquer comme utilisé (ne peut pas utiliser son effet expend ce tour)
        std::cout << "  -> " << champ->getNom() << " est étourdi (ne peut pas utiliser son pouvoir)" << std::endl;
    }
}

void GameController::appliquerEffetAvecAdversaire(Joueur& joueur, Joueur& adversaire, 
                                                   const Systeme::Effet& effet, 
                                                   std::shared_ptr<Cartes::Carte> carte) {
    std::string type = effet.getType();
    int valeur = effet.getValeur();
    
    if (type == "defausse_adversaire") {
        gererDefausseAdversaire(adversaire, valeur);
    }
    else if (type == "stun") {
        gererStunChampion(adversaire);
    }
    else {
        // Pour les autres effets, utiliser la méthode normale
        appliquerEffet(joueur, effet, carte);
    }
}

// ==================== GOD-MODE ====================

void GameController::activerGodMode(GameView& view, int joueurIdx) {
    auto& joueur = getJoueurMutable(joueurIdx);
    auto& adversaire = getJoueurMutable(1 - joueurIdx);
    
    view.afficherMenuGodMode();
    
    int choix;
    std::cin >> choix;
    
    switch (choix) {
        case 1: { // Modifier PV du joueur actuel
            int nouveauxPV = view.demanderChoix("Nouveaux PV pour vous", 1, 999);
            modifierPV(joueur, nouveauxPV);
            view.afficherResultatAction("PV modifies!");
            break;
        }
        
        case 2: { // Modifier PV de l'adversaire
            int nouveauxPV = view.demanderChoix("Nouveaux PV pour l'adversaire", 1, 999);
            modifierPV(adversaire, nouveauxPV);
            view.afficherResultatAction("PV de l'adversaire modifies!");
            break;
        }
        
        case 3: { // Acheter depuis toute la pioche
            if (piocheMarche.empty()) {
                view.afficherErreur("La pioche du marche est vide!");
                break;
            }
            
            std::cout << "\n";
            view.afficherPiocheComplete(piocheMarche);
            
            int carteIdx = view.demanderChoix("Quelle carte acheter? (0 pour annuler)", 0, piocheMarche.size());
            
            if (carteIdx == 0) {
                view.afficherInfo("Achat annule.");
            } else if (carteIdx >= 1 && carteIdx <= (int)piocheMarche.size()) {
                acheterDePioche(joueur, carteIdx - 1);
                view.afficherResultatAction("Carte ajoutee directement a votre main!");
            } else {
                view.afficherErreur("Choix invalide.");
            }
            break;
        }
        
        case 4: { // Toggle God-Mode
            toggleGodMode();
            view.afficherGodModeActif(godModeActif);
            break;
        }
        
        case 0: { // Retour
            view.afficherInfo("Retour au jeu.");
            break;
        }
        
        default:
            view.afficherErreur("Option invalide.");
            break;
    }
}

void GameController::modifierPV(Joueur& joueur, int nouveauxPV) {
    joueur.setPv(nouveauxPV);
}

void GameController::acheterDePioche(Joueur& joueur, int carteIdx) {
    if (carteIdx >= 0 && carteIdx < (int)piocheMarche.size()) {
        auto carte = piocheMarche[carteIdx];
        
        // Retirer de la pioche
        piocheMarche.erase(piocheMarche.begin() + carteIdx);
        
        // Ajouter directement à la main (au lieu de la défausse)
        joueur.getMainMutable().ajouterCarte(carte);
        
        std::cout << "  -> Carte '" << carte->getNom() << "' ajoutee a votre main!" << std::endl;
    }
}

} // namespace Game::Core
