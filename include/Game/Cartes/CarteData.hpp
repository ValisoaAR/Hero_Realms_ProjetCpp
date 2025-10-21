
#ifndef CARTEDATA_HPP
#define CARTEDATA_HPP

#include "Carte.hpp"
#include <vector>
#include <memory>

namespace HeroRealms {


// Crée toutes les cartes du Base Set (marché)
std::vector<std::shared_ptr<Game::Cartes::Carte>> CreerCartesBaseSet();

// Crée les 16 Fire Gems
std::vector<std::shared_ptr<Game::Cartes::Carte>> CreerFireGems();

// Crée le deck de départ d'un joueur (10 cartes)
std::vector<std::shared_ptr<Game::Cartes::Carte>> CreerDeckDepart();

} // namespace HeroRealms

#endif // CARTE_HPP