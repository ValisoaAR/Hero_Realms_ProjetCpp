#pragma once
#include <memory>
#include <vector>
#include <random>
#include "Joueur.hpp"
#include "../Cartes/Carte.hpp"
#include "../Cartes/Champion.hpp"
#include "../Zones/Marche.hpp"

namespace Game::Core {

    // Forward declarations
    class GameController;
    class GameView;

    /**
     * IA simple qui prend des décisions basiques mais cohérentes
     * Stratégie :
     * - Joue toutes ses cartes
     * - Achète les cartes les plus chères qu'elle peut se permettre
     * - Attaque en priorité les champions avec garde, sinon le joueur
     * - Active tous ses champions
     */
    class IAJoueur {
    public:
        IAJoueur();
        
        // Joue un tour complet pour l'IA
        void jouerTour(GameController& controller, GameView& view, int joueurIdx, std::mt19937& rng);
        
    private:
        // Phases du tour
        void jouerToutesLesCartes(GameController& controller, Joueur& joueur, Joueur& adversaire);
        void acheterCartes(GameController& controller, GameView& view, Joueur& joueur, const Zones::Marche& marche, std::mt19937& rng);
        void attaquerAdversaire(GameController& controller, Joueur& joueur, Joueur& adversaire, std::mt19937& rng);
        void activerTousLesChampions(GameController& controller, Joueur& joueur, Joueur& adversaire);
        
        // Aide à la décision
        int choisirMeilleureCarteAcheter(const Zones::Marche& marche, int orDisponible, std::mt19937& rng);
        int choisirCibleAttaque(const Joueur& adversaire, std::mt19937& rng);
        int evaluerCarte(std::shared_ptr<Cartes::Carte> carte) const;
    };

} // namespace Game::Core
