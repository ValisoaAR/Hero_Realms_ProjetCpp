#pragma once
#include <map>
#include <memory>
#include <string>
#include "../Zones/ZoneDeCarte.hpp"
#include "../Systeme/Ressources.hpp"
#include "../Systeme/Faction.hpp"
#include "../Cartes/Champion.hpp"

namespace Game::Core {
    class Joueur {
    public:
        Joueur(const std::string& nom, int pv = 50);

        // Getters de base
        std::string getNom() const { return nom; }
        int getPv() const { return pv; }
        
        // Ressources
        const Systeme::Ressources& getRessources() const { return ressources; }
        
        // Zones de cartes (const)
        const Zones::ZoneDeCarte& getMain() const { return main; }
        const Zones::ZoneDeCarte& getDeck() const { return deck; }
        const Zones::ZoneDeCarte& getDefausse() const { return defausse; }
        
        // Zones de cartes (mutables)
        Zones::ZoneDeCarte& getMainMutable() { return main; }
        Zones::ZoneDeCarte& getDeckMutable() { return deck; }
        Zones::ZoneDeCarte& getDefausseMutable() { return defausse; }
        
        // Champions en jeu (const)
        const std::vector<std::shared_ptr<Cartes::Champion>>& getChampionsEnJeu() const { return championsEnJeu; }
        
        // Factions jouées ce tour
        const std::map<Systeme::FactionType, int>& getFactionsJouees() const { return factionsJouees; }

        // Gestion des PV
        void ajouterPv(int delta);
        void retirerPv(int delta);
        
        // Gestion de l'or
        void ajouterOr(int delta);
        void retirerOr(int delta);
        
        // Gestion du combat
        void ajouterCombat(int delta);
        void retirerCombat(int delta);
        
        // Gestion des champions
        void ajouterChampion(std::shared_ptr<Cartes::Champion> champion);
        void retirerChampion(int index);
        
        // Gestion des factions
        void ajouterFactionJouee(Systeme::FactionType faction);
        
        // Réinitialisation du tour
        void reinitialiserRessources();

    private:
        std::string nom;
        int pv;
        Systeme::Ressources ressources;
        Zones::ZoneDeCarte main;
        Zones::ZoneDeCarte deck;
        Zones::ZoneDeCarte defausse;
        
        // Champions actifs sur le terrain
        std::vector<std::shared_ptr<Cartes::Champion>> championsEnJeu;
        
        // Factions jouées ce tour (pour les bonus alliés)
        std::map<Systeme::FactionType, int> factionsJouees;
    };
}