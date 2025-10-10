#pragma once
#include <string>

class Effet {
public:
    int id;
    std::string type; // "or", "dmg", "pioche", "soin", "sacrifice"
    int valeur;
    std::string condition_type; // "aucune", "faction", "champion"
    std::string condition_valeur; // ex: "Imperial", "Necros", id de champion...
    std::string activation; // "toujours", "sacrifice"

    Effet(int id, const std::string& type, int valeur, const std::string& condition_type, const std::string& condition_valeur, const std::string& activation);
};
