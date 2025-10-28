// ✅ FICHIER UTILISÉ - Classe Joueur pour le jeu

#include "../../../include/Game/Core/Joueur.hpp"

namespace Game::Core {

Joueur::Joueur(const std::string& nom, int pv)
    : nom(nom), pv(pv), ressources(0, 0),
      main("main"), deck("deck"), defausse("defausse")
{
}

void Joueur::ajouterPv(int delta) {
    pv += delta;
    // Limiter à 50 PV maximum (règle standard Hero Realms)
    if (pv > 50) pv = 50;
}

void Joueur::retirerPv(int delta) {
    pv -= delta;
    if (pv < 0) pv = 0;
}

void Joueur::ajouterOr(int delta) {
    ressources.ajouterOr(delta);
}

void Joueur::retirerOr(int delta) {
    ressources.retirerOr(delta);
}

void Joueur::ajouterCombat(int delta) {
    ressources.ajouterCombat(delta);
}

void Joueur::retirerCombat(int delta) {
    ressources.retirerCombat(delta);
}

void Joueur::ajouterChampion(std::shared_ptr<Cartes::Champion> champion) {
    championsEnJeu.push_back(champion);
}

void Joueur::retirerChampion(int index) {
    if (index >= 0 && index < (int)championsEnJeu.size()) {
        championsEnJeu.erase(championsEnJeu.begin() + index);
    }
}

void Joueur::ajouterFactionJouee(Systeme::FactionType faction) {
    factionsJouees[faction]++;
}

void Joueur::reinitialiserRessources() {
    ressources.reinitialiser();
    factionsJouees.clear();
}

} // namespace Game::Core