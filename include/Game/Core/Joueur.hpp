#pragma once
#include "../Zones/ZoneDeCarte.hpp"
#include "../Systeme/Ressources.hpp"

namespace Game::Core {
    class Joueur {
    public:
        Joueur(int id, int pv = 50);

        int getId() const { return id; }
        int getPv() const { return pv; }
        int getOr() const { return ressources.getOr(); }
        int getCombat() const { return ressources.getCombat(); }

        void modifierPv(int delta);
        void modifierOr(int delta);
        void modifierCombat(int delta);

    private:
        int id;
        int pv;
        Systeme::Ressources ressources;
        Zones::ZoneDeCarte main;
        Zones::ZoneDeCarte deck;
    public:
        Zones::ZoneDeCarte& getDeck() { return deck; }
        void setDeck(const Zones::ZoneDeCarte& d) { deck = d; }
        Zones::ZoneDeCarte defausse;
        Zones::ZoneDeCarte champions;
    };
}