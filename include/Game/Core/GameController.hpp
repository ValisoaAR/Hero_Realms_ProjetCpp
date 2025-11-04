#pragma once
#include <vector>
#include <memory>
#include <random>
#include <string>
#include "../Cartes/Carte.hpp"
#include "../Cartes/Champion.hpp"
#include "../Systeme/Faction.hpp"
#include "../Systeme/Effet.hpp"
#include "../Zones/Marche.hpp"
#include "../Zones/ZoneFireGem.hpp"
#include "Joueur.hpp"

namespace Game::Core {

    // Forward declaration de GameView
    class GameView;

    // Contrôleur principal du jeu
    class GameController {
    public:
        GameController();
        
        // Boucle de jeu principale
        void jouerPartie(GameView& view);
        
        // Initialisation
        void initialiserPartie();
        void initialiserJoueur(Joueur& joueur);
        void initialiserMarche();
        
        // Gestion du tour
        void jouerTour(int joueurIdx, GameView& view);
        void debutTour(Joueur& joueur);
        void finTour(Joueur& joueur);
        
        // Actions du joueur
        bool jouerCarte(Joueur& joueur, int carteIdx, Joueur* adversaire = nullptr, bool estIA = false);
        bool acheterCarte(Joueur& joueur, int marcheIdx);
        bool acheterFireGem(Joueur& joueur);
        bool attaquer(Joueur& attaquant, Joueur& defenseur, int cibleIdx);
        bool activerChampion(Joueur& joueur, int championIdx, Joueur* adversaire = nullptr, bool estIA = false);
        bool sacrifierCarte(Joueur& joueur, int carteIdx);
        
        // Gestion des cartes
        void piocherCartes(Joueur& joueur, int nombre);
        void defausserMain(Joueur& joueur);
        void defausserChampions(Joueur& joueur);
        
        // Application des effets
        void appliquerEffetsCarte(Joueur& joueur, std::shared_ptr<Cartes::Carte> carte, bool estAllie, Joueur* adversaire = nullptr, bool estIA = false);
        void appliquerEffet(Joueur& joueur, const Systeme::Effet& effet, std::shared_ptr<Cartes::Carte> carte, bool estIA = false);
        void appliquerEffetAvecAdversaire(Joueur& joueur, Joueur& adversaire, const Systeme::Effet& effet, std::shared_ptr<Cartes::Carte> carte, bool adversaireEstIA = false);
        
        // Effets complexes
        void gererEffetChoix(Joueur& joueur, std::shared_ptr<Cartes::Carte> carte, bool estIA = false);
        void gererDefausseAdversaire(Joueur& adversaire, int nombre, bool adversaireEstIA = false);
        void gererStunChampion(Joueur& adversaire);
        int compterChampionsEnJeu(const Joueur& joueur) const;
        int compterGardesEnJeu(const Joueur& joueur) const;
        int compterCartesFaction(const Joueur& joueur, Systeme::FactionType faction) const;
        
        // Vérifications
        bool verifierAllie(const Joueur& joueur, Systeme::FactionType faction) const;
        bool partieFinie() const;
        int getVainqueur() const;
        
        // Getters
        const Joueur& getJoueur(int idx) const { return (idx == 0) ? joueur1 : joueur2; }
        Joueur& getJoueurMutable(int idx) { return (idx == 0) ? joueur1 : joueur2; }
        const Zones::Marche& getMarche() const { return marche; }
        Zones::ZoneFireGem& getZoneFireGem() { return zoneFireGem; }
        const std::vector<std::shared_ptr<Cartes::Carte>>& getPiocheMarche() const { return piocheMarche; }
        
        // God-Mode
        void activerGodMode(GameView& view, int joueurIdx);
        void modifierPV(Joueur& joueur, int nouveauxPV);
        void acheterDePioche(Joueur& joueur, int carteIdx);
        bool isGodModeActif() const { return godModeActif; }
        void toggleGodMode() { godModeActif = !godModeActif; }
        
        // IA
        void setJoueur2EstIA(bool estIA) { joueur2EstIA = estIA; }
        bool isJoueur2IA() const { return joueur2EstIA; }
        void setNomJoueur2(const std::string& nom);
        
    private:
        Joueur joueur1;
        Joueur joueur2;
        Zones::Marche marche;
        Zones::ZoneFireGem zoneFireGem;
        std::vector<std::shared_ptr<Cartes::Carte>> piocheMarche;
        std::mt19937 rng;
        int tourActuel;
        bool finie;
        bool godModeActif;
        bool joueur2EstIA;
    };

} // namespace Game::Core
