#include "Game/Systeme/Effet.hpp"

namespace Game::Systeme {

Effet::Effet(const std::string& type, int valeur,
             const std::string& condition_type,
             const std::string& condition_valeur,
             const std::string& activation)
    : type(type), valeur(valeur),
      condition_type(condition_type),
      condition_valeur(condition_valeur),
      activation(activation) {}

bool Effet::peutEtreActive() const {
    if (activation == "toujours") {
        return true;
    }
    
    if (condition_type == "aucune") {
        return true;
    }
    
    // Vérifier les conditions de faction ou de champion
    // À implémenter en fonction du contexte du jeu
    return false;
}

void Effet::appliquer() {
    if (!peutEtreActive()) {
        return;
    }
    
    // Appliquer l'effet en fonction de son type
    if (type == "or") {
        // Ajouter de l'or au joueur actif
    }
    else if (type == "dmg") {
        // Infliger des dégâts à une cible
    }
    else if (type == "pioche") {
        // Faire piocher des cartes au joueur
    }
    else if (type == "soin") {
        // Soigner une cible
    }
    else if (type == "sacrifice") {
        // Gérer le sacrifice d'une carte
    }
}

} // namespace Game::Systeme