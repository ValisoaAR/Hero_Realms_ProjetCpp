#pragma once
#include <string>

namespace Game::Systeme {
    class Capacite {
    public:
        Capacite(const std::string& nom, const std::string& description);
        virtual void activer() = 0;
        
        const std::string& getNom() const { return nom; }
        const std::string& getDescription() const { return description; }
        
    protected:
        std::string nom;
        std::string description;
    };
}