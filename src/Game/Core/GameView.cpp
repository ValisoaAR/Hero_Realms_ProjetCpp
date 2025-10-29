#include "../../../include/Game/Core/GameView.hpp"
#include "../../../include/Game/Core/Joueur.hpp"
#include "../../../include/Game/Cartes/Champion.hpp"
#include <iostream>
#include <iomanip>

namespace Game::Core {

void GameView::afficherTitre() const {
    afficherSeparateur();
    std::cout << "   Hero Realms - Partie a 2 joueurs   " << std::endl;
    afficherSeparateur();
}

void GameView::afficherDebut() const {
    std::cout << "\n";
    afficherSeparateur();
    std::cout << "         Debut de la partie !           " << std::endl;
    afficherSeparateur();
}

void GameView::afficherFinPartie(int vainqueur, int pvRestants) const {
    std::cout << "\n";
    afficherSeparateur();
    std::cout << "          FIN DE LA PARTIE !            " << std::endl;
    afficherSeparateur();
    std::cout << "[VICTOIRE] Joueur " << vainqueur << " gagne avec " 
              << pvRestants << " PV restants!" << std::endl;
}

void GameView::afficherDebutTour(int tour, int joueurId) const {
    std::cout << "\n";
    afficherSeparateur();
    std::cout << "           TOUR " << tour << " - Joueur " << joueurId << std::endl;
    afficherSeparateur();
}

void GameView::afficherEtatJoueur(const Joueur& joueur) const {
    std::cout << "\n+--- " << joueur.getNom() << " --------------------+" << std::endl;
    std::cout << "| PV: " << std::setw(3) << joueur.getPv() 
              << " | Or: " << std::setw(2) << joueur.getRessources().getOr() 
              << " | Combat: " << std::setw(2) << joueur.getRessources().getCombat() << std::endl;
    
    auto main = joueur.getMain().getCartes();
    std::cout << "| Main (" << main.size() << "): ";
    for (size_t i = 0; i < main.size(); ++i) {
        std::cout << "[" << (i+1) << "]" << main[i]->getNom() << " ";
    }
    
    auto champions = joueur.getChampionsEnJeu();
    std::cout << "\n| Champions (" << champions.size() << "): ";
    for (size_t i = 0; i < champions.size(); ++i) {
        auto champ = champions[i];
        std::cout << "[" << (i+1) << "]" << champ->getNom() << "(" << champ->getPv() << "PV";
        if (champ->estGarde()) std::cout << ",GARDE";
        if (champ->estActif()) std::cout << ",ACTIF";
        std::cout << ") ";
    }
    
    std::cout << "\n| Deck: " << joueur.getDeck().getCartes().size() 
              << " | Defausse: " << joueur.getDefausse().getCartes().size() << std::endl;
    std::cout << "+--------------------------------+" << std::endl;
}

void GameView::afficherMarche(const Zones::Marche& marche) const {
    std::cout << "\n[Marche] Cartes disponibles:" << std::endl;
    auto cartes = marche.getCartes();
    for (size_t i = 0; i < cartes.size(); ++i) {
        auto carte = cartes[i];
        std::cout << "  [" << (i+1) << "] " << carte->getNom() 
                  << " (Cout: " << carte->getCout() << " or)";
        
        if (carte->getType() == "champion") {
            auto champ = std::dynamic_pointer_cast<Cartes::Champion>(carte);
            if (champ) {
                std::cout << " [Champion " << champ->getPv() << "PV";
                if (champ->estGarde()) std::cout << " GARDE";
                std::cout << "]";
            }
        }
        std::cout << std::endl;
    }
}

void GameView::afficherMenuPrincipal() const {
    std::cout << "\n[Actions] Que voulez-vous faire?" << std::endl;
    std::cout << "  1. Jouer carte(s) de votre main" << std::endl;
    std::cout << "  2. Acheter une carte du marche" << std::endl;
    std::cout << "  3. Attaquer (champions/joueur adverse)" << std::endl;
    std::cout << "  4. Activer un champion" << std::endl;
    std::cout << "  5. Fin du tour" << std::endl;
    std::cout << "  6. [GOD-MODE] Triche" << std::endl;
    std::cout << "Choix: ";
}

void GameView::afficherResultatAction(const std::string& message) const {
    std::cout << "[OK] " << message << std::endl;
}

void GameView::afficherErreur(const std::string& message) const {
    std::cout << "[X] " << message << std::endl;
}

void GameView::afficherInfo(const std::string& message) const {
    std::cout << "[INFO] " << message << std::endl;
}

void GameView::afficherEffet(const std::string& typeEffet, int valeur) const {
    std::cout << "  -> ";
    if (typeEffet == "or") {
        std::cout << "+" << valeur << " Or";
    } else if (typeEffet == "combat") {
        std::cout << "+" << valeur << " Combat";
    } else if (typeEffet == "soin") {
        std::cout << "+" << valeur << " PV";
    } else if (typeEffet == "pioche") {
        std::cout << "Pioche " << valeur << " carte(s)";
    } else {
        std::cout << typeEffet << " (" << valeur << ")";
    }
    std::cout << std::endl;
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
    std::cout << "  -> Champion mis en jeu: " << nom;
    if (garde) {
        std::cout << " (GARDE)";
    }
    std::cout << std::endl;
}

void GameView::afficherAttaque(const std::string& cible, int degats) const {
    std::cout << "[ATK] Vous attaquez " << cible << " (-" << degats << " PV/degats)" << std::endl;
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
        std::cout << "  [" << (i+1) << "] " << carte->getNom() 
                  << " (Cout: " << carte->getCout() << " or)";
        
        if (carte->getType() == "champion") {
            auto champ = std::dynamic_pointer_cast<Cartes::Champion>(carte);
            if (champ) {
                std::cout << " [Champion " << champ->getPv() << "PV";
                if (champ->estGarde()) std::cout << " GARDE";
                std::cout << "]";
            }
        }
        std::cout << std::endl;
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
