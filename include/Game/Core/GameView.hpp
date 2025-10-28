#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Cartes/Carte.hpp"
#include "../Systeme/Faction.hpp"
#include "../Zones/Marche.hpp"

// Forward declarations
namespace Game::Core {
    class Joueur;
}

namespace Game::Core {

    class GameView {
    public:
        // Affichage général
        void afficherTitre() const;
        void afficherDebut() const;
        void afficherFinPartie(int vainqueur, int pvRestants) const;
        void afficherDebutTour(int tour, int joueurId) const;
        
        // Affichage de l'état du jeu
        void afficherEtatJoueur(const Joueur& joueur) const;
        void afficherMarche(const Zones::Marche& marche) const;
        
        // Affichage des actions
        void afficherMenuPrincipal() const;
        void afficherResultatAction(const std::string& message) const;
        void afficherErreur(const std::string& message) const;
        void afficherInfo(const std::string& message) const;
        
        // Affichage des effets
        void afficherEffet(const std::string& typeEffet, int valeur) const;
        void afficherAllieActive(Systeme::FactionType faction) const;
        void afficherChampionEnJeu(const std::string& nom, bool garde) const;
        
        // Affichage de combat
        void afficherAttaque(const std::string& cible, int degats) const;
        void afficherMortChampion(const std::string& nom) const;
        void afficherListeCibles(const Joueur& defenseur) const;
        
        // Demande d'input
        int demanderChoix(const std::string& question, int min, int max) const;
        bool demanderConfirmation(const std::string& question) const;
        
    private:
        void afficherSeparateur() const;
        void afficherLigne(const std::string& texte) const;
    };

} // namespace Game::Core
