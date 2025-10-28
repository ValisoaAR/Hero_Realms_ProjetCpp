#include <iostream>
#include "Game/Core/GameController.hpp"
#include "Game/Core/GameView.hpp"

using namespace Game::Core;

int main() {
    // Création du contrôleur et de la vue
    GameController controller;
    GameView view;
    
    // Lancer la partie (toute la logique est dans le contrôleur)
    controller.jouerPartie(view);
    
    return 0;
}

