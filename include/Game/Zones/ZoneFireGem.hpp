#pragma once
#include "ZoneDeCarte.hpp"
#include <memory>

namespace Game::Zones {
    class ZoneFireGem : public ZoneDeCarte {
    public:
        ZoneFireGem();
        
        // Initialiser avec des Fire Gems
        void initialiser();
        
        // Acheter une Fire Gem
        std::shared_ptr<Cartes::Carte> acheterFireGem();
        
        // Vérifier s'il reste des Fire Gems
        bool aDesFireGems() const { return !cartes.empty(); }
    };
}
