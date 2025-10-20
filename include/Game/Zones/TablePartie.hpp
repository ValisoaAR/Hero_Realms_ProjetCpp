#pragma once
#include "ZoneDeCarte.hpp"
#include "Marche.hpp"

namespace Game::Zones {
    class TablePartie {
    public:
        TablePartie();
        
        int getNbGemmes() const { return nb_gemmes; }
        void modifierNbGemmes(int delta);
        
        Marche& getMarche() { return marche; }
        ZoneDeCarte& getDeckMarche() { return deck_marche; }
        ZoneDeCarte& getZoneSacrifice() { return zone_sacrifice; }
        
    private:
        int nb_gemmes;
        Marche marche;
        ZoneDeCarte deck_marche;
        ZoneDeCarte zone_sacrifice;
    };
}