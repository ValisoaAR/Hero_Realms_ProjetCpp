#pragma once

namespace Game::Systeme {
    class Ressources {
    public:
        Ressources(int or_initial = 0, int combat_initial = 0);
        
        int getOr() const { return or_val; }
        int getCombat() const { return combat; }
        
        void ajouterOr(int montant);
        void ajouterCombat(int montant);
        void reinitialiser();
        
    private:
        int or_val;
        int combat;
    };
}