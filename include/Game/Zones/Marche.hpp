#pragma once
#include "ZoneDeCarte.hpp"

namespace Game::Zones {
    class Marche : public ZoneDeCarte {
    public:
        Marche();
        void rafraichir();
        void acheterCarte(int position);
        void defausserCarte(int position);
        
    private:
        static constexpr int TAILLE_MARCHE = 5;
    };
}