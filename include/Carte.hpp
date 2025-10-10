#pragma once
#include <string>

class Carte {
public:
    int id;
    std::string nom;
    int cout;
    std::string type; // action, objet, champion
    std::string faction;
    std::string description;

    Carte(int id, const std::string& nom, int cout, const std::string& type, const std::string& faction, const std::string& description);
};
