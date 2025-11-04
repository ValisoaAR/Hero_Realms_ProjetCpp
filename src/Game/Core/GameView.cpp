#include "../../../include/Game/Core/GameView.hpp"
#include "../../../include/Game/Core/Joueur.hpp"
#include "../../../include/Game/Cartes/Champion.hpp"
#include "../../../include/Game/Utils/Couleurs.hpp"
#include <iostream>
#include <iomanip>

using namespace Game::Utils::Couleurs;

namespace Game::Core {

// Fonction helper pour obtenir le symbole et la couleur de la faction
static std::string obtenirSymboleFaction(Systeme::FactionType faction) {
    switch(faction) {
        case Systeme::FactionType::IMPERIAL:
            return BLEU + "[IMPERIAL]" + RESET;
        case Systeme::FactionType::GUILD:
            return JAUNE + "[GUILD]" + RESET;
        case Systeme::FactionType::NECROS:
            return MAGENTA + "[NECROS]" + RESET;
        case Systeme::FactionType::WILD:
            return VERT + "[WILD]" + RESET;
        case Systeme::FactionType::NEUTRAL:
            return ""; // Pas d'affichage pour neutre
        default:
            return "";
    }
}

void GameView::afficherTitre() const {
    afficherSeparateur();
    std::cout << TITRE << "   Hero Realms - Partie a 2 joueurs   " << RESET << std::endl;
    afficherSeparateur();
}

void GameView::afficherDebut() const {
    std::cout << "\n";
    afficherSeparateur();
    std::cout << "         Debut de la partie !           " << std::endl;
    afficherSeparateur();
}

void GameView::afficherFinPartie(const std::string& nomVainqueur, int pvRestants) const {
    std::cout << "\n";
    afficherSeparateur();
    std::cout << TITRE << "          FIN DE LA PARTIE !            " << RESET << std::endl;
    afficherSeparateur();
    std::cout << SUCCES << "[VICTOIRE] " << RESET << GRAS << nomVainqueur << RESET 
              << " gagne avec " << VERT_CLAIR << pvRestants << " PV" << RESET << " restants!" << std::endl;
}

void GameView::afficherDebutTour(int tour, int joueurId) const {
    std::cout << "\n";
    afficherSeparateur();
    std::cout << "           TOUR " << tour << " - Joueur " << joueurId << std::endl;
    afficherSeparateur();
}

void GameView::afficherEtatJoueur(const Joueur& joueur) const {
    // Couleur selon le joueur
    std::string couleurJoueur = (joueur.getNom() == "Joueur 1") ? JOUEUR1 : 
                                (joueur.getNom() == "IA" || joueur.getNom() == "Joueur 2") ? JOUEUR2 : BLANC;
    
    std::cout << "\n" << couleurJoueur << "+--- " << joueur.getNom() << " --------------------+" << RESET << std::endl;
    std::cout << "| " << SOIN << "PV: " << RESET << std::setw(3) << joueur.getPv() 
              << " | " << OR << "Or: " << RESET << std::setw(2) << joueur.getRessources().getOr() 
              << " | " << COMBAT << "Combat: " << RESET << std::setw(2) << joueur.getRessources().getCombat() << std::endl;
    
    auto main = joueur.getMain().getCartes();
    std::cout << "| Main (" << main.size() << "):" << std::endl;
    for (size_t i = 0; i < main.size(); ++i) {
        auto carte = main[i];
        std::string symboleFaction = obtenirSymboleFaction(carte->getFaction());
        std::cout << "|   [" << (i+1) << "] " << GRAS << carte->getNom() << RESET;
        if (!symboleFaction.empty()) {
            std::cout << " " << symboleFaction;
        }
        std::cout << " (Cout: " << OR << carte->getCout() << RESET << ")" << std::endl;
        afficherEffetsCarte(*carte);
    }
    
    auto champions = joueur.getChampionsEnJeu();
    if (!champions.empty()) {
        std::cout << "| Champions en jeu (" << champions.size() << "):" << std::endl;
        for (size_t i = 0; i < champions.size(); ++i) {
            auto champ = champions[i];
            std::string symboleFaction = obtenirSymboleFaction(champ->getFaction());
            std::cout << "|   [" << (i+1) << "] " << CHAMPION << GRAS << champ->getNom() << RESET;
            if (!symboleFaction.empty()) {
                std::cout << " " << symboleFaction;
            }
            std::cout << " (" << SOIN << champ->getPv() << "PV" << RESET;
            if (champ->estGarde()) std::cout << "," << ROUGE << "GARDE" << RESET;
            if (champ->estActif()) std::cout << "," << VERT << "ACTIF" << RESET;
            std::cout << ")" << std::endl;
            afficherEffetsCarte(*champ);
        }
    }
    
    std::cout << "| Deck: " << joueur.getDeck().getCartes().size() 
              << " | Defausse: " << joueur.getDefausse().getCartes().size() << std::endl;
    std::cout << "+--------------------------------+" << std::endl;
}

void GameView::afficherEtatAdversaire(const Joueur& adversaire) const {
    // Couleur selon l'adversaire
    std::string couleurAdv = (adversaire.getNom() == "Joueur 1") ? JOUEUR1 : JOUEUR2;
    
    std::cout << "\n" << couleurAdv << "+--- " << adversaire.getNom() << " --------------------+" << RESET << std::endl;
    std::cout << "| " << SOIN << "PV: " << RESET << std::setw(3) << adversaire.getPv() << std::endl;
    std::cout << "| Cartes en main: " << adversaire.getMain().getCartes().size() << std::endl;
    
    auto champions = adversaire.getChampionsEnJeu();
    if (!champions.empty()) {
        std::cout << "| Champions en jeu (" << champions.size() << "):" << std::endl;
        for (size_t i = 0; i < champions.size(); ++i) {
            auto champ = champions[i];
            std::cout << "|   [" << (i+1) << "] " << champ->getNom() 
                      << " (" << champ->getPv() << "PV";
            if (champ->estGarde()) std::cout << ",GARDE";
            if (champ->estActif()) std::cout << ",ACTIF";
            std::cout << ")" << std::endl;
        }
    } else {
        std::cout << "| Aucun champion en jeu" << std::endl;
    }
    
    std::cout << "| Deck: " << adversaire.getDeck().getCartes().size() 
              << " | Defausse: " << adversaire.getDefausse().getCartes().size() << std::endl;
    std::cout << "+--------------------------------+" << std::endl;
}

void GameView::afficherMarche(const Zones::Marche& marche) const {
    std::cout << "\n" << MARCHE << "[Marche] Cartes disponibles:" << RESET << std::endl;
    auto cartes = marche.getCartes();
    for (size_t i = 0; i < cartes.size(); ++i) {
        auto carte = cartes[i];
        std::string symboleFaction = obtenirSymboleFaction(carte->getFaction());
        
        std::cout << MARCHE << "  [" << (i+1) << "] " << GRAS << carte->getNom() << RESET;
        if (!symboleFaction.empty()) {
            std::cout << " " << symboleFaction;
        }
        std::cout << " (Cout: " << OR << carte->getCout() << " or" << RESET << ")";
        
        if (carte->getType() == "champion") {
            auto champ = std::dynamic_pointer_cast<Cartes::Champion>(carte);
            if (champ) {
                std::cout << " " << CHAMPION << "[Champion " << SOIN << champ->getPv() << "PV" << RESET;
                if (champ->estGarde()) std::cout << " " << ROUGE << "GARDE" << RESET;
                std::cout << CHAMPION << "]" << RESET;
            }
        }
        std::cout << std::endl;
        afficherEffetsCarte(*carte);
    }
}

void GameView::afficherMarcheAvecOr(const Zones::Marche& marche, const Joueur& joueur) const {
    afficherMarche(marche);
    std::cout << "\n" << OR << "Or disponible: " << joueur.getRessources().getOr() << " gold" << RESET << std::endl;
}

void GameView::afficherMenuPrincipal() const {
    std::cout << "\n[Actions] Que voulez-vous faire?" << std::endl;
    std::cout << "  1. Jouer carte(s) de votre main" << std::endl;
    std::cout << "  2. Acheter une carte" << std::endl;
    std::cout << "  3. Attaquer (champions/joueur adverse)" << std::endl;
    std::cout << "  4. Activer un champion" << std::endl;
    std::cout << "  5. Sacrifier une carte pour son effet" << std::endl;
    std::cout << "  6. Fin du tour" << std::endl;
    std::cout << "  7. [GOD-MODE] Triche" << std::endl;
    std::cout << "Choix: ";
}

void GameView::afficherMenuAchat(const Joueur& joueur, int nbFireGemsRestantes) const {
    std::cout << "\n" << MARCHE << "=== MENU ACHAT ===" << RESET << std::endl;
    std::cout << "  1. Acheter depuis le marche" << std::endl;
    std::cout << "  2. Acheter une Fire Gem (2 gold) - " << ROUGE << nbFireGemsRestantes << " restantes" << RESET << std::endl;
    std::cout << "  0. Annuler" << std::endl;
    std::cout << "\n" << OR << "Or disponible: " << joueur.getRessources().getOr() << " gold" << RESET << std::endl;
    std::cout << "Choix: ";
}

void GameView::afficherResultatAction(const std::string& message) const {
    std::cout << SUCCES << "[OK] " << RESET << message << std::endl;
}

void GameView::afficherErreur(const std::string& message) const {
    std::cout << ERREUR << "[X] " << RESET << message << std::endl;
}

void GameView::afficherInfo(const std::string& message) const {
    std::cout << INFO << "[INFO] " << RESET << message << std::endl;
}

void GameView::afficherEffet(const std::string& typeEffet, int valeur) const {
    std::cout << "  -> ";
    if (typeEffet == "or") {
        std::cout << OR << "+" << valeur << " Or" << RESET;
    } else if (typeEffet == "combat") {
        std::cout << COMBAT << "+" << valeur << " Combat" << RESET;
    } else if (typeEffet == "soin") {
        std::cout << SOIN << "+" << valeur << " PV" << RESET;
    } else if (typeEffet == "pioche") {
        std::cout << CYAN << "Pioche " << valeur << " carte(s)" << RESET;
    } else {
        std::cout << typeEffet << " (" << valeur << ")";
    }
    std::cout << std::endl;
}

void GameView::afficherEffetsCarte(const Cartes::Carte& carte) const {
    const auto& effets = carte.getEffets();
    
    if (effets.empty()) {
        return;
    }
    
    for (const auto& effet : effets) {
        std::cout << "      ";
        
        // Afficher le préfixe selon l'activation
        if (effet.getActivation() == "ally") {
            std::cout << "[ALLIE] ";
        } else if (effet.getActivation() == "sacrifice") {
            std::cout << "[SACRIFICE] ";
        } else if (effet.getActivation() == "expend") {
            std::cout << "[EXPEND] ";
        }
        
        // Afficher l'effet principal
        if (effet.getType() == "or") {
            std::cout << OR << "+" << effet.getValeur() << " Or" << RESET;
        } else if (effet.getType() == "combat") {
            std::cout << COMBAT << "+" << effet.getValeur() << " Combat" << RESET;
        } else if (effet.getType() == "soin") {
            std::cout << SOIN << "+" << effet.getValeur() << " PV (soin)" << RESET;
        } else if (effet.getType() == "pioche") {
            std::cout << CYAN << "Pioche " << effet.getValeur() << " carte(s)" << RESET;
        } else if (effet.getType() == "sacrifice") {
            std::cout << "Sacrifier une carte";
        } else if (effet.getType() == "stun") {
            std::cout << "Etourdir un champion";
        } else if (effet.getType() == "prepare") {
            std::cout << "Preparer un champion";
        } else if (effet.getType() == "defausse_adversaire") {
            std::cout << ROUGE << "Adversaire defausse " << effet.getValeur() << " carte(s)" << RESET;
        } else if (effet.getType() == "choix") {
            // Afficher les choix disponibles selon la carte
            std::string nom = carte.getNom();
            if (nom == "Darian, War Mage") {
                std::cout << JAUNE_CLAIR << "Choix: +3 Combat OU +4 Soin" << RESET;
            } else if (nom == "Street Thug") {
                std::cout << JAUNE_CLAIR << "Choix: +1 Or OU +2 Combat" << RESET;
            } else if (nom == "Cult Priest") {
                std::cout << JAUNE_CLAIR << "Choix: +1 Or OU +1 Combat" << RESET;
            } else if (nom == "Tithe Priest") {
                std::cout << JAUNE_CLAIR << "Choix: +1 Or OU +X Soin (1 par champion)" << RESET;
            } else if (nom == "Master Weaver") {
                std::cout << JAUNE_CLAIR << "Choix: +3 Or OU Piocher 3 cartes" << RESET;
            } else if (nom == "Shadow Chain") {
                std::cout << JAUNE_CLAIR << "Choix: +5 Combat OU Sacrifier une carte pour +7 Combat" << RESET;
            } else if (nom == "Bloodletter") {
                std::cout << JAUNE_CLAIR << "Choix: +4 Combat OU +6 Combat (adversaire gagne 3 PV)" << RESET;
            } else {
                std::cout << JAUNE_CLAIR << "Choix d'effet" << RESET;
            }
        } else {
            std::cout << effet.getType() << " (" << effet.getValeur() << ")";
        }
        
        // Afficher la condition si présente
        if (effet.getConditionType() == "ally") {
            std::string factionColor = RESET;
            std::string faction = effet.getConditionValeur();
            
            // Choisir la couleur selon la faction
            if (faction == "GUILD") {
                factionColor = GUILD;
            } else if (faction == "IMPERIAL") {
                factionColor = IMPERIAL;
            } else if (faction == "NECROS") {
                factionColor = NECROS;
            } else if (faction == "WILD") {
                factionColor = WILD;
            }
            
            std::cout << " (si allie " << factionColor << faction << RESET << ")";
        } else if (effet.getConditionType() == "per_champion") {
            std::cout << " (par champion en jeu)";
        }
        
        std::cout << std::endl;
    }
}

void GameView::afficherAllieActive(Systeme::FactionType faction) const {
    std::cout << "  [**] ALLIE active! (faction ";
    switch(faction) {
        case Systeme::FactionType::IMPERIAL: std::cout << "IMPERIAL"; break;
        case Systeme::FactionType::GUILD: std::cout << "GUILD"; break;
        case Systeme::FactionType::NECROS: std::cout << "NECROS"; break;
        case Systeme::FactionType::WILD: std::cout << "WILD"; break;
        default: std::cout << "NEUTRAL"; break;
    }
    std::cout << ")" << std::endl;
}

void GameView::afficherChampionEnJeu(const std::string& nom, bool garde) const {
    std::cout << "  -> " << CHAMPION << "Champion mis en jeu: " << GRAS << nom << RESET;
    if (garde) {
        std::cout << ROUGE << " (GARDE)" << RESET;
    }
    std::cout << std::endl;
}

void GameView::afficherAttaque(const std::string& cible, int degats) const {
    std::cout << COMBAT << "[ATK]" << RESET << " Vous attaquez " << ROUGE << cible 
              << RESET << " (" << COMBAT << "-" << degats << " PV" << RESET << ")" << std::endl;
}

void GameView::afficherMortChampion(const std::string& nom) const {
    std::cout << "  [MORT] Champion detruit: " << nom << std::endl;
}

void GameView::afficherListeCibles(const Joueur& defenseur) const {
    std::cout << "\nCibles disponibles:" << std::endl;
    
    // Vérifier s'il y a des gardes
    bool aDesGardes = false;
    for (const auto& champ : defenseur.getChampionsEnJeu()) {
        if (champ->estGarde()) {
            aDesGardes = true;
            break;
        }
    }
    
    if (aDesGardes) {
        std::cout << "[!] L'adversaire a des champions avec GARDE!" << std::endl;
        std::cout << "Vous devez d'abord detruire les gardes:" << std::endl;
        auto champions = defenseur.getChampionsEnJeu();
        for (size_t i = 0; i < champions.size(); ++i) {
            auto champ = champions[i];
            if (champ->estGarde()) {
                std::cout << "  [" << (i+1) << "] " << champ->getNom() 
                          << " (" << champ->getPv() << " PV)" << std::endl;
            }
        }
    } else {
        std::cout << "  [0] Le joueur adverse directement" << std::endl;
        auto champions = defenseur.getChampionsEnJeu();
        for (size_t i = 0; i < champions.size(); ++i) {
            auto champ = champions[i];
            std::cout << "  [" << (i+1) << "] Champion: " << champ->getNom() 
                      << " (" << champ->getPv() << " PV)" << std::endl;
        }
    }
}

int GameView::demanderChoix(const std::string& question, int min, int max) const {
    std::cout << question << " (" << min << "-" << max << "): ";
    int choix;
    std::cin >> choix;
    return choix;
}

bool GameView::demanderConfirmation(const std::string& question) const {
    std::cout << question << " (o/n): ";
    char reponse;
    std::cin >> reponse;
    return (reponse == 'o' || reponse == 'O');
}

void GameView::afficherSeparateur() const {
    std::cout << "========================================" << std::endl;
}

void GameView::afficherLigne(const std::string& texte) const {
    std::cout << texte << std::endl;
}

// ==================== GOD-MODE ====================

void GameView::afficherMenuGodMode() const {
    std::cout << "\n";
    afficherSeparateur();
    std::cout << "          [GOD-MODE] Menu Triche        " << std::endl;
    afficherSeparateur();
    std::cout << "  1. Modifier vos PV" << std::endl;
    std::cout << "  2. Modifier les PV de l'adversaire" << std::endl;
    std::cout << "  3. Acheter une carte de toute la pioche (directement dans la main)" << std::endl;
    std::cout << "  4. Toggle God-Mode (ON/OFF)" << std::endl;
    std::cout << "  0. Retour au jeu" << std::endl;
    std::cout << "Choix: ";
}

void GameView::afficherPiocheComplete(const std::vector<std::shared_ptr<Cartes::Carte>>& pioche) const {
    std::cout << "\n[Pioche complete du marche] (" << pioche.size() << " cartes):" << std::endl;
    for (size_t i = 0; i < pioche.size(); ++i) {
        auto carte = pioche[i];
        std::string symboleFaction = obtenirSymboleFaction(carte->getFaction());
        
        std::cout << "  [" << (i+1) << "] " << GRAS << carte->getNom() << RESET;
        if (!symboleFaction.empty()) {
            std::cout << " " << symboleFaction;
        }
        std::cout << " (Cout: " << OR << carte->getCout() << " or" << RESET << ")";
        
        if (carte->getType() == "champion") {
            auto champ = std::dynamic_pointer_cast<Cartes::Champion>(carte);
            if (champ) {
                std::cout << " " << CHAMPION << "[Champion " << SOIN << champ->getPv() << "PV" << RESET;
                if (champ->estGarde()) std::cout << " " << ROUGE << "GARDE" << RESET;
                std::cout << CHAMPION << "]" << RESET;
            }
        }
        std::cout << std::endl;
        afficherEffetsCarte(*carte);
    }
}

void GameView::afficherGodModeActif(bool actif) const {
    if (actif) {
        std::cout << "\n[GOD-MODE] *** MODE TRICHE ACTIVE ***" << std::endl;
    } else {
        std::cout << "\n[GOD-MODE] Mode triche desactive." << std::endl;
    }
}

} // namespace Game::Core
