#pragma once
#include "ZoneDeCarte.hpp"
#include <memory>
#include <random>

namespace Game::Zones {
    class Marche : public ZoneDeCarte {
    public:
        Marche();
        
        // Initialiser avec une pioche
        void initialiser(std::vector<std::shared_ptr<Cartes::Carte>>& pioche, std::mt19937& rng);
        
        // Remplir le marché depuis la pioche
        void remplir(std::vector<std::shared_ptr<Cartes::Carte>>& pioche);
        
        // Retirer une carte du marché (après achat)
        std::shared_ptr<Cartes::Carte> acheter(int position);
        
        // Rafraîchir le marché (défausser tout et piocher de nouvelles cartes)
        void rafraichir(std::vector<std::shared_ptr<Cartes::Carte>>& pioche, 
                       std::vector<std::shared_ptr<Cartes::Carte>>& defausse);
        
    private:
        static constexpr int TAILLE_MARCHE = 5;
    };
}