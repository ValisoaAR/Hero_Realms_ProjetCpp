#pragma once
#include <string>

class ZoneDeCarte {
public:
    int id;
    std::string type; // deck, main, defausse, champions, deck_marche, marche, sacrifice
    int owner_joueur; // id du joueur si applicable
    int owner_table; // id de la table si applicable

    ZoneDeCarte(int id, const std::string& type, int owner_joueur, int owner_table);
};
