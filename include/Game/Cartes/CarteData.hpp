#ifndef CARTE_HPP
#define CARTE_HPP

#include "Carte.hpp"
#include <vector>
#include <memory>

namespace HeroRealms {

// Crée toutes les cartes du Base Set (marché)
std::vector<std::shared_ptr<Carte>> CreerCartesBaseSet();

// Crée les 16 Fire Gems
std::vector<std::shared_ptr<Carte>> CreerFireGems();

// Crée le deck de départ d'un joueur (10 cartes)
std::vector<std::shared_ptr<Carte>> CreerDeckDepart();

} // namespace HeroRealms

#endif // CARTE_HPP