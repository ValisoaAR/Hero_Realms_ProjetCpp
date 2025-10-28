#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../Cartes/Carte.hpp"

namespace Game::Zones {
    class ZoneDeCarte {
    public:
        ZoneDeCarte(const std::string& type);
        
        // Nouvelles méthodes avec shared_ptr
        void ajouterCarte(std::shared_ptr<Cartes::Carte> carte);
        std::shared_ptr<Cartes::Carte> retirerCarte(int position);
        std::shared_ptr<Cartes::Carte> getCarte(int position) const;
        
        void melanger();
        size_t getNbCartes() const { return cartes.size(); }
        bool estVide() const { return cartes.empty(); }
        void vider() { cartes.clear(); }
        
        // Accès aux cartes
        const std::vector<std::shared_ptr<Cartes::Carte>>& getCartes() const { return cartes; }
        std::vector<std::shared_ptr<Cartes::Carte>>& getCartesMutable() { return cartes; }
        
    protected:
        std::string type;  // deck, main, defausse, champions, marche
        std::vector<std::shared_ptr<Cartes::Carte>> cartes;
    };
}